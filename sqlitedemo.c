/*
** Execute the program in the VM resuling from Vdbe.exec()
*/
int sqlite3VdbeExec(
  Vdbe *p                    /* The VDBE */
){
  int pc=0;                  /* The program counter */
  Op *aOp = p->aOp;          /* Copy of p->aOp */
  Op *pOp;                   /* Current operation */
  int rc = SQLITE_OK;        /* Value to return */
  sqlite3 *db = p->db;       /* The database */
  u8 resetSchemaOnFault = 0; /* Reset schema after an error if positive */
  u8 encoding = ENC(db);     /* The database encoding */
  int iCompare = 0;          /* Result of last OP_Compare operation */
  unsigned nVmStep = 0;      /* Number of virtual machine steps */

#ifdef SQLITE_DEBUG
  sqlite3VdbeIOTraceSql(p);
#endif
#if !defined(SQLITE_OMIT_PROGRESS_CALLBACK) || !defined(SQLITE_OMIT_VIRTUALTABLE)
  /* This is a utility function to call the progress callback and/or
  ** call the xSync method on virtual tables.  The way it works is that
  ** if the progress callback returns non-zero, then the xSync method
  ** of all virtual tables is invoked, and we return SQLITE_ABORT to the
  ** caller.
  */
  int checkProgress(void){
    int rc = SQLITE_OK;
#ifndef SQLITE_OMIT_PROGRESS_CALLBACK
    if( db->xProgress ){
      if( db->nProgressOps==0 ){
        db->nProgressOps = 1000;
        if( db->xProgress(db->pProgressArg) ){
          rc = SQLITE_INTERRUPT;
        }
      }
      db->nProgressOps--;
    }
#endif
#ifndef SQLITE_OMIT_VIRTUALTABLE
    if( rc==SQLITE_OK && db->nVTrans>0 ){
      rc = sqlite3VtabSync(db, &p->zErrMsg);
    }
#endif
    return rc;
  }
#endif

  if( p->rc==SQLITE_NOMEM ){
    /* This happens if a malloc() inside a call to sqlite3_column_text() or
    ** sqlite3_column_text16() failed.  */
    goto no_mem;
  }
  assert( p->rc==SQLITE_OK || p->rc==SQLITE_BUSY );
  p->rc = SQLITE_OK;
  assert( p->explain==0 );
  p->pResultSet = 0;
  db->busyHandler.nBusy = 0;
  CHECK_FOR_INTERRUPT;
  sqlite3VdbeIOTraceMsg(p, "start");

  /* Sanity check (We always come into this fuction with the stack having
  ** at least one entry.  If this ever changes because of a refactoring
  ** then we need to make sure that aStack is initialized correctly.  Even
  ** though there is assert() below which checks for this, we still need
  ** to initialize aStack, to silence compiler warnings.)
  */
  assert( p->stackDepth>0 );
  if( p->stackDepth<=0 ) p->aStack[0].flags = MEM_Null;

  do{
    assert( pc>=0 && pc<p->nOp );
    assert( (p->aStack[p->stackDepth-1].flags & MEM_RowSet)==0 );

    /* Errors can accumulate silently, for example when a parser error occurs
    ** via sqlite3_prepare_v2().  When an error occurs the bit that represents
    ** that error in db->errMask is set.  Or, if many errors occur, the first
    ** error is set and later errors are commented out.  The following code
    ** block checks for errors and aborts if there are any.
    */
    if( (db->errMask & ~p->ignoreRaised) ){
      p->rc = sqlite3ErrCode(db);
      sqlite3VdbeIOTraceMsg(p, "abort due to error");
      goto abort_due_to_error;
    }

    /* Invoke the xTrace callback if there is one
    */
#ifdef SQLITE_ENABLE_VDBE_TRACE
    if( db->xTrace ){
      (*db->xTrace)(db->pTraceArg, (const char*)p->zSql);
      if( (rc = checkProgress())!=0 ) goto abort_due_to_error;
    }
#endif

    /* Check the program counter and make sure it is within range of the
    ** opcodes.  If not, halt the program.
    */
    if( pc>=p->nOp ){
      sqlite3VdbeIOTraceMsg(p, "end of code");
      rc = SQLITE_OK;
      goto vdbe_return;
    }

    /* Sanity check on the current stack depth
    */
#ifdef SQLITE_DEBUG
    assert( p->stackDepth>=0 );
    assert( p->stackDepth<=p->nMem );
#endif

    /* The following are sanity checks to make sure that all is well in
    ** the world of the virtual machine.  This block of code can be
    ** deleted with no change to function and a small performance gain.
    */
#ifdef VDBE_PROFILE
    nProfileOp++;
    p->aOp[pc].nExec++;
    p->aOp[pc].nCycle += sqlite3Hwtime() - p->startTime;
#endif

    /* Trace the next opcode if required.  The zTraceArg argument
    ** can be either a NULL pointer or a pre-formatted string.  The
    ** traceOnce flag means that only the first occurrence of this
    ** particular opcode is reported, and subsequent occurrances are
    ** skipped.
    */
    if( db->flags & SQLITE_VdbeTrace ){
      u8 traceOnce = (db->flags & SQLITE_TraceVdbeLast)!=0 ? 3 : 0;
      if( p->nOp<200 || pc<p->nOp-10 ){
        sqlite3VdbeIOTraceXOpCode(p, pc, &aOp[pc], traceOnce);
      }
    }

    /* Check to see if we need to simulate an interrupt.  This only happens
    ** if we have a special test build.
    */
#ifdef SQLITE_TEST
    if( sqlite3_interrupt_count>0 ){
      sqlite3_interrupt_count--;
      if( sqlite3_interrupt_count==0 ){
        sqlite3_interrupt(db);
      }
    }
#endif

#ifdef SQLITE_DEBUG
    /* If the number of virtual machine steps exceeds the maximum allowed,
    ** then this might be a run-away infinite loop.  Call the progress
    ** callback to check to see if we need to abort.
    */
    nVmStep++;
    if( nVmStep==1000000000 ){
      nVmStep = 0;
      if( checkProgress()!=0 ) goto abort_due_to_error;
    }
#endif

    /* Fetch and decode the next opcode */
    pOp = &aOp[pc++];
    switch( pOp->opcode ){

/*****************************************************************************
** What follows is a massive switch statement where each case implements a
** separate instruction in the virtual machine.  If we have a
** virtualMachinePtr register, the Nth instruction contains an additional
** "virtualMachinePtr += N;" statement.
**
** If virtualMachinePtr is defined, then the switch statement is flat.
** Otherwise, we must nest the switch inside a loop in order to be able
** to use break and continue.
*/

/* Opcode:  Goto * P2 * * *
**
** An unconditional jump to address P2.
** The next instruction executed will be 
** the one at index P2 from the beginning of
** the program.
**
** The P1 parameter is not used by this opcode.  It is only there
** so that the three-operand syntax will conform to the established
** template for all opcodes.
*/
case OP_Goto: {             /* jump */
  pc = pOp->p2;
  break;
}

/* Opcode:  Gosub P1 P2 * * *
**
** Write the current address onto register P1
** and then jump to address P2.
*/
case OP_Gosub: {            /* jump */
  assert( pOp->p1>0 && pOp->p1<=p->nMem );
  pIn1 = &p->aMem[pOp->p1];
  assert( pIn1->flags==MEM_Null );
  pIn1->flags = MEM_Int;
  pIn1->u.i = pc;
  REGISTER_TRACE(pOp->p1, pIn1);
  pc = pOp->p2;
  break;
}

/* Opcode:  Return P1 * * * *
**
** Jump to the next instruction after the address in register P1.
*/
case OP_Return: {           /* in1 */
  pIn1 = &p->aMem[pOp->p1];
  assert( pIn1->flags==MEM_Int );
  pc = (int)pIn1->u.i;
  pIn1->flags = MEM_Null;
  break;
}

/* Opcode:  Yield P1 * * * *
**
** Swap the program counter with the value in register P1.
*/
case OP_Yield: {            /* in1 */
  int pcDest;
  pIn1 = &p->aMem[pOp->p1];
  assert( pIn1->flags==MEM_Int );
  pcDest = (int)pIn1->u.i;
  pIn1->u.i = pc;
  REGISTER_TRACE(pOp->p1, pIn1);
  pc = pcDest;
  break;
}

/* Opcode:  HaltIfNull  P1 P2 P3 P4 *
**
** Check the value in register P3.  If it is NULL then Halt using
** parameter P1, P2, and P4 as if this were a Halt instruction.  If the
** value in register P3 is not NULL, then this routine is a no-op.
*/
case OP_HaltIfNull: {      /* in3 */
  pIn3 = &p->aMem[pOp->p3];
  if( (pIn3->flags & MEM_Null)==0 ) break;
  /* Fall through into OP_Halt */
}

/* Opcode:  Halt P1 P2 * P4 *
**
** Exit immediately.  All open cursors, etc are closed
** automatically.
**
** P1 is the result code returned by sqlite3_exec(), sqlite3_reset(),
** or sqlite3_finalize().  For a normal halt, this should be SQLITE_OK (0).
** For errors, it can be some other value.  If P1!=0 then P2 will determine
** whether or not to rollback the current transaction.  Do not rollback
** if P2==OE_Fail. Do the rollback if P2==OE_Rollback.  If P2==OE_Abort,
** then back out all changes that have occurred during this execution of the
** VDBE, but do not rollback the transaction. 
**
** If P4 is not null then it is an error message string.
**
** There is an implied "Halt 0 0 0" instruction inserted at the very end of
** every program.  So a jump past the last instruction of the program
** is the same as executing Halt.
*/
case OP_Halt: {
  p->pc = pc;
  p->rc = pOp->p1;
  p->errorAction = (u8)pOp->p2;
  p->nChange = p->nChangeV;
  p->pc = pc;
  if( p->rc ){
    p->zErrMsg = pOp->p4.z;
    testcase( p->rc==SQLITE_CORRUPT );
    testcase( p->rc==SQLITE_MISUSE );
    testcase( p->rc==SQLITE_FULL );
    testcase( p->rc==SQLITE_NOMEM );
    testcase( p->rc==SQLITE_IOERR_READ );
    testcase( p->rc==SQLITE_IOERR_WRITE );
    testcase( p->rc==SQLITE_IOERR_FSYNC );
    testcase( p->rc==SQLITE_IOERR_DIR_FSYNC );
    testcase( p->rc==SQLITE_IOERR_TRUNCATE );
    testcase( p->rc==SQLITE_IOERR_FSTAT );
    testcase( p->rc==SQLITE_IOERR_UNLOCK );
    testcase( p->rc==SQLITE_IOERR_LOCK );
    testcase( p->rc==SQLITE_IOERR_CLOSE );
    testcase( p->rc==SQLITE_IOERR_DIR_CLOSE );
    testcase( p->rc==SQLITE_IOERR_SHMOPEN );
    testcase( p->rc==SQLITE_IOERR_SHMSIZE );
    testcase( p->rc==SQLITE_LOCKED_SHAREDCACHE );
    testcase( p->rc==SQLITE_BUSY );
    testcase( p->rc==SQLITE_READONLY );
    testcase( p->rc==SQLITE_INTERRUPT );
    testcase( p->rc==SQLITE_CONSTRAINT );
    testcase( p->rc==SQLITE_CANTOPEN );
    testcase( p->rc==SQLITE_IOERR_SEEK );
    if( p->zErrMsg==0 ){
      if( p->rc!=SQLITE_CONSTRAINT || p->errorAction!=OE_Default ){
        p->zErrMsg = (char *)sqlite3ErrStr(p->rc);
      }
    }
  }
  rc = sqlite3VdbeHalt(p);
  assert( rc==SQLITE_OK || rc==SQLITE_BUSY || rc==SQLITE_NOMEM );
  if( rc==SQLITE_BUSY ){
    p->rc = rc = SQLITE_BUSY;
  }else{
    rc = p->rc ? SQLITE_ERROR : SQLITE_OK;
  }
  goto vdbe_return;
}