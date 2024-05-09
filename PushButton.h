#pragma once
#include"BasicWidget.h"
#include"Configure.h"
class PushButton:
	public BasicWidget
{
public:
	PushButton(const std::string& text = "Button", int x = 0, int y = 0, int w = 100, int h = 30);
	void show()override;

	bool isin();//判断鼠标是否在当前按钮上
	bool isClicked();//判断是否点击

	void eventLoop(const ExMessage& msg);

private:
	std::string m_text;
	ExMessage m_msg;

};

