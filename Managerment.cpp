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
			case WM_KEYDOWN://���°���
				//��esc�˳�����������
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
			InputBox(a, 1000, "�������ļ���ַ\n��Ϊ���Զ���������ͷ", "�ļ���Դ");
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
	initgraph(960, 640);    //��������
	VideoCapture video(kkk);    //����Ƶ
	//����Ƶ
	const char* str = "@#$%&!=+*,';`.";  //�滻���ص����
	int len = strlen(str);
	Mat frame;  //��ȡͼ��
	Mat show;   //չʾͼ��
	string text;
	int index = 0;
	BeginBatchDraw();
	//���������С
	settextstyle(12, 0, "����");
	while (1)
	{
		video >> frame;     //��ȡÿһ֡ͼ��
		if (frame.empty())  //�����ж�
		{
			break;
		}
		cvtColor(frame, frame, COLOR_BGR2GRAY);     //ת��Ϊ�Ҷ�ͼ
		resize(frame, show, Size(300, 150));    //����ͼ��
		resize(frame, frame, Size(150, 50));   //��������

		//��ȡÿһ�����ص�
		for (int x = 0; x < frame.rows; x++)
		{
			for (int y = 0; y < frame.cols; y++)
			{
				int color = frame.at<uchar>(x, y);
				index = color / 256.0 * len;
				text += str[index];
			}
			//���ÿһ��
			outtextxy(0, x * textheight(str[index]), text.c_str());
			text.clear();
		}

		imshow("�ַ���", show);
		int userkey = waitKey(1);
		//��ͣ
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