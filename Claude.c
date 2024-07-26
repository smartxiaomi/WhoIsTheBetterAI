//刘晓冰 by claude3.5 Sonnet
#include <stdio.h>
#include <string.h>

int main() {
   int N, M, K;
   char X[11];
   
   scanf("%d %s %d %d", &N, X, &M, &K);
   
   if (K == N) {
       printf("mei you mai %s de\n", X);
   } else if (K == M) {
       printf("kan dao le mai %s de\n", X);
   } else {
       printf("wang le zhao mai %s de\n", X);
   }
   
   return 0;
}
#include <stdio.h>

int main() {
   int N, A, B, C;
   
   scanf("%d", &N);
   
   for (int i = 0; i < N; i++) {
       scanf("%d %d %d", &A, &B, &C);
       
       if (A * B == C) {
           printf("Lv Yan\n");
       } else if (A + B == C) {
           printf("Tu Dou\n");
       } else {
           printf("zhe du shi sha ya!\n");
       }
   }
   
   return 0;
}
#include <stdio.h>

#define MAX_N 100

int main() {
   int N, K;
   int hats[MAX_N];
   int guess[MAX_N];
   int i, j;
   int correct, wrong, guessed;

   scanf("%d", &N);
   for (i = 0; i < N; i++) {
       scanf("%d", &hats[i]);
   }

   scanf("%d", &K);
   for (i = 0; i < K; i++) {
       correct = 0;
       wrong = 0;
       guessed = 0;

       for (j = 0; j < N; j++) {
           scanf("%d", &guess[j]);
           if (guess[j] != 0) {
               guessed = 1;
               if (guess[j] == hats[j]) {
                   correct = 1;
               } else {
                   wrong = 1;
               }
           }
       }

       if (correct && !wrong) {
           printf("Da Jiang!!!\n");
       } else {
           printf("Ai Ya\n");
       }
   }

   return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX_LEN 201

void cut_and_paste(char *str, int start, int end, char *before, char *after) {
   char clipboard[MAX_LEN] = {0};
   char temp[MAX_LEN] = {0};
   int i, j, len = strlen(str);

   // Cut
   strncpy(clipboard, str + start - 1, end - start + 1);
   clipboard[end - start + 1] = '\0';
   strcpy(temp, str + end);
   str[start - 1] = '\0';
   strcat(str, temp);

   // Paste
   char *pos = strstr(str, before);
   if (pos != NULL) {
       pos += strlen(before);
       strcpy(temp, pos);
       *pos = '\0';
       strcat(str, clipboard);
       strcat(str, temp);
   } else {
       strcat(str, clipboard);
   }
}

int main() {
   char str[MAX_LEN];
   int n, start, end;
   char before[6], after[6];

   scanf("%s", str);
   scanf("%d", &n);

   for (int i = 0; i < n; i++) {
       scanf("%d %d %s %s", &start, &end, before, after);
       cut_and_paste(str, start, end, before, after);
   }

   printf("%s\n", str);
   return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
   int n0, n1, n;
   scanf("%d %d %d", &n0, &n1, &n);

   int female_rooms = 0, male_rooms = 0;
   int min_diff = 1000000;
   int found_solution = 0;

   for (int f = 1; f <= n; f++) {
       if (n0 % f != 0) continue;
       
       int m = n - f;
       if (m <= 0 || n1 % m != 0) continue;

       int female_per_room = n0 / f;
       int male_per_room = n1 / m;

       if (female_per_room < 2 || male_per_room < 2) continue;

       int diff = abs(female_per_room - male_per_room);
       if (diff < min_diff) {
           min_diff = diff;
           female_rooms = f;
           male_rooms = m;
           found_solution = 1;
       }
   }

   if (found_solution) {
       printf("%d %d\n", female_rooms, male_rooms);
   } else {
       printf("No Solution\n");
   }

   return 0;
}
#include <stdio.h>

int sum_digits(long long n) {
   int sum = 0;
   while (n > 0) {
       sum += n % 10;
       n /= 10;
   }
   return sum;
}

char determine_winner(long long NA, long long NB) {
   int SA = sum_digits(NA);
   int SB = sum_digits(NB);
   
   int A_is_dad = (NA % SB == 0);
   int B_is_dad = (NB % SA == 0);
   
   if (A_is_dad && !B_is_dad) return 'A';
   if (B_is_dad && !A_is_dad) return 'B';
   
   return (NA > NB) ? 'A' : 'B';
}

int main() {
   int N;
   scanf("%d", &N);
   
   for (int i = 0; i < N; i++) {
       long long NA, NB;
       scanf("%lld %lld", &NA, &NB);
       printf("%c\n", determine_winner(NA, NB));
   }
   
   return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
   int data[MAX_N];
   int top;
} Stack;

void init(Stack *s) {
   s->top = -1;
}

void push(Stack *s, int value) {
   s->data[++s->top] = value;
}

int pop(Stack *s) {
   return s->data[s->top--];
}

int peek(Stack *s) {
   return s->data[s->top];
}

int is_empty(Stack *s) {
   return s->top == -1;
}

int main() {
   int N, ring, towers = 0, max_height = 0;
   Stack A, B;
   init(&A);
   init(&B);

   scanf("%d", &N);

   for (int i = 0; i < N; i++) {
       scanf("%d", &ring);

       if (is_empty(&A) || ring < peek(&A)) {
           push(&A, ring);
       } else {
           while (!is_empty(&B) && ring > peek(&B)) {
               push(&A, pop(&B));
           }

           if (!is_empty(&A)) {
               towers++;
               if (A.top + 1 > max_height) {
                   max_height = A.top + 1;
               }
               init(&A);
           }

           push(&B, ring);
       }
   }

   if (!is_empty(&A)) {
       towers++;
       if (A.top + 1 > max_height) {
           max_height = A.top + 1;
       }
   }

   if (!is_empty(&B)) {
       towers++;
       if (B.top + 1 > max_height) {
           max_height = B.top + 1;
       }
   }

   printf("%d %d\n", towers, max_height);

   return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SCHOOLS 5000
#define MAX_NAME_LENGTH 7

typedef struct {
   char name[MAX_NAME_LENGTH];
   int students;
   int rooms;
} School;

typedef struct {
   int capacity;
   int remaining;
} Room;

int compare(const void *a, const void *b) {
   return ((School*)b)->students - ((School*)a)->students;
}

int main() {
   int N, C;
   scanf("%d %d", &N, &C);

   School schools[MAX_SCHOOLS];
   for (int i = 0; i < N; i++) {
       scanf("%s %d", schools[i].name, &schools[i].students);
       schools[i].rooms = 0;
   }

   qsort(schools, N, sizeof(School), compare);

   Room *rooms = NULL;
   int room_count = 0;

   for (int i = 0; i < N; i++) {
       int students_left = schools[i].students;
       while (students_left > 0) {
           int room_found = 0;
           for (int j = 0; j < room_count; j++) {
               if (rooms[j].remaining >= students_left) {
                   rooms[j].remaining -= students_left;
                   students_left = 0;
                   schools[i].rooms++;
                   room_found = 1;
                   break;
               }
           }
           if (!room_found) {
               room_count++;
               rooms = realloc(rooms, room_count * sizeof(Room));
               rooms[room_count-1].capacity = C;
               rooms[room_count-1].remaining = C;
               int to_assign = (students_left < C) ? students_left : C;
               rooms[room_count-1].remaining -= to_assign;
               students_left -= to_assign;
               schools[i].rooms++;
           }
       }
   }

   qsort(schools, N, sizeof(School), compare);
   for (int i = N-1; i >= 0; i--) {
       printf("%s %d\n", schools[i].name, schools[i].rooms);
   }
   printf("%d\n", room_count);

   free(rooms);
   return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_K 18
#define MAX_N (1 << MAX_K)

int k, n;
int l[MAX_K + 1][MAX_N];
int w;
int a[MAX_N + 1];

int solve(int round, int match, int min_val) {
   if (round > k) {
       return 1;
   }

   int left = 2 * match - 1;
   int right = 2 * match;

   if (round == k) {
       a[left] = w;
       a[right] = l[round][match];
       return (w >= min_val && l[round][match] >= min_val && w != l[round][match]);
   }

   int loser = l[round][match];
   int winner = (loser == l[round + 1][(match + 1) / 2]) ? w : l[round + 1][(match + 1) / 2];

   if (winner < loser || winner < min_val || loser < min_val) {
       return 0;
   }

   a[left] = winner;
   a[right] = loser;

   return solve(round + 1, (match - 1) / 2 + 1, winner);
}

int main() {
   scanf("%d", &k);
   n = 1 << k;

   for (int i = 1; i <= k; i++) {
       for (int j = 1; j <= (1 << (k - i)); j++) {
           scanf("%d", &l[i][j]);
       }
   }

   scanf("%d", &w);

   if (solve(1, 1, 1)) {
       for (int i = 1; i <= n; i++) {
           printf("%d", a[i]);
           if (i < n) printf(" ");
       }
       printf("\n");
   } else {
       printf("No Solution\n");
   }

   return 0;
}
#include <stdio.h>
#include <stdbool.h>

#define MAX_N 1000
#define MAX_M 1000

int N, M;
int map[MAX_N][MAX_M];
bool visited[MAX_N][MAX_M];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y, bool* has_treasure) {
   if (x < 0 || x >= N || y < 0 || y >= M || map[x][y] == 0 || visited[x][y]) {
       return;
   }

   visited[x][y] = true;
   if (map[x][y] >= 2) {
       *has_treasure = true;
   }

   for (int i = 0; i < 4; i++) {
       int nx = x + dx[i];
       int ny = y + dy[i];
       dfs(nx, ny, has_treasure);
   }
}

int main() {
   scanf("%d %d", &N, &M);

   for (int i = 0; i < N; i++) {
       for (int j = 0; j < M; j++) {
           scanf("%1d", &map[i][j]);
           visited[i][j] = false;
       }
   }

   int total_islands = 0;
   int treasure_islands = 0;

   for (int i = 0; i < N; i++) {
       for (int j = 0; j < M; j++) {
           if (map[i][j] != 0 && !visited[i][j]) {
               bool has_treasure = false;
               dfs(i, j, &has_treasure);
               total_islands++;
               if (has_treasure) {
                   treasure_islands++;
               }
           }
       }
   }

   printf("%d %d\n", total_islands, treasure_islands);

   return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100000
#define MAX_M 200
#define INF INT_MAX

typedef struct {
   int city;
   int power;
   int alive;
} Player;

typedef struct {
   int to;
   int time;
} Edge;

Player players[MAX_N];
Edge graph[MAX_M][MAX_M];
int dist[MAX_M];
int N, M, Me, D;
int current_city, current_power, current_day;

int compare_players(const void *a, const void *b) {
   Player *pa = (Player *)a;
   Player *pb = (Player *)b;
   return pa->power - pb->power;
}

void dijkstra(int start) {
   int visited[MAX_M] = {0};
   for (int i = 0; i < M; i++) {
       dist[i] = INF;
   }
   dist[start] = 0;

   for (int i = 0; i < M; i++) {
       int u = -1;
       int min_dist = INF;
       for (int j = 0; j < M; j++) {
           if (!visited[j] && dist[j] < min_dist) {
               u = j;
               min_dist = dist[j];
           }
       }
       if (u == -1) break;
       visited[u] = 1;

       for (int v = 0; v < M; v++) {
           if (graph[u][v].time > 0 && !visited[v]) {
               int new_dist = dist[u] + graph[u][v].time;
               if (new_dist < dist[v]) {
                   dist[v] = new_dist;
               }
           }
       }
   }
}

int find_next_target() {
   int target = -1;
   int min_diff = INF;
   int min_dist = INF;

   for (int i = 0; i < N; i++) {
       if (players[i].alive && players[i].power <= current_power) {
           int diff = current_power - players[i].power;
           if (diff < min_diff || (diff == min_diff && dist[players[i].city] < min_dist)) {
               min_diff = diff;
               min_dist = dist[players[i].city];
               target = i;
           }
       }
   }

   return target;
}

void move_to_city(int city) {
   printf("Move from %d to %d.\n", current_city, city);
   current_day += dist[city];
   current_city = city;
}

void defeat_player(int target) {
   printf("Get %d at %d on day %d.\n", players[target].power, current_city, current_day);
   current_power += players[target].power;
   players[target].alive = 0;
   current_day++;
}

int main() {
   scanf("%d %d %d %d", &N, &M, &Me, &D);

   for (int i = 0; i < N; i++) {
       scanf("%d %d", &players[i].city, &players[i].power);
       players[i].alive = 1;
   }

   memset(graph, 0, sizeof(graph));
   for (int i = 0; i < Me; i++) {
       int from, to, time;
       scanf("%d %d %d", &from, &to, &time);
       graph[from][to].time = graph[to][from].time = time;
   }

   current_city = players[0].city;
   current_power = players[0].power;
   current_day = 1;
   players[0].alive = 0;

   while (current_day <= D) {
       dijkstra(current_city);
       int target = find_next_target();

       if (target == -1) {
           for (int i = 1; i < N; i++) {
               if (players[i].alive && players[i].power > current_power) {
                   printf("Lose on day %d with %d.\n", current_day, current_power);
                   return 0;
               }
           }
           printf("WIN on day %d with %d!\n", current_day, current_power);
           return 0;
       }

       if (players[target].city != current_city) {
           move_to_city(players[target].city);
       }

       if (current_day > D) break;

       defeat_player(target);

       int alliance_power = 0;
       for (int i = 1; i < N; i++) {
           if (players[i].alive && players[i].city == current_city && players[i].power <= current_power) {
               alliance_power += players[i].power;
           }
       }

       if (alliance_power > 0 && alliance_power <= current_power) {
           printf("Get %d at %d on day %d.\n", alliance_power, current_city, current_day);
           current_power += alliance_power;
           for (int i = 1; i < N; i++) {
               if (players[i].alive && players[i].city == current_city && players[i].power <= current_power) {
                   players[i].alive = 0;
               }
           }
           current_day++;
       }
   }

   printf("Game over with %d.\n", current_power);
   return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 100001
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
   int color;
   int cost;
   int children_count;
   int children[MAX_N];
} Node;

Node tree[MAX_N];
int dp[MAX_N][3];
int N;

void dfs(int node) {
   int black_count = tree[node].color;
   int white_count = 1 - tree[node].color;

   for (int i = 0; i < tree[node].children_count; i++) {
       int child = tree[node].children[i];
       dfs(child);

       int new_black_count = black_count + dp[child][1];
       int new_white_count = white_count + dp[child][0];

       dp[node][0] = MIN(new_white_count + dp[child][2], new_black_count + tree[node].cost + dp[child][2]);
       dp[node][1] = MIN(new_black_count + dp[child][2], new_white_count + tree[node].cost + dp[child][2]);
       dp[node][2] = MIN(new_black_count + dp[child][2], new_white_count + dp[child][2]);
   }

   if (abs(black_count - white_count) <= 1) {
       dp[node][2] = MIN(dp[node][2], MIN(dp[node][0], dp[node][1]));
   }
}

int main() {
   scanf("%d", &N);

   for (int i = 1; i <= N; i++) {
       scanf("%d %d %d", &tree[i].color, &tree[i].cost, &tree[i].children_count);
       for (int j = 0; j < tree[i].children_count; j++) {
           scanf("%d", &tree[i].children[j]);
       }
   }

   memset(dp, 0x3f, sizeof(dp));
   dfs(1);

   printf("%d\n", dp[1][2]);

   return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MOD 998244353
#define MAX_N 100005
#define MAX_M 100005

int n, m;
int l[MAX_M], r[MAX_M];
int dp[1 << 16][2][2];
bool valid[1 << 16];

int count_bits(int x) {
   int count = 0;
   while (x) {
       count += x & 1;
       x >>= 1;
   }
   return count;
}

int main() {
   int t;
   scanf("%d", &t);

   while (t--) {
       scanf("%d %d", &n, &m);
       for (int i = 0; i < m; i++) {
           scanf("%d %d", &l[i], &r[i]);
       }

       int limit = (m > 16) ? 16 : m;
       memset(valid, true, sizeof(valid));

       for (int mask = 0; mask < (1 << limit); mask++) {
           for (int i = 1; i <= n; i++) {
               for (int j = i + 1; j <= n; j++) {
                   bool ok = true;
                   for (int k = 0; k < limit; k++) {
                       bool in_range = (i >= l[k] && i <= r[k]) || (j >= l[k] && j <= r[k]);
                       if (in_range != (mask & (1 << k))) {
                           ok = false;
                           break;
                       }
                   }
                   if (ok) {
                       valid[mask] = false;
                       break;
                   }
               }
               if (!valid[mask]) break;
           }
       }

       memset(dp, 0, sizeof(dp));
       dp[0][0][0] = 1;

       for (int i = 0; i < m; i++) {
           int new_dp[1 << 16][2][2] = {0};
           for (int mask = 0; mask < (1 << limit); mask++) {
               for (int x = 0; x < 2; x++) {
                   for (int y = 0; y < 2; y++) {
                       if (dp[mask][x][y] == 0) continue;

                       bool in_range_x = (l[i] <= x * n && x * n <= r[i]);
                       bool in_range_y = (l[i] <= y * n && y * n <= r[i]);

                       int new_mask = (i < limit) ? (mask | (1 << i)) : mask;
                       int result = in_range_x || in_range_y;

                       new_dp[new_mask][x][y] = (new_dp[new_mask][x][y] + dp[mask][x][y]) % MOD;
                       if (i < limit) {
                           new_dp[mask][x][y] = (new_dp[mask][x][y] + dp[mask][x][y]) % MOD;
                       }
                   }
               }
           }
           memcpy(dp, new_dp, sizeof(dp));
       }

       int answer = 0;
       for (int mask = 0; mask < (1 << limit); mask++) {
           if (valid[mask]) {
               answer = (answer + dp[mask][0][1] + dp[mask][1][0]) % MOD;
           }
       }

       printf("%d\n", answer);
   }

   return 0;
}