#include "pvz_01.h"
#include <QtWidgets/QApplication>
#include <qdialog>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow win;
	//win.show();
	return a.exec();
}
