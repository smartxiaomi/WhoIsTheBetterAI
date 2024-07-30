import pygame
import random

# 初始化pygame
pygame.init()

# 设置窗口大小
WINDOW_SIZE = (640, 640)
SCREEN = pygame.display.set_mode(WINDOW_SIZE)
pygame.display.set_caption('方块翻转游戏')

# 颜色定义
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GRAY = (128, 128, 128)

# 方块设置
GRID_SIZE = 5  # 默认5x5的方格
SQUARE_SIZE = WINDOW_SIZE[0] // GRID_SIZE

# 游戏状态
game_over = False
board = [[BLACK for _ in range(GRID_SIZE)] for _ in range(GRID_SIZE)]

# 游戏循环
def game_loop():
    global game_over
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.MOUSEBUTTONDOWN and not game_over:
                handle_click(event.pos)

        SCREEN.fill(GRAY)
        draw_board()
        pygame.display.flip()

        if game_over:
            show_game_over_message()

        pygame.time.Clock().tick(60)

    pygame.quit()

def handle_click(pos):
    global game_over
    x, y = pos
    x, y = x // SQUARE_SIZE, y // SQUARE_SIZE
    if 0 <= x < GRID_SIZE and 0 <= y < GRID_SIZE:
        flip_squares(x, y)
        check_game_state()

def flip_squares(x, y):
    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1), (0, 0)]:
        nx, ny = x + dx, y + dy
        if 0 <= nx < GRID_SIZE and 0 <= ny < GRID_SIZE:
            board[ny][nx] = WHITE if board[ny][nx] == BLACK else BLACK

def check_game_state():
    global game_over
    if all(board[y][x] == WHITE for x in range(GRID_SIZE) for y in range(GRID_SIZE)):
        game_over = True

def draw_board():
    for y in range(GRID_SIZE):
        for x in range(GRID_SIZE):
            color = board[y][x]
            pygame.draw.rect(SCREEN, color, (x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))
            pygame.draw.rect(SCREEN, RED, (x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE), 1)

def show_game_over_message():
    font = pygame.font.Font(None, 36)
    text = font.render("Game Over! All squares are white.", True, WHITE)
    SCREEN.blit(text, (WINDOW_SIZE[0] / 2 - text.get_width() / 2, WINDOW_SIZE[1] / 2 - text.get_height() / 2))

if __name__ == "__main__":
    game_loop()