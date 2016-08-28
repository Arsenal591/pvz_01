#include "pvz_01.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	pvz_01 w;
	w.show();
	int a = 10;
	int b = 11;
	return a.exec();
}
