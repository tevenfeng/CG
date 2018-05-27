#include "SimpleViewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SimpleViewer w;
	w.show();
	return a.exec();
}
