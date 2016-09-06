#include "pvz_01.h"
#include <QtWidgets/QApplication>
#include <qdialog>
#include <qdir.h>

int main(int argc, char *argv[])
{
	QDir::setCurrent(QCoreApplication::applicationDirPath());
	QApplication a(argc, argv);
	MainWindow win;
	//win.show();
	return a.exec();
}
