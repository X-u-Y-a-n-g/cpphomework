#include"Managerment.h"
#include"Window.h"

int main()
{
	Window w(960, 640, EX_SHOWCONSOLE);
	w.setWindowTitle("×Ö·û»­");

	Managerment m;
	m.run();


	return w.exec();
}