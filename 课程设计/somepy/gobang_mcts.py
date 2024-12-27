import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.utils.data import DataLoader, Dataset

class Gobang:#五子棋基本逻辑
    def __init__(self, size=9):#为了减少训练量将棋盘改为9*9
        self.size = size
        self.board = np.zeros((size, size), dtype=int)
        self.current_player = 1
        self.last_move = None

    def reset(self):#清空棋盘
        self.board = np.zeros((self.size, self.size), dtype=int)
        self.current_player = 1
        self.last_move = None

    def is_valid_move(self, x, y):#落子合法性
        return 0 <= x < self.size and 0 <= y < self.size and self.board[x, y] == 0

    def make_move(self, x, y):
        if self.is_valid_move(x, y):
            self.board[x, y] = self.current_player
            self.last_move = (x, y)
            if self.check_win(x, y):
                return f'Player {self.current_player} wins!'
            self.current_player = 3 - self.current_player
            return 'Move made'
        else:
            return 'Invalid move'

    def check_win(self, x, y):
        def count_stones(dx, dy):
            count = 0
            for i in range(1, 5):
                nx, ny = x + i * dx, y + i * dy
                if 0 <= nx < self.size and 0 <= ny < self.size and self.board[nx, ny] == self.current_player:
                    count += 1
                else:
                    break
            for i in range(1, 5):
                nx, ny = x - i * dx, y - i * dy
                if 0 <= nx < self.size and 0 <= ny < self.size and self.board[nx, ny] == self.current_player:
                    count += 1
                else:
                    break
            return count

        directions = [(1, 0), (0, 1), (1, 1), (1, -1)]
        for dx, dy in directions:
            if count_stones(dx, dy) >= 4:
                return True
        return False

class GobangDataset(Dataset):
    def __init__(self, data, labels):
        self.data = data
        self.labels = labels

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        return self.data[idx], self.labels[idx]

class GobangCNN(nn.Module):
    def __init__(self):
        super(GobangCNN, self).__init__()
        self.conv1 = nn.Conv2d(in_channels=1, out_channels=32, kernel_size=3, padding=1)
        self.conv2 = nn.Conv2d(in_channels=32, out_channels=64, kernel_size=3, padding=1)
        self.conv3 = nn.Conv2d(in_channels=64, out_channels=128, kernel_size=3, padding=1)
        self.fc1 = nn.Linear(128 * 1 * 1, 512)
        self.fc2 = nn.Linear(512, 1)

    def forward(self, x):
        x = F.relu(self.conv1(x))
        x = F.max_pool2d(x, 2)
        x = F.relu(self.conv2(x))
        x = F.max_pool2d(x, 2)
        x = F.relu(self.conv3(x))
        x = F.max_pool2d(x, 2)
        x = x.view(x.size(0), -1)
        x = F.relu(self.fc1(x))
        x = torch.sigmoid(self.fc2(x))
        return x

class MCTSNode:
    def __init__(self, state, parent=None):
        self.state = state
        self.parent = parent
        self.children = []
        self.visits = 0
        self.wins = 0
        
def mcts_search(root, model, iterations=100):
    for _ in range(iterations):
        node = root
        while node.children:
            node = max(node.children, key=lambda n: (n.wins / n.visits + np.sqrt(2 * np.log(node.visits) / n.visits)) if n.visits > 0 else float('inf'))
        if node.visits == 0:
            result = simulate(node.state, model)
            backpropagate(node, result)
        else:
            expand(node)
    return max(root.children, key=lambda n: n.visits).state

def simulate(state,model):#激活函数
    game = Gobang()
    game.board = state.board.copy()
    game.current_player = state.current_player
    while True:
        moves = [(x, y) for x in range(game.size) for y in range(game.size) if game.is_valid_move(x, y)]
        if not moves:
            return 0.5  
        move = moves[np.random.randint(len(moves))]
        result = game.make_move(*move)
        if result != 'Move made':
            return 1 if '1' in result else 0
        # 使用模型评估当前棋盘状态
        board_tensor = torch.tensor(game.board, dtype=torch.float32).unsqueeze(0).unsqueeze(0)
        score = model(board_tensor).item()
        if score > 0.5:
            return 1
        else:
            return 0

def expand(node):
    game = Gobang()
    game.board = node.state.board.copy()
    game.current_player = node.state.current_player
    for x in range(game.size):
        for y in range(game.size):
            if game.is_valid_move(x, y):
                new_state = Gobang()
                new_state.board = game.board.copy()
                new_state.current_player = game.current_player
                new_state.make_move(x, y)
                node.children.append(MCTSNode(new_state, node))

def backpropagate(node, result):#反向修改树值
    while node:
        node.visits += 1
        node.wins += result
        node = node.parent

def generate_training_data(game, model, num_samples=10):
    data = []
    labels = []
    for _ in range(num_samples):
        game.reset()
        while True:
            root = MCTSNode(game)
            best_state = mcts_search(root, model)
            data.append(game.board.copy())
            labels.append(best_state.board.copy())
            if game.last_move and game.check_win(*game.last_move):
                break
    return np.array(data), np.array(labels)

game = Gobang()

model = GobangCNN()
model_path = 'gobang_cnn.pth'
try:
    model.load_state_dict(torch.load(model_path, weights_only=True))
    print('Model loaded.')
except FileNotFoundError:
    print('No pre-trained model found.')
    pass
except Exception as e:
    pass
    
data, labels = generate_training_data(game,model)
data = torch.tensor(data, dtype=torch.float32).unsqueeze(1)
labels = torch.tensor(labels, dtype=torch.float32).unsqueeze(1)
dataset = GobangDataset(data, labels)
dataloader = DataLoader(dataset, batch_size=10, shuffle=True)

criterion = nn.BCELoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

num_epochs = 3
for epoch in range(num_epochs):
    model.train()
    for inputs, targets in dataloader:
        optimizer.zero_grad()
        outputs = model(inputs)
        loss = criterion(outputs, targets)
        loss.backward()
        optimizer.step()
    print(f'Epoch {epoch+1}/{num_epochs}, Loss: {loss.item()}')
torch.save(model.state_dict(), 'gobang_cnn.pth')
print('Model saved.')
print('Finish.')