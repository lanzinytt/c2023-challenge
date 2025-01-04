import numpy as np
from typing import List, Tuple

class ChessBoard:
    def __init__(self, board_size: int):
        self.board_size = board_size
        self.board = np.zeros((board_size, board_size), dtype=int)
        self.current_player = 1  # 1 for black, -1 for white

    def __len__(self):
        return self.board_size

    def __getitem__(self, index: Tuple[int, int]) -> int:
        x, y = index
        return self.board[x, y]

    def copy(self):
        new_board = ChessBoard(self.board_size)
        new_board.board = self.board.copy()
        new_board.current_player = self.current_player
        return new_board

    def do_action(self, action: Tuple[int, int]):
        x, y = action
        self.board[x, y] = self.current_player
        self.current_player = -self.current_player

    def available_actions(self) -> List[Tuple[int, int]]:
        return [(x, y) for x in range(self.board_size) for y in range(self.board_size) if self.board[x, y] == 0]

    def is_game_over(self) -> Tuple[bool, int]:
        for x in range(self.board_size):
            for y in range(self.board_size):
                if self.board[x, y] != 0:
                    if self.check_five_in_a_row(x, y):
                        return True, self.board[x, y]

        if not any(0 in row for row in self.board):
            return True, 0

        return False, None

    def check_five_in_a_row(self, x: int, y: int) -> bool:
        directions = [(1, 0), (0, 1), (1, 1), (1, -1)]
        for dx, dy in directions:
            count = 1
            for step in range(1, 5):
                nx, ny = x + step * dx, y + step * dy
                if 0 <= nx < self.board_size and 0 <= ny < self.board_size and self.board[nx, ny] == self.board[x, y]:
                    count += 1
                else:
                    break
            for step in range(1, 5):
                nx, ny = x - step * dx, y - step * dy
                if 0 <= nx < self.board_size and 0 <= ny < self.board_size and self.board[nx, ny] == self.board[x, y]:
                    count += 1
                else:
                    break
            if count >= 5:
                return True
        return False


'''  #蒙特卡洛树太赌狗，计算量打的同时还不稳定，虽然在大计算量下更能得到最优解，但是这里不选择
def mcts(chess_board: ChessBoard, n_iters: int, color: int) -> List[Tuple[Tuple[int, int], int]]:
    action_scores = []

    for action in chess_board.available_actions():
        total_score = 0

        for _ in range(n_iters):
            board_copy = chess_board.copy()
            board_copy.do_action(action)

            # Simulate random play until the game is over
            while not board_copy.is_game_over()[0]:
                available_actions = board_copy.available_actions()
                random_action = available_actions[np.random.randint(len(available_actions))]
                board_copy.do_action(random_action)

            # Evaluate the final board state
            score = evaluate_board(board_copy, color)
            total_score += score

        average_score = total_score / n_iters
        action_scores.append((action, average_score))

    return action_scores
'''

