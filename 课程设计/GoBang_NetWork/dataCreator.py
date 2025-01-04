from gobang_logic import ChessBoard
import numpy as np
import h5py
import torch
import os

results = [
    0, 5, 5, 80, 5, 60, 100, 500, 5, 20, 80, 500, 100, 500, 8000, 200000, 5, 10,
    20, 600, 50, 600, 500, 8000, 80, 600, 500, 6000, 500, 8000, 200000, 10000000
]

def evaluate_board(board, color, bias = 1):
        score = 0
        directions = [(0, 1), (1, 0), (1, 1), (1, -1)]

        for direction in directions:
            for i in range(len(board)):
                for j in range(len(board)):
                    is_only = True
                    k = 0
                    chess_list = 0
                    px, py = i, j

                    while k < 5 and 0 < px < len(board)-1 and 0 < py < len(board)-1 and board[px, py] == 0:
                        py += direction[1]
                        px += direction[0]
                        k += 1

                    now_color = board[px, py]  

                    while k < 5 and is_only and (0 <= px < len(board) and 0 <= py < len(board)):
                        if now_color == -board[px, py]: 
                            is_only = False
                        chess_list = chess_list * 2 + (0 if board[px, py] == 0 else 1)  # 使用元组 (px, py) 访问棋盘
                        py += direction[1]
                        px += direction[0]
                        k += 1

                    if k == 5 and is_only:
                        score += results[chess_list] * (now_color * color) * (1 if now_color == color else bias)

        return score
def alphabeta(board: ChessBoard, depth: int, alpha: int, beta: int, maximizing_player: bool, color: int) -> int:
    is_over, winner = board.is_game_over()
    if depth == 0 or is_over:
        return evaluate_board(board, color)

    if maximizing_player:
        max_eval = -0
        for action in board.available_actions():
            board_copy = board.copy()
            board_copy.do_action(action)
            eval = alphabeta(board_copy, depth - 1, alpha, beta, False, color)
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:
                break
        return max_eval
    else:
        min_eval = 0
        for action in board.available_actions():
            board_copy = board.copy()
            board_copy.do_action(action)
            eval = alphabeta(board_copy, depth - 1, alpha, beta, True, color)
            min_eval = min(min_eval, eval)
            beta = min(beta, eval)
            if beta <= alpha:
                break
        return min_eval

def calculate_gt_board(chess_board: ChessBoard, depth: int, color: int) -> np.ndarray:
    GT_board = np.full((chess_board.board_size, chess_board.board_size), -0)
    #保存为GT用于卷积深度学习
    for action in chess_board.available_actions():
        board_copy = chess_board.copy()
        board_copy.do_action(action)
        score = alphabeta(board_copy, depth - 1, -0, 0, False, color)
        x, y = action
        GT_board[x, y] = score

    return GT_board

def create_random_board(board_size: int) -> ChessBoard:
    chess_board = ChessBoard(board_size)
    num_moves = np.random.randint(1, board_size * board_size // 2)
    for _ in range(num_moves):
        available_actions = chess_board.available_actions()
        if not available_actions:
            break
        action = available_actions[np.random.randint(len(available_actions))]
        chess_board.do_action(action)
    return chess_board

def save_to_h5(filename: str, pre: np.ndarray, gt: np.ndarray):
    with h5py.File(filename, 'w') as f:
        f.create_dataset('pre', data=pre)
        f.create_dataset('gt', data=gt)

if __name__ == "__main__":
    board_size = 10
    chess_board = create_random_board(board_size)
    depth = 1  # 深度，方便快速获取数据就使用1层，很可能...这个alphabeta是有问题的
    color = 1  # 1 for black, -1 for white

    bias = 1.0

    os.makedirs('training_data', exist_ok=True)

    for i in range(1, 51):
        chess_board = create_random_board(board_size)
        GT_board = calculate_gt_board(chess_board, depth, color)

        # 将棋盘状态和评估结果转换为 Tensor 格式
        pre = torch.tensor(chess_board.board, dtype=torch.float32).unsqueeze(0)  # 添加批次维度
        gt = torch.tensor(GT_board, dtype=torch.float32).unsqueeze(0)  # 添加批次维度
        
        gt = (gt - gt.min()) / (gt.max() - gt.min())
        gt = torch.round(gt * 100) / 100
        print(f"pre: {pre}")
        print(f"gt: {gt}")
        # 保存到 HDF5 文件
        filename = f'training_data/data_{i}.h5'
        save_to_h5(filename, pre.numpy(), gt.numpy())
        print(f"Saved {filename}")
