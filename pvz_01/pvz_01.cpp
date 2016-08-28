#include "pvz_01.h"
#include <qdialog>

MainWindow::MainWindow(QWidget* parent)
{
	_currentWidget = new WelcomeInterface;
	_currentWidget->show();

}