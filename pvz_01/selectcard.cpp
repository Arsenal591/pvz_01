#include "selectcard.h"
#include "qdebug.h"

SelectCard::SelectCard(QWidget* parent)
{
	this->setParent(parent);
	memset(ifSelected, 0, sizeof(ifSelected));
	selectedSum = 0;
	this->setFixedSize(465, 554);
	this->setGeometry(0, 100, 465, 554);
	
	this->setAutoFillBackground(true);
	QPalette* newQPalette = new QPalette;
	QPixmap* newImg = new QPixmap(PICKCARD_PATH);
	*newImg = newImg->scaled(this->size());
	newQPalette->setBrush(QPalette::Background, QBrush(*newImg));
	this->setPalette(*newQPalette);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			buttons[3 * i + j] = new MyButton(this, CARD_PATH[3 * i + j] + "2.jpg");
			buttons[3 * i + j]->setSize(QRect(60 + j * 65, 100 + i * 100, 45, 63));
			buttons[3 * i + j]->setOffset(2, 2);
			buttons[3 * i + j]->show();
		}
	}
	this->ok = new MyButton(this, PICKCARD_BUTTON_PATH);
	this->ok->setSize(QRect(182, 450, 100, 60));
	this->ok->setOffset(2, 2);

	statement = new QLabel(this);
	statement->setFont(QFont("Microsoft YaHei", 12));
	statement->setGeometry(300, 175, 120, 120);
	statement->setWordWrap(true);
	statement->setAlignment(Qt::AlignTop);
	statement->show();

	title = new QLabel(this);
	title->setFont(QFont("Microsoft YaHei", 15));
	title->setGeometry(100, 20, 300, 60);
	title->setText(QStringLiteral("请选择6种你需要的植物"));
	title->show();

	QPalette* pal = new QPalette;
	pal->setColor(QPalette::WindowText, qRgb(213, 159, 43));
	statement->setPalette(*pal);
	title->setPalette(*pal);
	connect();
}

void SelectCard::connect()
{
	QSignalMapper* mapper1 = new QSignalMapper(this);
	QSignalMapper* mapper2 = new QSignalMapper(this);
	for (int i = 0; i < 9; i++)
	{
		QObject::connect(buttons[i], SIGNAL(clicked()), mapper1, SLOT(map()));
		mapper1->setMapping(buttons[i], i);
		QObject::connect(buttons[i], SIGNAL(entered()), mapper2, SLOT(map()));
		mapper2->setMapping(buttons[i], i);
	}
	QObject::connect(mapper1, SIGNAL(mapped(int)), this, SLOT(dealCard(int)));
	QObject::connect(mapper2, SIGNAL(mapped(int)), this, SLOT(changeStatement(int)));

	QObject::connect(ok, SIGNAL(clicked()), this, SLOT(submit()));
}

void SelectCard::dealCard(int n)
{
	if (ifSelected[n] == true)
	{
		buttons[n]->setIcon(QIcon(CARD_PATH[n] + "2.jpg"));
		ifSelected[n] = false;
		selectedSum--;
	}
	else
	{
		if (selectedSum >= 3)return;
		buttons[n]->setIcon(QIcon(CARD_PATH[n] + "1.jpg"));
		ifSelected[n] = true;
		selectedSum++;
	}
}

void SelectCard::changeStatement(int n)
{
	statement->setText(STATEMENTS[n]);
}
void SelectCard::submit()
{
	if (selectedSum < 3)return;
	QVector<int>res;
	int pos = 0;
	for (int i = 0; i < 9; i++)
	{
		if (ifSelected[i])
		{
			res.push_back(i);
		}
	}
	emit selected(res);
}

void SelectCard::hide()
{
	this->QWidget::hide();
}