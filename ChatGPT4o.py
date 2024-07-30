import numpy as np
import pygame
import sys

# Constants
BOARD_SIZE = 8
WHITE = -1
BLACK = 1
EMPTY = 0
TILE_SIZE = 60
WINDOW_SIZE = BOARD_SIZE * TILE_SIZE
FPS = 30
COLORS = {EMPTY: (34, 139, 34), BLACK: (0, 0, 0), WHITE: (255, 255, 255)}

# Initialize pygame
pygame.init()
screen = pygame.display.set_mode((WINDOW_SIZE, WINDOW_SIZE + 50))
pygame.display.set_caption("ChatGPT4o Reversi")
font = pygame.font.SysFont("Arial", 24)

class Reversi:
    def __init__(self):
        self.board = np.zeros((BOARD_SIZE, BOARD_SIZE), dtype=int)
        self.board[3, 3], self.board[4, 4] = WHITE, WHITE
        self.board[3, 4], self.board[4, 3] = BLACK, BLACK
        self.current_player = BLACK

    def display_board(self):
        screen.fill(COLORS[EMPTY])
        for x in range(BOARD_SIZE):
            for y in range(BOARD_SIZE):
                pygame.draw.rect(screen, COLORS[EMPTY], (y * TILE_SIZE, x * TILE_SIZE, TILE_SIZE, TILE_SIZE))
                pygame.draw.rect(screen, (0, 0, 0), (y * TILE_SIZE, x * TILE_SIZE, TILE_SIZE, TILE_SIZE), 1)
                if self.board[x, y] != EMPTY:
                    pygame.draw.circle(screen, COLORS[self.board[x, y]], (y * TILE_SIZE + TILE_SIZE // 2, x * TILE_SIZE + TILE_SIZE // 2), TILE_SIZE // 2 - 4)

        self.show_scores()
        pygame.display.flip()

    def show_scores(self):
        human_score = np.sum(self.board == BLACK)
        machine_score = np.sum(self.board == WHITE)
        score_text = f"Human (Black): {human_score}  ChatGPT-4o (White): {machine_score}"
        text_surface = font.render(score_text, True, (255, 255, 255))
        screen.blit(text_surface, (10, WINDOW_SIZE + 10))

    def is_valid_move(self, x, y, player):
        if self.board[x, y] != EMPTY:
            return False
        opponent = -player
        directions = [(1, 0), (0, 1), (1, 1), (1, -1), (-1, 0), (0, -1), (-1, -1), (-1, 1)]
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            found_opponent = False
            while 0 <= nx < BOARD_SIZE and 0 <= ny < BOARD_SIZE:
                if self.board[nx, ny] == opponent:
                    found_opponent = True
                elif self.board[nx, ny] == player and found_opponent:
                    return True
                else:
                    break
                nx += dx
                ny += dy
        return False

    def make_move(self, x, y, player):
        if not self.is_valid_move(x, y, player):
            return False
        self.board[x, y] = player
        opponent = -player
        directions = [(1, 0), (0, 1), (1, 1), (1, -1), (-1, 0), (0, -1), (-1, -1), (-1, 1)]
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            cells_to_flip = []
            while 0 <= nx < BOARD_SIZE and 0 <= ny < BOARD_SIZE:
                if self.board[nx, ny] == opponent:
                    cells_to_flip.append((nx, ny))
                elif self.board[nx, ny] == player:
                    for cx, cy in cells_to_flip:
                        self.board[cx, cy] = player
                    break
                else:
                    break
                nx += dx
                ny += dy
        return True

    def get_valid_moves(self, player):
        valid_moves = []
        for x in range(BOARD_SIZE):
            for y in range(BOARD_SIZE):
                if self.is_valid_move(x, y, player):
                    valid_moves.append((x, y))
        return valid_moves

    def machine_move(self):
        valid_moves = self.get_valid_moves(WHITE)
        if valid_moves:
            x, y = valid_moves[np.random.randint(len(valid_moves))]
            self.make_move(x, y, WHITE)

    def play(self):
        while True:
            self.display_board()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                elif event.type == pygame.MOUSEBUTTONDOWN and self.current_player == BLACK:
                    x, y = event.pos[1] // TILE_SIZE, event.pos[0] // TILE_SIZE
                    if self.make_move(x, y, BLACK):
                        self.current_player = WHITE
                        pygame.time.wait(500)
                        self.machine_move()
                        self.current_player = BLACK

            valid_moves = self.get_valid_moves(self.current_player)
            if not valid_moves:
                self.current_player = -self.current_player
                if not self.get_valid_moves(self.current_player):
                    break

        self.display_board()
        pygame.time.wait(2000)
        self.show_winner()

    def show_winner(self):
        human_score = np.sum(self.board == BLACK)
        machine_score = np.sum(self.board == WHITE)
        winner_text = ""
        if human_score > machine_score:
            winner_text = "Human wins!"
        elif machine_score > human_score:
            winner_text = "Ali wins!"
        else:
            winner_text = "It's a tie!"

        winner_surface = font.render(winner_text, True, (255, 255, 255))
        screen.blit(winner_surface, (WINDOW_SIZE // 2 - winner_surface.get_width() // 2, WINDOW_SIZE // 2 - winner_surface.get_height() // 2))
        pygame.display.flip()
        pygame.time.wait(3000)

if __name__ == "__main__":
    game = Reversi()
    game.play()
