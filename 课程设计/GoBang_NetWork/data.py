import torch.utils.data as data
import torch
import h5py
import numpy as np

class Dataset_Pro(data.Dataset):
    def __init__(self, file_path):
        super(Dataset_Pro, self).__init__()
        with h5py.File(file_path, 'r') as f:
            self.pre = f["pre"][...]  # 加载预处理数据
            self.gt = f["gt"][...]    # 加载标签数据

    def __getitem__(self, index):
        pre = self.pre[index]
        gt = self.gt[index]
        return torch.tensor(pre, dtype=torch.float32), torch.tensor(gt, dtype=torch.float32)

    def __len__(self):
        return self.gt.shape[0]
