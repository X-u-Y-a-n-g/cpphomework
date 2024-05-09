#pragma once
#include"Window.h"
#include<vector>
#include"PushButton.h"
#include<string>
using namespace std;
class Managerment
{
	enum Operator
	{
		Display, Menu = 66
	};
public:
	Managerment();
	//启动管理类
	void run();

	int menu();
	void display(string kkk);

	void drawBackground();

private:
	IMAGE m_bk;
	ExMessage m_msg;

	std::vector<PushButton*>menu_btns;
};

