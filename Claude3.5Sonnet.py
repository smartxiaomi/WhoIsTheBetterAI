import pygame
import sys
import random

# Initialize Pygame
pygame.init()

# Define colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GREEN = (0, 128, 0)
GRAY = (128, 128, 128)

# Define board size
BOARD_SIZE = 8
SQUARE_SIZE = 60
WINDOW_SIZE = (BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE + 40)

# Create window
screen = pygame.display.set_mode(WINDOW_SIZE)
pygame.display.set_caption("Claude3.5Sonnet Reversi")

# Define board
board = [[0 for _ in range(BOARD_SIZE)] for _ in range(BOARD_SIZE)]

# Initialize board
board[3][3] = board[4][4] = 1  # White
board[3][4] = board[4][3] = 2  # Black

# Define directions
directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]


def draw_board():
    screen.fill(GREEN)
    for i in range(BOARD_SIZE):
        for j in range(BOARD_SIZE):
            pygame.draw.rect(screen, BLACK, (i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE), 1)
            if board[i][j] == 1:
                pygame.draw.circle(screen, WHITE,
                                   (i * SQUARE_SIZE + SQUARE_SIZE // 2, j * SQUARE_SIZE + SQUARE_SIZE // 2),
                                   SQUARE_SIZE // 2 - 2)
            elif board[i][j] == 2:
                pygame.draw.circle(screen, BLACK,
                                   (i * SQUARE_SIZE + SQUARE_SIZE // 2, j * SQUARE_SIZE + SQUARE_SIZE // 2),
                                   SQUARE_SIZE // 2 - 2)


def is_valid_move(x, y, player):
    if board[x][y] != 0:
        return False
    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 0 <= nx < BOARD_SIZE and 0 <= ny < BOARD_SIZE and board[nx][ny] == 3 - player:
            while 0 <= nx < BOARD_SIZE and 0 <= ny < BOARD_SIZE and board[nx][ny] == 3 - player:
                nx += dx
                ny += dy
            if 0 <= nx < BOARD_SIZE and 0 <= ny < BOARD_SIZE and board[nx][ny] == player:
                return True
    return False


def make_move(x, y, player):
    board[x][y] = player
    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        to_flip = []
        while 0 <= nx < BOARD_SIZE and 0 <= ny < BOARD_SIZE and board[nx][ny] == 3 - player:
            to_flip.append((nx, ny))
            nx += dx
            ny += dy
        if 0 <= nx < BOARD_SIZE and 0 <= ny < BOARD_SIZE and board[nx][ny] == player:
            for fx, fy in to_flip:
                board[fx][fy] = player


def get_valid_moves(player):
    return [(x, y) for x in range(BOARD_SIZE) for y in range(BOARD_SIZE) if is_valid_move(x, y, player)]


def count_pieces():
    white = sum(row.count(1) for row in board)
    black = sum(row.count(2) for row in board)
    return white, black


def ai_move():
    valid_moves = get_valid_moves(1)
    if valid_moves:
        return random.choice(valid_moves)
    return None


def game_over():
    return not (get_valid_moves(1) or get_valid_moves(2))


def main():
    player = 2  # Human player is black
    game_end = False
    clock = pygame.time.Clock()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            if not game_end and event.type == pygame.MOUSEBUTTONDOWN and player == 2:
                x, y = event.pos[0] // SQUARE_SIZE, event.pos[1] // SQUARE_SIZE
                if is_valid_move(x, y, player):
                    make_move(x, y, player)
                    player = 3 - player

        if not game_end and player == 1:
            move = ai_move()
            if move:
                make_move(*move, player)
                player = 3 - player
            else:
                player = 3 - player

        if not get_valid_moves(player):
            player = 3 - player

        draw_board()
        white_count, black_count = count_pieces()
        font = pygame.font.Font(None, 36)
        text = font.render(f"Human: {black_count}  Claude3.5 Sonnet: {white_count}", True, WHITE)
        screen.blit(text, (10, WINDOW_SIZE[1] - 30))

        if game_over():
            game_end = True
            if white_count > black_count:
                winner = "Ali"
            elif black_count > white_count:
                winner = "Human"
            else:
                winner = "Tie"
            text = font.render(f"Game Over! {winner} wins!", True, WHITE)
            screen.blit(text,
                        (WINDOW_SIZE[0] // 2 - text.get_width() // 2, WINDOW_SIZE[1] // 2 - text.get_height() // 2))

        pygame.display.flip()
        clock.tick(30)


if __name__ == "__main__":
    main()