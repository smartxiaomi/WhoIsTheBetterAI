import tkinter as tk


class FlipGame:
    def __init__(self, root, size=5):
        self.root = root
        self.size = size
        self.board = [['B' for _ in range(size)] for _ in range(size)]
        self.grid_frame = tk.Frame(root)
        self.grid_frame.pack(padx=10, pady=10)

        self.create_board()

    def create_board(self):
        for i in range(self.size):
            for j in range(self.size):
                button = tk.Button(self.grid_frame, command=lambda i=i, j=j: self.flip_cell(i, j),
                                   bg='black', fg='white', width=4, height=2, relief='raised', borderwidth=2,
                                   highlightbackground='red')
                button.grid(row=i, column=j, padx=1, pady=1)

    def flip_cell(self, row, col):
        if 0 <= row < self.size and 0 <= col < self.size:
            self.flip_color(row, col)
            self.update_board()
            if self.check_win():
                self.show_win_message()

    def flip_color(self, row, col):
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        self.board[row][col] = 'W' if self.board[row][col] == 'B' else 'B'
        for dx, dy in directions:
            r, c = row + dx, col + dy
            if 0 <= r < self.size and 0 <= c < self.size:
                self.board[r][c] = 'W' if self.board[r][c] == 'B' else 'B'

    def update_board(self):
        for i in range(self.size):
            for j in range(self.size):
                widget = self.grid_frame.grid_slaves(row=i, column=j)[0]
                widget.config(bg='white' if self.board[i][j] == 'W' else 'black')

    def check_win(self):
        return all(cell == 'W' for row in self.board for cell in row)

    def show_win_message(self):
        messagebox = tk.messagebox.showinfo("Win!", "Congratulations! You've flipped all cells to white.")


def main():
    root = tk.Tk()
    root.title("Baidu Flip Game")
    game = FlipGame(root)
    root.mainloop()


if __name__ == "__main__":
    main()