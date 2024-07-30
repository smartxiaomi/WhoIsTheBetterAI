import pygame
import numpy as np

# 初始化 Pygame
pygame.init()

# 游戏设置
GRID_SIZE = 5  # N x N grid
SQUARE_SIZE = 50
WIDTH, HEIGHT = GRID_SIZE * SQUARE_SIZE, GRID_SIZE * SQUARE_SIZE
screen = pygame.display.set_mode((WIDTH, HEIGHT))  # 使用 screen 而不是 WINDOW
pygame.display.set_caption("方块翻转游戏")

# 颜色
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)  # 添加红色
# 游戏状态
grid = np.ones((GRID_SIZE, GRID_SIZE))  # 全部初始化为黑色 (1 表示黑色)

# 绘制方格
# 绘制方格
def draw_grid(screen, grid):
    for row in range(GRID_SIZE):
        for col in range(GRID_SIZE):
            color = WHITE if grid[row][col] == 0 else BLACK
            pygame.draw.rect(screen, color, (col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))
            # 绘制红色边框
            pygame.draw.rect(screen, RED, (col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE), 1)  # 1 表示边框宽度
# 翻转方格颜色
def flip_squares(grid, row, col):
    for x in range(max(0, row - 1), min(GRID_SIZE, row + 2)):
        for y in range(max(0, col - 1), min(GRID_SIZE, col + 2)):
            grid[x][y] = 1 - grid[x][y]

# 检查是否所有方格颜色相同 (是否全为白色)
def check_win(grid):
    return np.all(grid == 0)  # 检查是否所有元素都是 0 (白色)

# 主游戏循环
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.MOUSEBUTTONDOWN:
            x, y = event.pos
            row, col = y // SQUARE_SIZE, x // SQUARE_SIZE
            flip_squares(grid, row, col)

            if check_win(grid):
                print("Congratulations! You won!")
                running = False

    # 绘制游戏界面
    draw_grid(screen, grid)  # 使用 screen 而不是 WINDOW
    pygame.display.flip()  # 使用 flip() 更新整个屏幕

pygame.quit()
