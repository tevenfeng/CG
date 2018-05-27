#include "SimpleViewer.h"
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include "glwidget.h"

SimpleViewer::SimpleViewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QMenuBar *menuBar = new QMenuBar;
	QMenu *menuFile = menuBar->addMenu(tr("&File"));
	QMenu *menuEdit = menuBar->addMenu(tr("&Edit"));
	menuFile->addAction(tr("Load File"));
	setMenuBar(menuBar);
	GLWidget * glWidget = new GLWidget(this);
	setCentralWidget(glWidget);
}
