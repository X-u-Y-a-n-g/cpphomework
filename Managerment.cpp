#include "Managerment.h"
#include<iostream>
#include"conio.h"
#include"Window.h"
using namespace std;
#include "stdio.h"
#include<iostream> 
#include <opencv2/opencv.hpp> 
#include<graphics.h>
#include<easyx.h>
#include<mmsystem.h>
#include<string>
using namespace cv;
#pragma comment(lib,"winmm.lib")

Managerment::Managerment()
{
	::loadimage(&m_bk, "./background.png", Window::width(), Window::height());
	//主界面按钮初始化
	menu_btns.push_back(new PushButton("展示动画"));
	menu_btns.push_back(new PushButton("退出"));
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(250, 50);
		int bx = (Window::width() - menu_btns[i]->width()) / 2;
		int vspace = (Window::height() - menu_btns.size() * menu_btns[i]->height()) / 2;
		int by = vspace + i * menu_btns[i]->height();
		menu_btns[i]->move(bx, by);
	}
}

void Managerment::run()
{
	BeginBatchDraw();
	int op = Menu;
	Window::clear();
	while (true)
	{
		drawBackground();
		if (Window::hasMsg())
		{

			m_msg = Window::getMsg();
			switch (m_msg.message)
			{
			case WM_KEYDOWN://按下按键
				//按esc退出返回主界面
				if (m_msg.vkcode == VK_ESCAPE)
				{
					op = Menu;
				}
				break;
			default:
				break;
			}
		}
		char a[1000]; string kkk;
		cout << "run while" << endl;
		switch (op)
		{
		case Menu:
			op = menu();
			cout << "kkk";
			break;
		case Managerment::Display:
			InputBox(a, 1000, "请输入文件地址\n若为空自动调用摄像头", "文件来源");
			kkk = a;
			display(kkk);
			op = Menu;
			break;
		default:
			exit(666);
			break;
		}
		Window::flushDraw();

	}
	Window::endDraw();
}


int Managerment::menu()
{
	
	//根据按钮选择返回值
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->show();
		menu_btns[i]->eventLoop(m_msg);
		if (menu_btns[i]->isClicked())
		{
			return i;
		}
	}
	return Menu;
}

void Managerment::display(string kkk)
{
	initgraph(960, 640);    //创建窗口
	VideoCapture video(kkk);    //打开视频
	//打开音频
	const char* str = "@#$%&!=+*,';`.";  //替换像素点符号
	int len = strlen(str);
	Mat frame;  //获取图像
	Mat show;   //展示图像
	string text;
	int index = 0;
	BeginBatchDraw();
	//调整字体大小
	settextstyle(12, 0, "楷体");
	while (1)
	{
		video >> frame;     //获取每一帧图像
		if (frame.empty())  //结束判断
		{
			break;
		}
		cvtColor(frame, frame, COLOR_BGR2GRAY);     //转换为灰度图
		resize(frame, show, Size(300, 150));    //缩放图像
		resize(frame, frame, Size(150, 50));   //二次缩放

		//获取每一个像素点
		for (int x = 0; x < frame.rows; x++)
		{
			for (int y = 0; y < frame.cols; y++)
			{
				int color = frame.at<uchar>(x, y);
				index = color / 256.0 * len;
				text += str[index];
			}
			//输出每一行
			outtextxy(0, x * textheight(str[index]), text.c_str());
			text.clear();
		}

		imshow("字符画", show);
		int userkey = waitKey(1);
		//暂停
		if (userkey == ' ')
		{
			userkey = waitKey(0);
			if (userkey == ' ')
			{
				continue;
			}
		}
		if (userkey == 27)
		{

			return;
		}
		FlushBatchDraw();
	}

	EndBatchDraw();
	closegraph();
	return;
}

void Managerment::drawBackground()
{
	::putimage(0, 0, &m_bk);
}