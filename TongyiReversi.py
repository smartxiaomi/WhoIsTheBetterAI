import pygame
import random

# 初始化pygame
pygame.init()

# 设置窗口大小
WINDOW_SIZE = (640, 640)
SCREEN = pygame.display.set_mode(WINDOW_SIZE)
pygame.display.set_caption('Tongyi Qianwen Reversi')

# 颜色定义
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GRAY = (128, 128, 128)
BOARD_BACKGROUND_COLOR = (0, 128, 0)  # 深绿色
# 棋盘设置
BOARD_SIZE = 8
SQUARE_SIZE = WINDOW_SIZE[0] // BOARD_SIZE

# 加载字体
FONT = pygame.font.Font(None, 36)

# 定义棋子类型
EMPTY = 0
BLACK_PIECE = 1
WHITE_PIECE = 2

class Reversi:
    def __init__(self):
        self.board = [[0] * BOARD_SIZE for _ in range(BOARD_SIZE)]
        self.board[3][3], self.board[4][4] = WHITE_PIECE, WHITE_PIECE
        self.board[3][4], self.board[4][3] = BLACK_PIECE, BLACK_PIECE
        self.current_player = BLACK_PIECE
        self.opponent = {BLACK_PIECE: WHITE_PIECE, WHITE_PIECE: BLACK_PIECE}
        self.display()

    def draw_board(self):
        SCREEN.fill(BOARD_BACKGROUND_COLOR)
        for y in range(BOARD_SIZE):
            for x in range(BOARD_SIZE):
                pygame.draw.rect(SCREEN, GRAY, (x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE), 1)
                if self.board[y][x] == BLACK_PIECE:
                    pygame.draw.circle(SCREEN, BLACK, (x * SQUARE_SIZE + SQUARE_SIZE // 2, y * SQUARE_SIZE + SQUARE_SIZE // 2), SQUARE_SIZE // 2 - 5)
                elif self.board[y][x] == WHITE_PIECE:
                    pygame.draw.circle(SCREEN, WHITE, (x * SQUARE_SIZE + SQUARE_SIZE // 2, y * SQUARE_SIZE + SQUARE_SIZE // 2), SQUARE_SIZE // 2 - 5)

    def display(self):
        self.draw_board()
        pygame.display.flip()

    def is_valid_move(self, x, y):
        if not (0 <= x < BOARD_SIZE and 0 <= y < BOARD_SIZE) or self.board[y][x] != EMPTY:
            return False
        to_flip = []
        directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        for dx, dy in directions:
            temp_x, temp_y = x + dx, y + dy
            flips = []
            while 0 <= temp_x < BOARD_SIZE and 0 <= temp_y < BOARD_SIZE:
                if self.board[temp_y][temp_x] == 0:
                    break
                elif self.board[temp_y][temp_x] == self.current_player:
                    if flips:
                        to_flip.extend(flips)
                    break
                else:
                    flips.append((temp_x, temp_y))
                    temp_x += dx
                    temp_y += dy
        if len(to_flip) > 0:
            return to_flip
        return False

    def make_move(self, x, y):
        to_flip = self.is_valid_move(x, y)
        if to_flip:
            self.board[y][x] = self.current_player
            for x_flip, y_flip in to_flip:
                self.board[y_flip][x_flip] = self.current_player
            self.current_player = self.opponent[self.current_player]
            return True
        return False

    def has_possible_moves(self):
        for y in range(BOARD_SIZE):
            for x in range(BOARD_SIZE):
                if self.is_valid_move(x, y):
                    return True
        return False

    def play_human(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    quit()
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    x, y = pygame.mouse.get_pos()
                    x, y = x // SQUARE_SIZE, y // SQUARE_SIZE
                    if self.make_move(x, y):
                        break
            if self.has_possible_moves():
                break
            self.display()

    def play_ai(self):
        best_move = None
        max_flips = 0
        for y in range(BOARD_SIZE):
            for x in range(BOARD_SIZE):
                flips = self.is_valid_move(x, y)
                if flips and len(flips) > max_flips:
                    best_move = (x, y)
                    max_flips = len(flips)
        if best_move:
            self.make_move(*best_move)

    def show_score(self):
        black = sum(row.count(BLACK_PIECE) for row in self.board)
        white = sum(row.count(WHITE_PIECE) for row in self.board)
        text = FONT.render(f"Score: Black {black} - TongyiQianwen {white}", True, WHITE)
        SCREEN.blit(text, (10, 10))
        pygame.display.update()

def main():
    game = Reversi()
    clock = pygame.time.Clock()
    while True:
        game.display()
        game.show_score()
        if not game.has_possible_moves():
            break
        if game.current_player == BLACK_PIECE:  # Human player (Black)
            game.play_human()
        else:  # AI player (White)
            print("AI Tongyiqianwen's turn...")
            game.play_ai()
        clock.tick(60)

    game.display()
    black = sum(row.count(BLACK_PIECE) for row in game.board)
    white = sum(row.count(WHITE_PIECE) for row in game.board)
    if black > white:
        print("Human wins!")
    elif white > black:
        print("AI Tongyiqianwen wins!")
    else:
        print("It's a tie!")
    pygame.quit()

if __name__ == "__main__":
    main()