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
	
}

void Managerment::drawBackground()
{
	::putimage(0, 0, &m_bk);
}