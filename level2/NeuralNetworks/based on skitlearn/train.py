import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.metrics import ConfusionMatrixDisplay
from sklearn import datasets, svm, metrics
from sklearn.model_selection import train_test_split
import pickle

digits = datasets.load_digits()     #导入数据

n_samples = len(digits.images)      #记录总样本个数
data = digits.images.reshape((n_samples, -1))   #将所有的图像转化为二维数组存入data

classifier = svm.SVC(gamma=0.001)   #数学模型，gamma为高斯核参数的宽度，此处宽度大，说明关注全局

X_train, X_test, y_train, y_test = train_test_split(
    data,           #刚刚的图像数组呀
    digits.target,  #给出图片对应正确数字
    test_size=0.5,  #定义测试集占总数居的比例，此处为50%
    shuffle=False   #shuffle老朋友了，随机洗牌数据为false
)

classifier.fit(X_train, y_train)    #一句话训练qwq

with open('classifier.pkl','wb') as f:
    pickle.dump(classifier,f)     #保存训练的classifier
