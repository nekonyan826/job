import sys
from time import sleep
from PyQt6.QtWidgets import QApplication,QWidget,QLabel,QPushButton,QMainWindow,QLineEdit,QFormLayout
from PyQt6.QtGui import QIcon,QFont
from PyQt6.QtCore import Qt,pyqtSignal
from PyQt6 import QtCore
import random

import pexpect

from pyqtgraph import PlotWidget, plot
import pyqtgraph as pg

graph_width = 300
graph_height =300

class MainWindow(QMainWindow):
    """
    @ 说明：主窗体类
    """
    def __init__(self):
        """
        @ 主窗体构造函数
        """
        super().__init__()                                          # 调用父类构造函数
        self.now_time = 0
        self.num = 0
        self.p = 0.2
        self.m = 2
        # self.n = 10
        self.l = 100
        self.interval = 1000

        self.pexpect = pexpect.spawn("../main")

        # 图像数据
        self.times = []
        self.avg_wait_times = []
        self.min_wait_times = []
        self.max_wait_times = []
        self.sizes = []
        self.working_job = []

        self.flag_input = False
        self.input_job_timer = QtCore.QTimer()

        self.initUI()
    
    def initUI(self):

        self.setWindowTitle("陈一苇最漂亮！！！！")                         # 设置标题
        self.setWindowIcon(QIcon("res/Entire Network.ico"))         # 设置图标

         # 设置中央控件
        self.mainwidget = QWidget(self)
        self.mainwidget.resize(200,800)
        self.mainwidget.move(950,0)
 
        # 设置布局
        self.flayout_main = QFormLayout(self)
        self.mainwidget.setLayout(self.flayout_main)
        # self.flayout_main.move(200,300)

        #设置参数
        self.ledit_p = QLineEdit(str(self.p),self)
        self.ledit_p.setEchoMode(QLineEdit.EchoMode.Normal)
        self.flayout_main.addRow("注入概率 p", self.ledit_p)

        self.ledit_m = QLineEdit(str(self.m),self)
        self.ledit_m.setEchoMode(QLineEdit.EchoMode.Normal)
        self.flayout_main.addRow("一轮最多注入job数 m", self.ledit_m)

        self.ledit_l = QLineEdit(str(self.l),self)
        self.ledit_l.setEchoMode(QLineEdit.EchoMode.Normal)
        self.flayout_main.addRow("job最大运行时间 l", self.ledit_l)

        self.ledit_interval = QLineEdit(str(self.interval),self)
        self.ledit_interval.setEchoMode(QLineEdit.EchoMode.Normal)
        self.flayout_main.addRow("运行间隔时间单位毫秒", self.ledit_interval)

        self.ledit_platform =  QLineEdit("NOP",self)
        self.ledit_platform.setEchoMode(QLineEdit.EchoMode.Normal)
        self.flayout_main.addRow("系统状态", self.ledit_platform)

        self.ledit_now_time =  QLineEdit(str(self.now_time),self)
        self.ledit_now_time.setEchoMode(QLineEdit.EchoMode.Normal)
        self.flayout_main.addRow("当前系统时间", self.ledit_now_time)

        self.ledit_num =  QLineEdit(str(self.num),self)
        self.ledit_num.setEchoMode(QLineEdit.EchoMode.Normal)
        self.flayout_main.addRow("已经产生多少job了", self.ledit_num)


        self.ledit_job_id =  QLineEdit(self)
        self.ledit_job_id.setEchoMode(QLineEdit.EchoMode.Normal)
        self.flayout_main.addRow("当前job id", self.ledit_job_id)

        self.ledit_job_s =  QLineEdit(self)
        self.ledit_job_s.setEchoMode(QLineEdit.EchoMode.Normal)
        self.flayout_main.addRow("当前job起始时间", self.ledit_job_s)

        self.ledit_job_w =  QLineEdit(self)
        self.ledit_job_w.setEchoMode(QLineEdit.EchoMode.Normal)
        self.flayout_main.addRow("当前job等了多长时间", self.ledit_job_w)

        self.ledit_job_t =  QLineEdit(self)
        self.ledit_job_t.setEchoMode(QLineEdit.EchoMode.Normal)
        self.flayout_main.addRow("当前job的剩余运行时间", self.ledit_job_t)

        self.ledit_job_p =  QLineEdit(self)
        self.ledit_job_p.setEchoMode(QLineEdit.EchoMode.Normal)
        self.flayout_main.addRow("当前job的优先级", self.ledit_job_p)



        # 读取参数按钮
        self.btn = QPushButton("get",self)
        self.btn.resize(self.btn.sizeHint())
        self.btn.move(10,120)
        self.btn.clicked.connect(self.get_param)
        # 按钮
        btn_input_continue = QPushButton("持续注入",self)
        btn_input_continue.resize(btn_input_continue.sizeHint())
        btn_input_continue.move(110,120)
        btn_input_continue.clicked.connect(self.start_input)

        btn_input_pause = QPushButton("暂停注入",self)
        btn_input_pause.resize(btn_input_pause.sizeHint())
        btn_input_pause.move(410,120)
        btn_input_pause.clicked.connect(self.pause_input)


        btn_input_single = QPushButton("单步测试",self)
        btn_input_single.resize(btn_input_single.sizeHint())
        btn_input_single.move(210,120)
        btn_input_single.clicked.connect(self.run)

        btn_reset = QPushButton("清空状态",self)
        btn_reset.resize(btn_input_single.sizeHint())
        btn_reset.move(510,120)
        btn_reset.clicked.connect(self.reset)
 
        lab = QLabel("Hello World.",self)                           # 创建label控件
        lab.resize(300,100)                                         # 设置标签尺寸
        lab.setFont(QFont("Times new roman",16))                    # 设置字体
        lab.setAlignment(Qt.AlignmentFlag.AlignCenter)              # 设置标签对齐方式

        # graphWidget = pg.PlotWidget(self)
        # # self.setCentralWidget(self.graphWidget)
        # hour = [1,2,3,4,5,6,7,8,9,10]
        # temperature = [30,32,34,32,33,31,29,32,35,45]
        # # plot data: x, y values
        
        # graphWidget.plot(hour, temperature)
        # graphWidget.resize(300,100)
        # graphWidget.move(300,400)

        # 数据图
        styles = {'color':'r', 'font-size':'20px'}

        # 等待时间
        self.graph_wait_time = pg.PlotWidget(self)
        self.graph_wait_time.setTitle("等待时间", color="b", size="30pt")
        self.graph_wait_time.setBackground('w')
        self.graph_wait_time.setLabel('left', '等待时间', **styles)
        self.graph_wait_time.setLabel('bottom', '运行时间', **styles)
        # self.graph_wait_time.plot(self.times, self.avg_wait_times)

        pen1 = pg.mkPen(color=(255, 0, 0), width=4)
        pen2 = pg.mkPen(color=(255, 198, 0), width=4)
        pen3 = pg.mkPen(color=(255, 0, 122), width=4)
        self.line_avg_wait_time = self.graph_wait_time.plot(self.times, self.avg_wait_times,pen = pen1)
        self.line_min_wait_time = self.graph_wait_time.plot(self.times, self.min_wait_times,pen = pen2)
        self.line_max_wait_time = self.graph_wait_time.plot(self.times, self.max_wait_times,pen = pen3)

        self.graph_wait_time.resize(graph_width,graph_height)
        self.graph_wait_time.move(0,200)

        # 队列大小
        self.graph_size = pg.PlotWidget(self)
        self.graph_size.setTitle("队列大小", color="b", size="30pt")
        self.graph_size.setBackground('w')
        self.graph_size.setLabel('left', '等待时间', **styles)
        self.graph_size.setLabel('bottom', '运行时间', **styles)

        pen4 = pg.mkPen(color=(255, 0, 0), width=4)
        self.line_size = self.graph_size.plot(self.times, self.sizes,pen = pen4)

        self.graph_size.resize(graph_width,graph_height)
        self.graph_size.move(graph_width+10,200)
        # 正在执行的job剩余时间
        self.graph_working_job = pg.PlotWidget(self)
        self.graph_working_job.setTitle("剩余时间", color="b", size="30pt")
        self.graph_working_job.setBackground('w')
        self.graph_working_job.setLabel('left', '等待时间', **styles)
        self.graph_working_job.setLabel('bottom', '运行时间', **styles)

        pen5 = pg.mkPen(color=(255, 0, 0), width=4)
        self.line_working_job = self.graph_working_job.plot(self.times,self.working_job,pen = pen5)
        # self.graph_working_job.addItem(pg.BarGraphItem(x = self.times, height = self.working_job, width = 0.6, brush ='g'))

        self.graph_working_job.resize(graph_width,graph_height)
        self.graph_working_job.move(2*(graph_width+10),200)



        self.setFixedSize(1200, 800)                                 #设置窗体大小
        self.show()                                                 #显示窗体

    
    def get_param(self):
        self.p = float(self.ledit_p.text())
        self.m = int(self.ledit_m.text())
        self.l = int(self.ledit_l.text())
        self.interval = int(self.ledit_interval.text())
        # print(self.p)
    
    def reset(self):
        self.now_time = 0
        self.num = 0
        self.times = []
        self.avg_wait_times = []
        self.min_wait_times = []
        self.max_wait_times = []
        self.sizes = []
        self.working_job = []
        self.pexpect.close()
        self.pexpect = pexpect.spawn("../main")

        self.ledit_now_time.setText(str(self.now_time))
        self.ledit_num.setText(str(self.num))

        self.ledit_platform.setText("NOP")
        self.ledit_job_id.setText("")
        self.ledit_job_s.setText("")
        self.ledit_job_t.setText("")
        self.ledit_job_w.setText("")
        self.ledit_job_p.setText("")

        self.line_avg_wait_time.setData(self.times, self.avg_wait_times)
        self.line_min_wait_time.setData(self.times, self.min_wait_times)
        self.line_max_wait_time.setData(self.times, self.max_wait_times)
        self.line_size.setData(self.times,self.sizes)
        self.line_working_job.setData(self.times,self.working_job)



    def start_input(self):
        self.flag_input = True
        self.input_job_timer.timeout.connect(self.run)
        self.input_job_timer.start(self.interval)
        # self.input_job() 
    
    def pause_input(self):
        self.flag_input = False
        self.input_job_timer.stop()

    def run(self):
        self.now_time += 1
        jobs = []
        tmp_num = 0
        for i in range(self.m):
            tmp_p = random.random()
            # print(tmp_p)
            if tmp_p<self.p:
                tmp_jobs = []
                tmp_jobs.append(self.num)
                tmp_jobs.append(self.now_time)
                tmp_length = random.randint(0, self.l)
                tmp_jobs.append(tmp_length)
                self.num += 1 
                tmp_num +=1
                jobs.append(tmp_jobs)

        # print(str(self.now_time)+" "+str(tmp_num))
        self.pexpect.sendline(str(self.now_time)+" "+str(tmp_num))
        for item in jobs:
            # print(str(item[0])+" "+str(item[1])+" "+str(item[2]))
            self.pexpect.sendline(str(item[0])+" "+str(item[1])+" "+str(item[2]))

        # self.pexpect.interact()
        # self.pexpect.expect("ok")
        # output = self.pexpect.readlines()
        # print(output)
        # print()
        tmp = self.pexpect.before
        ans = []
        if tmp !=None:
            tmp = tmp.decode('utf-8')

            tmp = tmp.split("\n")
            for i in range(len(tmp)):
                tmp_ans = tmp[i].split(" ")
                if tmp_ans[0] == '-1':
                    ans = tmp_ans
        # print(ans)
        if len(ans) != 0:
            self.update(ans)
        # for i in range(len(jobs)):
        #     output = self.pexpect.readline()
        #     print(output)
        
        self.pexpect.expect("ok")

        # self.pexpect.expect("ok")

        

    def update(self,ans):

        self.ledit_now_time.setText(str(self.now_time))
        self.ledit_num.setText(str(self.num))

        self.times.append(int(ans[1]))
        self.avg_wait_times.append(float(ans[3]))
        self.min_wait_times.append(int(ans[4]))
        self.max_wait_times.append(int(ans[5]))
        self.sizes.append(int(ans[6]))


        if ans[2] == '1':
            self.working_job.append(int(ans[9]))
            self.ledit_platform.setText("IN")
            self.ledit_job_id.setText(ans[7])
            self.ledit_job_s.setText(ans[8])
            self.ledit_job_t.setText(ans[9])
            self.ledit_job_w.setText(ans[10])
            self.ledit_job_p.setText(ans[11])
        else:
            self.ledit_platform.setText("NOP")
            self.ledit_job_id.setText("")
            self.ledit_job_s.setText("")
            self.ledit_job_t.setText("")
            self.ledit_job_w.setText("")
            self.ledit_job_p.setText("")
            self.working_job.append(0)

        self.line_avg_wait_time.setData(self.times, self.avg_wait_times)
        self.line_min_wait_time.setData(self.times, self.min_wait_times)
        self.line_max_wait_time.setData(self.times, self.max_wait_times)
        self.line_size.setData(self.times,self.sizes)
        self.line_working_job.setData(self.times,self.working_job)
        pass


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec())