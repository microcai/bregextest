#include "stdafx.h"
#include "mainwnd.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWnd w;
	w.show();
	w.setWindowTitle("Boost.Regex.Test");
	return a.exec();
}
