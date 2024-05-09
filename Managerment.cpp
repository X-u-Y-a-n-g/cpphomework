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
	//�����水ť��ʼ��
	menu_btns.push_back(new PushButton("չʾ����"));
	menu_btns.push_back(new PushButton("�˳�"));
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
	
}


int Managerment::menu()
{
	
	//���ݰ�ťѡ�񷵻�ֵ
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