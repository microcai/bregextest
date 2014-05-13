#ifndef MAINWND_H
#define MAINWND_H

#include <QtGui/QMainWindow>
#include <QtGui>
#include "texteditor.h"

class MainWnd : public QMainWindow
{
	Q_OBJECT

public:
	MainWnd(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWnd();

private slots:
	void regexMatch();
	void icaseChanged(int state);
private:
	QCheckBox *icaseCheckBox;
	TextEditor *regexEdit;
	TextEditor *sourceEdit;
	TextEditor *matchesEdit;

	void setupToolBar();
	void createDockWidget();
	void setupActions();
};

#endif // MAINWND_H
