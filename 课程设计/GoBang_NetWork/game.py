import torch
import torch.nn as nn
import numpy as np
from model import NetWork

def load_model(model_path):
    model = NetWork()
    model.load_state_dict(torch.load(model_path))
    model.eval()
    return model

def get_action(model, chess_board):
    # 将棋盘状态转换为模型输入格式
    input_tensor = torch.tensor(chess_board, dtype=torch.float32).unsqueeze(0).unsqueeze(0)  # 1x1x10x10

    # 使用模型进行预测
    with torch.no_grad():
        output_tensor = model(input_tensor)

    # 获取预测结果
    output_array = output_tensor.squeeze().numpy()  # 10x10

    # 根据预测结果选择最佳动作
    best_action = np.unravel_index(np.argmax(output_array), output_array.shape)
    return best_action

def update_board(chess_board, action, player):
    x, y = action
    chess_board[x, y] = player
    return chess_board

# 示例用法
if __name__ == "__main__":
    model_path = "Weights/test.pth"
    model = load_model(model_path)

    # 初始化棋盘状态
    board_size = 10
    chess_board = np.zeros((board_size, board_size), dtype=int)

    # 模拟游戏过程
    current_player = 1  # 1 for black, -1 for white
    for _ in range(board_size * board_size):
        action = get_action(model, chess_board)
        chess_board = update_board(chess_board, action, current_player)
        print(f"Player {current_player} moves to {action}")
        print(chess_board)

        # 切换玩家
        current_player = -current_player