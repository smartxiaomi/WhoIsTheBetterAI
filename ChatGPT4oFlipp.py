import tkinter as tk

class FlipGame:
    def __init__(self, root, size):
        self.root = root
        self.size = size
        self.grid = [[False] * size for _ in range(size)]
        self.buttons = [[None] * size for _ in range(size)]

        self.create_ui()

    def create_ui(self):
        for i in range(self.size):
            for j in range(self.size):
                button = tk.Button(self.root, bg='black', width=4, height=2,
                                   command=lambda i=i, j=j: self.flip(i, j))
                button.grid(row=i, column=j)
                self.buttons[i][j] = button

        reset_button = tk.Button(self.root, text="Reset", command=self.reset)
        reset_button.grid(row=self.size, column=0, columnspan=self.size)

    def flip(self, i, j):
        directions = [(0, 0), (0, 1), (0, -1), (1, 0), (-1, 0)]
        for di, dj in directions:
            ni, nj = i + di, j + dj
            if 0 <= ni < self.size and 0 <= nj < self.size:
                self.grid[ni][nj] = not self.grid[ni][nj]
                self.update_button_color(ni, nj)
        if self.check_win():
            self.show_win_message()

    def update_button_color(self, i, j):
        color = 'white' if self.grid[i][j] else 'black'
        self.buttons[i][j].config(bg=color)

    def reset(self):
        for i in range(self.size):
            for j in range(self.size):
                self.grid[i][j] = False
                self.update_button_color(i, j)

    def check_win(self):
        return all(all(row) for row in self.grid)

    def show_win_message(self):
        win_label = tk.Label(self.root, text="You win!", font=('Helvetica', 16))
        win_label.grid(row=self.size + 1, column=0, columnspan=self.size)

if __name__ == "__main__":
    root = tk.Tk()
    root.title("ChatGPT Flip Game")
    game = FlipGame(root, 5)
    root.mainloop()
