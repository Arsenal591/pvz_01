#include "pvz_01.h"
#include <QtWidgets/QApplication>
#include <qdir.h>
#include <qdesktopwidget>

int main(int argc, char *argv[])
{
	QDir::setCurrent(QCoreApplication::applicationDirPath());
	QApplication a(argc, argv);
	MainWindow win;
	win.setFixedSize(QSize(1200, 800));
	win.show();
	win.move((QApplication::desktop()->width() - win.width()) / 2, (QApplication::desktop()->height() - win.height()) / 2);
	QObject::connect(&win, SIGNAL(endApp()), &a, SLOT(quit()));
	return a.exec();
}
