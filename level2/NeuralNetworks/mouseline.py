
#取材https://blog.csdn.net/lidashent/article/details/106929578
#错是我故意加的，请注意
"""
使用百度api进行手写识别
每次启动获取一次tocken,然后tocken用来进行发送截图,返回结果

有一个截图程序
先生成一个0.3透明度的敞口,然后使用canvas画实时的矩形,在矩形结束点设置隐藏的按钮显示
确认截图后会调用手写识别功能,然后调用主界面的函数,将结果表现在主界面

主界面就是几个按钮,不过有容错机制,可以恢复上一步信息,对于空不恢复
复制会将内容复制到粘贴板

"""
# encoding:utf-8
import glob
import os
import tkinter as tk
from ctypes import windll

import pyautogui
import requests
import base64
import datetime
import json
import tkinter as tk

import win32con
import win32gui
import win32ui
from PIL import ImageGrab, ImageTk
import numpy as np
from PIL import Image
import pyperclip
from skimage.viewer.utils import canvas
import cv2
import easyocr
from tkinterdnd2 import DND_FILES, TkinterDnD
import winreg as reg
"""启动主程序"""

'''
手写文字识别函数
'''
def showLog(txt):
    # print(txt)
    pass
class picToTxt:
    def gettocken(self):
    #自己去百度申请手写识别pid
        Pid=""
        Psc=""
        url = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id={}&clien" \
              "t_secret={}".format(Pid,Psc)
        # print(url)

        payload = ""
        headers = {
            'Content-Type': 'application/json',
            'Accept': 'application/json'
        }

        response = requests.request("POST", url, headers=headers, data=payload)
        data = json.loads(response.text)
        return data["access_token"]
    def picToword(self,picPath,access_token):
        request_url = "https://aip.baidubce.com/rest/2.0/ocr/v1/handwriting"
        showLog(picPath)
        localPic=picPath
        # 二进制方式打开图片文件
        f = open(localPic, 'rb')
        img = base64.b64encode(f.read())

        params = {"image":img}

        request_url = request_url + "?access_token=" + access_token
        headers = {'content-type': 'application/x-www-form-urlencoded'}
        response = requests.post(request_url, data=params, headers=headers)
        handWord = []
        if response:
            # print (response.json())
            test=response.json()["words_result"]
            for i in test:
                handWord.append(i["words"])
        return handWord
    def picOcrToword(self,img_path):
        reader = easyocr.Reader(['ch_sim', 'en'])
        # 读取图像
        result = reader.readtext(img_path)
        # 结果123
        # print(result)
        allcontent = []
        for i in result:
            # print(i)
            allcontent.append(i[1])
        return allcontent
#     根据窗口句柄来截图



# 记录手写笔迹的函数
class HandDrawingApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title('手写绘制线条')
        self.geometry('1100x700+0+0')
        # self.attributes('-topmost', True)
        self.canvas = tk.Canvas(self, bg='white')
        self.canvas.pack(fill=tk.BOTH, expand=True)

        self.start_point = None
        self.drawing = False

        self.canvas.bind('<ButtonPress-1>', self.start_drawing)
        self.canvas.bind('<B1-Motion>', self.draw)
        self.canvas.bind('<ButtonRelease-1>', self.stop_drawing)

    def start_drawing(self, event):
        self.start_point = (event.x, event.y)
        self.drawing = True

    def clear_canvas(self):
        # 清除画布上的所有内容
        self.canvas.delete("all")
        # 重置绘图状态
        self.start_point = None
        self.drawing = False
    def draw(self, event):
        if not self.drawing:
            return

        self.canvas.create_line(self.start_point[0], self.start_point[1], event.x, event.y, width=2)
        self.start_point = (event.x, event.y)

    def stop_drawing(self, event):
        self.drawing = False
    #
    # def getCaptureScreen(self,picPath):
    #     x1, y1 = 0, 0
    #     x2, y2 = self.canvas.winfo_width(), self.canvas.winfo_height()
    #     img_np = np.array(ImageGrab.grab())
    #     newImg = img_np[y1:y2, x1:x2]
    #     pil_image = Image.fromarray(newImg)
    #     # 保存图像为PNG文件
    #     pil_image.save(picPath)
    def showWin(self):
        self.deiconify()  # 显示窗口
        self.attributes('-toolwindow', False)  # 重置窗口属性

    def hideWin(self):
        self.attributes('-toolwindow', True)
        self.withdraw()  # 隐藏窗口

    def run(self):

        self.mainloop()
"""
开发一个界面,
用于识别手写文字
"""
# 时间函数,用于为图像文件命名
def getNowTime():
    # 获取当前时间
    current_time = datetime.datetime.now()

    # 格式化当前时间
    formatted_time = current_time.strftime("%Y-%m-%d-%H-%M-%S-")

    # 如果你需要毫秒部分作为单独的整数
    nowTime = formatted_time + str(int(current_time.microsecond / 1000))
    return nowTime
# 截图函数

class otherFun:
    def set_proxy(self,proxy_server, proxy_bypass=None,enableNet=0):
        # 打开注册表键
        key = reg.OpenKey(reg.HKEY_CURRENT_USER, r"Software\Microsoft\Windows\CurrentVersion\Internet Settings", 0,
                          reg.KEY_SET_VALUE)

        # 设置代理服务器
        reg.SetValueEx(key, "ProxyServer", 0, reg.REG_SZ, proxy_server)

        # 设置代理绕过列表（可选）
        if proxy_bypass:
            reg.SetValueEx(key, "ProxyOverride", 0, reg.REG_SZ, proxy_bypass)
        else:
            reg.DeleteValue(key, "ProxyOverride")

            # 启用代理
        reg.SetValueEx(key, "ProxyEnable", 0, reg.REG_DWORD, enableNet)

        # 关闭注册表键
        reg.CloseKey(key)
    def check_proxy(self):
        # 打开注册表键
        key_path = r"Software\Microsoft\Windows\CurrentVersion\Internet Settings"
        key = reg.OpenKey(reg.HKEY_CURRENT_USER, key_path, 0, reg.KEY_READ)

        # 读取ProxyEnable的值
        try:
            proxy_enable_value, regtype = reg.QueryValueEx(key, "ProxyEnable")
            # 如果读取成功，将值存储在proxy_enable_value变量中
            if proxy_enable_value == 1:
                return 1
            elif proxy_enable_value == 0:
                return 0
            else:
                return ""
                print("未知的代理状态")
        except FileNotFoundError:
            # 如果键或值不存在，将抛出此异常
            print("ProxyEnable值不存在")
        finally:
            # 关闭注册表键
            reg.CloseKey(key)
    def getAllFilePath(self,path):
        # 初始化文件路径列表
        file_paths = []
        # 检查路径是否存在
        if os.path.exists(path):
            # 检查路径是一个文件还是一个文件夹
            if os.path.isfile(path):
                # 如果是一个文件，直接添加到文件路径列表
                file_paths.append(path)
            elif os.path.isdir(path):
                # 如果是一个文件夹，递归获取所有文件路径
                for root, dirs, files in os.walk(path):
                    for file in files:
                        file_path = os.path.join(root, file)
                        file_paths.append(file_path)
        else:
            print(f"路径 '{path}' 不存在")
        allTxt=""
        for i in file_paths:
            allTxt+=i+"<>\n"

        return allTxt
    def middle_mouse_down(self):
        print("Mouse middle button pressed")
        pyautogui.mouseDown(button='middle')
    def middle_mouse_up(self):
        print("Mouse middle button released")
        pyautogui.mouseUp(button='middle')
    def save_hand(self,picPath):
        # 获取后台窗口的句柄，注意后台窗口不能最小化
        hWnd = win32gui.FindWindow("TkTopLevel", "手写绘制线条")  # 窗口的类名可以用Visual Studio的SPY++工具获取
        # 获取句柄窗口的大小信息
        left, top, right, bot = win32gui.GetWindowRect(hWnd)
        showLog(f"窗口位置: ({left}, {top}) - ({right}, {bot})")
        # 因为去掉了标题栏,所以获得的窗口需要偏移一下向下获取,宽高需要适当缩减来获得主体,否则会多获得
        offsetx=15
        offsety=40
        width = right - left-offsetx
        height = bot - top-offsety
        # 返回句柄窗口的设备环境，覆盖整个窗口，包括非客户区，标题栏，菜单，边框
        hWndDC = win32gui.GetWindowDC(hWnd)
        # 创建设备描述表
        mfcDC = win32ui.CreateDCFromHandle(hWndDC)
        # 创建内存设备描述表
        saveDC = mfcDC.CreateCompatibleDC()
        # 创建位图对象准备保存图片
        saveBitMap = win32ui.CreateBitmap()
        # 为bitmap开辟存储空间
        saveBitMap.CreateCompatibleBitmap(mfcDC, width, height)
        # 将截图保存到saveBitMap中
        saveDC.SelectObject(saveBitMap)
        # 保存bitmap到内存设备描述表
        saveDC.BitBlt((0, 0), (width, height), mfcDC, (0, 0), win32con.SRCCOPY)

        # 如果要截图到打印设备：
        ###最后一个int参数：0-保存整个窗口，1-只保存客户区。如果PrintWindow成功函数返回值为1
        windll.user32.PrintWindow(hWnd, saveDC.GetSafeHdc(), 1)
        # 压缩图像
        # 将位图转换为Pillow图像对象
        bmpinfo = saveBitMap.GetInfo()
        bmpstr = saveBitMap.GetBitmapBits(True)
        img = Image.frombuffer(
            'RGB',
            (bmpinfo['bmWidth'], bmpinfo['bmHeight']),
            bmpstr, 'raw', 'BGRX', 0, 1)
        # 保存图像
        quality=90
        img.save(picPath, 'JPEG', quality=quality)
        # 清理资源
        win32gui.DeleteObject(saveBitMap.GetHandle())
        saveDC.DeleteDC()
        mfcDC.DeleteDC()
        win32gui.ReleaseDC(hWnd, hWndDC)
        # ##方法一：windows api保存
        # ###保存bitmap到文件
        # saveBitMap.SaveBitmapFile(saveDC, picPath)

class littleWin:
    def __init__(self):
       print("小窗口")
    def run(self):
        self.root = TkinterDnD.Tk()
        self.root.geometry("180x30")
        # 设置窗口透明度为50%
        self.root.attributes('-alpha', 0.9)
        # 使窗口固定在屏幕上的指定位置
        self.root.geometry("+{0}+{1}".format(1150, 150))  # 这将把窗口的左上角固定在屏幕上的(100, 100)位置
        self.root.attributes('-topmost', True)
        # 功能按钮
        self.buttonZoomIn = tk.Button(self.root, text="恢复", command=self.winZoomIn)
        self.buttonZoomIn.place(x=0, y=0, width=100, height=30)  # 第五个按钮跨两列，位置和大小
        self.root.mainloop()
    def destroy(self):
        self.root.destroy()
    def winZoomIn(self):
    #     恢复窗口,恢复所有部件
        littleWin.hideWin()

        app.showWin()
        app.run()

    def showWin(self):
        self.root.deiconify()  # 显示窗口
        self.root.attributes('-toolwindow', False)  # 重置窗口属性
    def hideWin(self):
        self.root.attributes('-toolwindow', True)
        self.root.withdraw()  # 隐藏窗口

littleWin=littleWin()
#主函数
class main:
    def __init__(self):
        self.root = TkinterDnD.Tk()
        self.root.geometry("350x600")
        # 设置窗口透明度为50%
        self.root.attributes('-alpha', 0.9)
        # 使窗口固定在屏幕上的指定位置
        self.root.geometry("+{0}+{1}".format(1000, 27))  # 这将把窗口的左上角固定在屏幕上的(100, 100)位置
        # 让窗口变得支持拖动显示路径
        self.root.drop_target_register(DND_FILES)
        self.root.dnd_bind('<<Drop>>', self.handle_drop)
        # 设置窗口始终在最前
        self.root.attributes('-topmost', True)
        self.status_label = tk.Label(self.root, text="手写识别程序状态...")

        self.buttonRecordTxt=tk.Button(self.root, text="计划格式", command=self.planTxtRecord)
        self.buttonWR = tk.Button(self.root, text="截图识别", command=self.writeRecongnize)
        self.buttonRE = tk.Button(self.root, text="恢复上一步", command=self.restorePrevious)
        self.buttonNW = tk.Button(self.root, text="查看当前步", command=self.nowWord)
        self.buttonCP = tk.Button(self.root, text="复制", command=self.copyText)
        self.buttonCL = tk.Button(self.root, text="清空", command=self.clearText)
        # 切换vpn
        self.buttonVPN = tk.Button(self.root, text="切换代理", command=self.changeVPN)
        self.buttonZoomOut = tk.Button(self.root, text="缩小主窗口", command=self.winZoomOut)
        # 手写画板按键区
        self.buttonPainterStatus = tk.Button(self.root, text="显示画板", command=self.changePainter)
        self.buttonPainterOcr= tk.Button(self.root, text="画板识别", command=self.writeOCR)
        self.buttonClearPainter= tk.Button(self.root, text="清空画板", command=self.clearPainter)
        self.buttonHidePainter= tk.Button(self.root, text="预留功能", command=self.HidePainter)

        # 添加标签
        # self.status_label.place(x=0, y=10, width=300, height=30)
        # self.status_label.place(x=0, y=10, relx=0, rely=0.033, width=300, height=30, anchor='nw')
        self.status_label.pack(side="top")

        # 将按钮添加到窗口中
        # 按钮上下40,左右120
        self.upDistance=30
        self.xDistance=10
        self.buttonRecordTxt.place(x=self.xDistance, y=self.upDistance, width=100, height=30)  # 第一个按钮的位置和大小
        self.buttonWR.place(x=self.xDistance, y=self.upDistance*2, width=100, height=30)  # 第一个按钮的位置和大小
        self.buttonRE.place(x=self.xDistance, y=self.upDistance*3, width=100, height=30)  # 第二个按钮的位置和大小
        self.buttonNW.place(x=self.xDistance, y=self.upDistance*4, width=100, height=30)  # 第三个按钮的位置和大小
        self.buttonCP.place(x=self.xDistance, y=self.upDistance*5,  width=100, height=30)  # 第四个按钮的位置和大小
        self.buttonCL.place(x=self.xDistance, y=self.upDistance*6,  width=100, height=30)  # 第五个按钮跨两列，位置和大小
        self.buttonVPN.place(x=self.xDistance, y=self.upDistance*7,  width=100, height=30)  # 第五个按钮跨两列，位置和大小
        self.buttonZoomOut.place(x=self.xDistance, y=self.upDistance*8,  width=100, height=30)  # 第五个按钮跨两列，位置和大小
        self.buttonPainterStatus.place(x=self.xDistance*12, y=self.upDistance*1,  width=100, height=30)
        self.buttonPainterOcr.place(x=self.xDistance*12, y=self.upDistance*2,  width=100, height=30)
        self.buttonClearPainter.place(x=self.xDistance*12, y=self.upDistance*3,  width=100, height=30)
        self.buttonHidePainter.place(x=self.xDistance*12, y=self.upDistance*4,  width=100, height=30)
        # 创建一个 Text 小部件
        self.text_widget = tk.Text(self.root, height=5, width=17)
        self.text_widget.place(x=self.xDistance, y=self.upDistance*9, width=320, height=300)   # 将 Text 小部件添加到窗口中

        # 初始化功能模块
        self.netC = otherFun()
    #    获取tocken,字符处理
        self.picT = picToTxt()

        self.hd = HandDrawingApp()
        self.lastWord=None
        self.nowHandWord=None
        self.picTocken=None
        self.vpnIP="10.9.9.235:8080"
        self.initProxy()
        self.initPainter()
    def initPainter(self):
        self.hd.hideWin()
    def changePainter(self):
        if self.buttonPainterStatus.cget('text') == "显示画板":
            self.hd.showWin()
            self.buttonPainterStatus.config(text="隐藏画板")
        elif self.buttonPainterStatus.cget('text') == "隐藏画板":
            self.hd.hideWin()
            self.buttonPainterStatus.config(text="显示画板")
        else:
            self.buttonPainterStatus.config(text="画板状态错误")
            showLog("画板状态异常,无法设置")
    def HidePainter(self):
        self.hd.hideWin()
    def clearPainter(self):
        self.hd.clear_canvas()
    def writeOCR(self):
        deleteFolder=r'D:\PGMCode\Mycode\pythonCode\voice_txt\goodTools\materialFolder'    !!!! #注意这里路径
        self.deleteAllFile(deleteFolder)
        # 每次保存图像前清空文件夹
        picPath=self.setPicPath()
        self.netC.save_hand(picPath)
    #     隐藏窗口
    #     self.hd.hideWin()
    #     得到图片以后进行手写识别
        self.picTocken=self.picT.gettocken()
        handWord=self.picT.picToword(picPath,self.picTocken)
        self.writeTxtToWin(handWord)
        self.copyText()


    def midlleUp(self):
        self.netC.middle_mouse_up()
    def midlleDown(self):
        self.netC.middle_mouse_down()

    def newtimeFormate(self,str):
        strList = str.split("-")
        return "{}-{}-{} {}:{}:{}".format(strList[0], strList[1], strList[2], strList[3], strList[4], strList[5])
    def planTxtRecord(self):

        self.labelShow("状态：格式化计划文本")
        text_content = self.text_widget.get("1.0", "end")

        newText="|[{}]|---------{}".format(self.newtimeFormate(getNowTime()),text_content)
        self.writeTxtToWin(newText)
        self.copyText()
    def showWin(self):
        self.root.deiconify()  # 显示窗口
        self.root.attributes('-toolwindow', False)  # 重置窗口属性
    def hideWin(self):
        self.root.attributes('-toolwindow', True)
        self.root.withdraw()  # 隐藏窗口
    #     隐藏恢复按钮
    def winZoomOut(self):
    #     缩小窗口,将所有部件隐藏
        app.hideWin()
        littleWin.run()
        littleWin.showWin()


    def initProxy(self):
        proxyStatus=self.netC.check_proxy()
        if proxyStatus==1:
            self.buttonVPN.config(text="关闭代理")
        elif proxyStatus==0:
            self.buttonVPN.config(text="开启代理")
        else:
            self.buttonVPN.config(text="代理状态错误")
    def changeVPN(self):
        if self.buttonVPN.cget('text')=="开启代理":
            self.netC.set_proxy(self.vpnIP, "<local>",1)
            self.buttonVPN.config(text="关闭代理")
        elif self.buttonVPN.cget('text')=="关闭代理":
            self.netC.set_proxy(self.vpnIP, "<local>", 0)
            self.buttonVPN.config(text="开启代理")
        else:
            self.buttonVPN.config(text="代理状态错误")
            print("代理状态异常,无法设置")
    def controlapha(self,deep):
        self.root.attributes('-alpha', deep)
    def setPicPath(self):
        nowTime=getNowTime()
        picPath = r"D:\PGMCode\Mycode\pythonCode\voice_txt\goodTools\materialFolder\{}.png".format(nowTime)
        return picPath
    def handle_drop(self,event):
        self.labelShow("状态：识别文件路径中...")
        # 当有多个文件时,需要自动增加换行,不清空
        files = event.data
        # 检查是否是文件夹,如果是文件夹,则找到其目录下所有路径
        if os.path.isdir(files):
            files=self.netC.getAllFilePath(files)
        else:
            files=files+"<>\n"
            # 如果不是文件夹就打印文件路径
            # for file_path in files:
            print(files)  # 在控制台打印文件路径
            # self.writeTxtToWin(files)
        self.text_widget.insert("end", files)
        self.copyText()
    def setNowWord(self,text):
        self.nowHandWord=text
    def nowWord(self):
        self.labelShow("状态：当前识别信息")
        self.writeTxtToWin(self.nowHandWord)
    def labelShow(self,text):
        self.status_label.config(text="")
        self.status_label.config(text=text)
    def deleteAllFile(self,folder):
        files = glob.glob(os.path.join(folder, '*'))
        # 遍历文件列表并删除每个文件
        for file in files:
            try:
                os.remove(file)  # 删除文件
            except OSError as e:
                showLog(f"删除文件时出错: {file}, 错误信息: {e.strerror}")
    def writeRecongnize(self):
        # 在生成新截图之前删除所有截图,以免一直占用空间
        deleteFolder=r'D:\PGMCode\Mycode\pythonCode\voice_txt\goodTools\materialFolder'    !!!! #注意这里路径
        self.deleteAllFile(deleteFolder)
        self.clearText()
        self.labelShow("状态:截图图片并识别")
        # 一开始就启用tocken改为只有使用百度识别时时才使用tocken
        # self.picTocken = self.picT.gettocken()
        # 得到图片
        tst=TransparentWindow(self.setPicPath(),self.picTocken)
        tst.run()
    def writeTxtToWin(self,allTxt):
        self.text_widget.delete("1.0", "end")
        if allTxt:
            self.text_widget.insert("1.0", allTxt)
        self.copyText()
    def restorePrevious(self):
        self.labelShow("状态：恢复上一步")
        if self.lastWord:
            # 恢复上一步功能
            self.writeTxtToWin(self.lastWord)

    def copyText(self):
        self.labelShow("状态：复制文本信息")
        text_content = self.text_widget.get("1.0", "end")
        pyperclip.copy(text_content)
    def destroy(self):
        self.root.destroy()
    def clearText(self):
        self.labelShow("状态：清空文本,并存储上一步有效信息")
        text_content = self.text_widget.get("1.0", "end")
        if text_content and "没有识别出任何手写字符" not in text_content :
            self.lastWord=text_content
        # 清空功能
        self.text_widget.delete("1.0", "end")
    def run(self):
        self.root.mainloop()
app=main()
class TransparentWindow:
    def __init__(self, picPath, picTocken):
        self.picTocken = picTocken
        self.picPath = picPath
        self.picT = picToTxt()
        self.HandTxt = None
        app.controlapha(0)
    def run(self):
        # 截取整个屏幕
        self.screenshot = ImageGrab.grab()
        self.handOcr = tk.Tk()
        self.handOcr.attributes('-topmost', True)
        self.handOcr.title("拖动绘制矩形")
        self.handOcr.geometry("1366x730")
        self.handOcr.configure(bg="gray")

        # 设置窗口透明度（0-1之间，0为完全透明，1为不透明）
        self.handOcr.attributes("-alpha", 0.4)

        self.canvas = tk.Canvas(self.handOcr, bg="black")
        self.canvas.pack(fill=tk.BOTH, expand=True)

        self.rect_start = None
        self.rect = None
        self.rectG = None

        # 绑定鼠标事件
        self.canvas.bind("<Button-1>", self.on_mouse_down)
        self.canvas.bind("<B1-Motion>", self.on_mouse_drag)
        self.canvas.bind("<ButtonRelease-1>", self.on_mouse_release)
        self.buttonCA = tk.Button(self.handOcr, text="取消框选", command=self.hideButton, height=1)
        self.buttonCA.config(bg='red', fg='white')  # 设置背景色为红色，前景色为白色
        self.buttonOK = tk.Button(self.handOcr, text="百度识别", command=self.screenshotOK, height=1)
        self.buttonOK.config(bg='green', fg='white')  # 设置背景色为绿色，前景色为白色
        self.buttonNOCR = tk.Button(self.handOcr, text="OCR识别", command=self.screenshotNOCR, height=1)
        self.buttonNOCR.config(bg='blue', fg='white')  # 设置背景色为绿色，前景色为白色
        self.buttonCS = tk.Button(self.handOcr, text="单纯截图", command=self.getCaptureScreen, height=1)
        self.buttonCS.config(bg='#FFA500',  fg='white')  # 设置背景色为绿色，前景色为白色
        self.buttonCO = tk.Button(self.handOcr, text="关闭窗口", command=self.closeOCR, height=1)
        self.buttonCO.config(bg='#800080', fg='white')  # 设置背景色为绿色，前景色为白色
    def closeOCR(self):
        self.handOcr.destroy()
        app.controlapha(0.9)
    def on_mouse_down(self, event):
        # 记录鼠标按下的起始点
        self.rect_start = (event.x, event.y)

    def on_mouse_drag(self, event):
        # 实时绘制矩形
        if self.rect:
            self.canvas.delete(self.rect)
        if self.rectG:
            self.canvas.delete(self.rectG)
        x1, y1 = self.rect_start
        x2, y2 = event.x, event.y
        self.rect = self.canvas.create_rectangle(x1, y1, x2, y2, outline="red", width=5)
        # self.rectG = self.canvas.create_rectangle(x1+8, y1+8, x2-8, y2-8, outline="white", width=8)

        # 设置选中窗口部分的透明度为0
        self.handOcr.attributes("-alpha", 0.3)  # 调整透明度的值

    def showButton(self):
        # 根据释放坐标生成按钮
        x1, y1 = self.rect_stop
        # 创建按钮
        self.buttonCA.place(x=x1 - 70*5, y=y1 + 10)  # 设置按钮的位置
        self.buttonCO.place(x=x1-70*4, y=y1 + 10)  # 设置按钮的位置
        self.buttonNOCR.place(x=x1-70*3, y=y1 + 10)  # 设置按钮的位置
        self.buttonOK.place(x=x1-70*2, y=y1 + 10)  # 设置按钮的位置
        self.buttonCS.place(x=x1-70, y=y1 + 10)  # 设置按钮的位置

    def hideButton(self):
        self.canvas.delete("all")
        self.buttonCA.place_forget()
        self.buttonOK.place_forget()
        self.buttonNOCR.place_forget()
        self.buttonCS.place_forget()
        self.buttonCO.place_forget()
    def screenshotNOCR(self):
        self.getCaptureScreen()
        # 识别图片
        handWord = self.picT.picOcrToword(self.picPath)
        allTxt = ""
        if handWord:
            for i in handWord:
                allTxt += i + "\n"
        else:
            allTxt = "没有识别出任何印刷字符"
        app.setNowWord(allTxt)
        app.writeTxtToWin(allTxt)
        app.labelShow("状态:印刷字符识别完成")
    def screenshotOK(self):
        self.getCaptureScreen()

        self.picTocken=self.picT.gettocken()
        # 识别图片
        handWord = self.picT.picToword(self.picPath, self.picTocken)
        allTxt = ""
        if handWord:
            for i in handWord:
                allTxt += i + "\n"
        else:
            allTxt = "没有识别出任何手写字符"
        app.setNowWord(allTxt)
        app.writeTxtToWin(allTxt)
        app.labelShow("状态:手写字符识别完成")
        # # 显示图像（可选）
        # pil_image.show()

    def getCaptureScreen(self):
        x1, y1 = self.rect_start
        x2, y2 = self.rect_stop
        x1, y1 = x1 + 11, y1 + 33
        x2, y2 = x2 + 8, y2 + 29

        img_np = np.array(self.screenshot)
        newImg = img_np[y1:y2, x1:x2]
        pil_image = Image.fromarray(newImg)
        # 保存图像为PNG文件
        pil_image.save(self.picPath)
        self.closeOCR()
        allTxt=self.picPath
        app.setNowWord(allTxt)
        app.writeTxtToWin(allTxt)
        app.labelShow("状态:截图完成")
    def on_mouse_release(self, event):
        # 鼠标释放时，固定矩形大小
        self.rect = None
        # 恢复窗口透明度
        self.handOcr.attributes("-alpha", 0.3)  # 恢复为完全不透明
        self.rect_stop = event.x, event.y
        self.showButton()
app.run()
"""
开发逻辑:
使用了两种方式,
一个是离线的easyocr,识别印刷文字
一个是百度手写api识别手写文字

还有一个单独的截图,会显示截图后的路径
还有一个拖动显示文件路径的功能

//截取的图片会自动命名为当前时间,在下一次截图识别前销毁上一次图片


//接下来增加一个功能,点击收缩,会自动将窗口变成一个小矩形,其他按钮隐藏,这个小矩形只有一个按钮
点击这个恢复,会自动隐藏恢复按钮,将其他按钮展示出来

//相比横着的界面遮挡的太多了,我觉得竖着的遮挡界面更少
//手写画布的按钮,应该将显示和隐藏变成一个
"""
