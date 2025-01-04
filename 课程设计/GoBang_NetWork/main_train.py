import os
import torch
import torch.backends.cudnn as cudnn
import torch.nn as nn
import torch.optim as optim
from data import Dataset_Pro
from model import NetWork,summaries
import numpy as np

import shutil
from torch.utils.tensorboard import SummaryWriter

SEED = 1
torch.manual_seed(SEED)
torch.cuda.manual_seed(SEED)
torch.cuda.manual_seed_all(SEED)
# cudnn.benchmark = True  ###自动寻找最优算法
cudnn.deterministic = True
cudnn.benchmark = False


lr = 0.001  #学习率
epochs = 50
ckpt = 50
batch_size = 32
model_path = "Weights/test.pth"

model = NetWork().cpu()
summaries(model, grad=True)    ## Summary the Network
criterion = nn.MSELoss(size_average=True).cuda()  ## Define the Loss function L2Loss

optimizer = optim.Adam(model.parameters(), lr=lr, weight_decay=0)   ## optimizer 1: Adam

writer = SummaryWriter('./train_logs/50')    ## Tensorboard_show: case 2

def save_checkpoint(model):  # save model function
    model_out_path = "Weights/test.pth"
    torch.save(model.state_dict(), model_out_path)
    print('NetWork is Successfully saved in %s' % (model_out_path))



def train(training_data_loader,start_epoch=0):
    print('Start training...')
    model.train()
    for pre,gt in dataloader:
        
        pre = pre.unsqueeze(1)  # 添加通道维度
        gt = gt.unsqueeze(1)    # 添加通道维度
        
        optimizer.zero_grad()  
        sr = model(pre) 
        loss = criterion(sr, gt)  
        loss.backward()   
        optimizer.step()  
        break
    t_loss = np.nanmean(np.array(loss.item()))  
    writer.add_scalar('mse_loss/t_loss', t_loss) 
    save_checkpoint(model)
    writer.close() 

if __name__ == "__main__":
    if os.path.isfile(model_path):
        model.load_state_dict(torch.load(model_path))   ## Load the pretrained Encoder
        print('NetWork is Successfully Loaded from %s' % (model_path))

    for i in range(50):
        dataset = Dataset_Pro(f'training_data/data_{i+1}.h5')
        dataloader = torch.utils.data.DataLoader(dataset, batch_size=4, shuffle=True)
        print(f"start {i+1}time training...")
        train(dataloader)  