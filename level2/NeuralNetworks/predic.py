import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.metrics import ConfusionMatrixDisplay
from sklearn import datasets, svm, metrics
from sklearn.model_selection import train_test_split
import pickle

digits = datasets.load_digits()     #导入数据

_, axes = plt.subplots(2, 4)        #预选展示数据
images_and_labels = list(zip(digits.images, digits.target))     #列表存储图片与对应正确数字
for ax, (image, label) in zip(axes[0, :], images_and_labels[:4]):   #for循环，展示四个数据，运用到plt
    ax.set_axis_off()
    ax.imshow(image, cmap=plt.cm.gray_r, interpolation='nearest')
    ax.set_title('Training: %i' % label)

n_samples = len(digits.images)      #记录总样本个数
data = digits.images.reshape((n_samples, -1))   #将所有的图像转化为二维数组存入data


X_train, X_test, y_train, y_test = train_test_split(
    data,           #刚刚的图像数组呀
    digits.target,  #给出图片对应正确数字
    test_size=0.5,  #定义测试集占总数居的比例，此处为50%
    shuffle=False   #shuffle老朋友了，随机洗牌数据为false
)

with open('classifier.pkl','rb') as f:
    classifier = pickle.load(f)     #加载训练好的模型
    
predicted = classifier.predict(X_test)  #一句话用训练完的模型预测测试集，太酷啦

images_and_predictions = list(zip(digits.images[n_samples // 2:], predicted))   #图片与预测结果结合
for ax, (image, prediction) in zip(axes[1, :], images_and_predictions[:4]):     #展示四个，和上面那个差不多
    ax.set_axis_off()
    ax.imshow(image, cmap=plt.cm.gray_r, interpolation='nearest')
    ax.set_title('Prediction: %i' % prediction)

print("Classification report for classifier %s:\n%s\n"  #给个小标题( •̀ ω •́ )y
      % (classifier, metrics.classification_report(y_test, predicted)))

cm = confusion_matrix(y_test, predicted)    #库里给的结果预测展示，真是太好用辣
disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=digits.target_names)
disp.plot(cmap=plt.cm.Blues)
plt.title("Confusion Matrix")
plt.show()      #plt显示（