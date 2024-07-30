import pygame
import sys

# Initialize Pygame
pygame.init()

# Game settings
N = 5  # Grid size
SQUARE_SIZE = 100
MARGIN = 2
WINDOW_SIZE = (N * (SQUARE_SIZE + MARGIN) + MARGIN, N * (SQUARE_SIZE + MARGIN) + MARGIN + 50)

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (128, 128, 128)

# Create window
screen = pygame.display.set_mode(WINDOW_SIZE)
pygame.display.set_caption("Square Flipping Game")

# Initialize grid (all black)
grid = [[0 for _ in range(N)] for _ in range(N)]

# Initialize move counter
moves = 0

def draw_grid():
    for row in range(N):
        for col in range(N):
            color = WHITE if grid[row][col] == 1 else BLACK
            pygame.draw.rect(screen, color,
                             [(MARGIN + SQUARE_SIZE) * col + MARGIN,
                              (MARGIN + SQUARE_SIZE) * row + MARGIN,
                              SQUARE_SIZE,
                              SQUARE_SIZE])

def flip_square(row, col):
    global moves
    moves += 1
    grid[row][col] = 1 - grid[row][col]
    for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        new_row, new_col = row + dr, col + dc
        if 0 <= new_row < N and 0 <= new_col < N:
            grid[new_row][new_col] = 1 - grid[new_row][new_col]

def is_game_won():
    return all(all(cell == 1 for cell in row) for row in grid)

def reset_game():
    global grid, moves
    grid = [[0 for _ in range(N)] for _ in range(N)]
    moves = 0

def main():
    global moves
    clock = pygame.time.Clock()
    font = pygame.font.Font(None, 36)

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                pos = pygame.mouse.get_pos()
                col = pos[0] // (SQUARE_SIZE + MARGIN)
                row = pos[1] // (SQUARE_SIZE + MARGIN)
                if row < N and col < N:
                    flip_square(row, col)
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_r:
                    reset_game()

        screen.fill(GRAY)
        draw_grid()

        # Display move counter
        text = font.render(f"Moves: {moves}", True, WHITE)
        screen.blit(text, (10, WINDOW_SIZE[1] - 40))

        if is_game_won():
            win_text = font.render("You Won! Press R to reset", True, WHITE)
            screen.blit(win_text, (WINDOW_SIZE[0]//2 - win_text.get_width()//2, WINDOW_SIZE[1] - 40))

        pygame.display.flip()
        clock.tick(60)

if __name__ == "__main__":
    main()