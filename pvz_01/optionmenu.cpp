#include "optionmenu.h"
#include <qdebug.h>

OptionMenu::OptionMenu(QWidget* parent)
{
	this->setParent(parent);
	this->setFixedSize(412, 483);
	this->setGeometry(QRect(394, 160, 412, 483));
	this->setFont(QFont("Microsoft YaHei", 12));

	this->setAutoFillBackground(true);
	QPalette* newPalette = new QPalette;
	QPixmap* newImg = new QPixmap(SETTING_PATH);
	*newImg = newImg->scaled(this->size());
	newPalette->setBrush(QPalette::Background, QBrush(*newImg));
	this->setPalette(*newPalette);

	musicLabel = new QLabel(this);
	musicLabel->setText(QStringLiteral("ÒôÀÖ"));
	audioLabel = new QLabel(this);
	audioLabel->setText(QStringLiteral("ÒôÐ§"));
	musicSetting = new QSlider(Qt::Horizontal, this);
	musicSetting->setRange(0, 100);
	audioSetting = new QSlider(Qt::Horizontal, this);
	audioSetting->setRange(0, 100);
	musicSetting->setStyleSheet("QSlider::groove:horizontal{background:#1D1E24;height:4px;}\
									QSlider::handle:horizontal{background:#686A8D;\
																height:20px;width:10px;margin: -8 0px;}");
	audioSetting->setStyleSheet("QSlider::groove:horizontal{background:#1D1E24;height:4px;}\
									QSlider::handle:horizontal{background:#686A8D;\
																height:20px;width:10px;margin: -8 0px;}");

	QGroupBox *box1 = new QGroupBox(this);
	QGroupBox *box2 = new QGroupBox(this);
	QHBoxLayout* newLayout1 = new QHBoxLayout(this);
	newLayout1->addWidget(musicLabel);
	newLayout1->addWidget(musicSetting);
	QHBoxLayout* newLayout2 = new QHBoxLayout(this);
	newLayout2->addWidget(audioLabel);
	newLayout2->addWidget(audioSetting);

	box1->setLayout(newLayout1), box2->setLayout(newLayout2);
	box1->setGeometry(QRect(100, 140, 200, 50));
	box2->setGeometry(QRect(100, 200, 200, 50));
	box1->setStyleSheet("border:none");
	box2->setStyleSheet("border:none");

	QPalette* textType = new QPalette;
	textType->setColor(QPalette::WindowText, qRgb(120, 123, 162));
	musicLabel->setPalette(*textType);
	audioLabel->setPalette(*textType);

	ok = new MyButton(this, SETTING_BUTTON_PATH);
	ok->setSize(QRect(25, 383, 360, 100));
	ok->setOffset(2, 2);

	connect();
}

void OptionMenu::connect()
{
	QObject::connect(ok, SIGNAL(clicked()), this, SLOT(finish()));
}

void OptionMenu::finish()
{
	qDebug() << "!!\n";
	emit setVolume(musicSetting->value(), audioSetting->value());
}