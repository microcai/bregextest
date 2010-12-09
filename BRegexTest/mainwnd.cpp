#include "stdafx.h"
#include "mainwnd.h"
#include <boost/regex.hpp>
using namespace boost;

MainWnd::MainWnd(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	setupToolBar();
	createDockWidget();
	setupActions();	
}

MainWnd::~MainWnd()
{

}

void MainWnd::setupToolBar()
{
	QToolBar *toolBar = new QToolBar;
	addToolBar(toolBar);

	icaseCheckBox = new QCheckBox("Case insensitive");
	toolBar->addWidget(icaseCheckBox);
}

void MainWnd::createDockWidget()
{
	//regex widget
	QDockWidget *regexWidget = new QDockWidget("Regex");
	regexWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	regexWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
	addDockWidget(Qt::TopDockWidgetArea, regexWidget);
	regexEdit = new TextEditor(this);
	regexEdit->setPlainText("Boost|Regex|Test");
	regexWidget->setWidget(regexEdit);

	//source widget
	QDockWidget *sourceWidget = new QDockWidget("Source");
	sourceWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	sourceWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
	addDockWidget(Qt::TopDockWidgetArea, sourceWidget);
	sourceEdit = new TextEditor(this);
	sourceEdit->setPlainText("This text is used for testing the\nBoost.Regex.Test");
	sourceWidget->setWidget(sourceEdit);

	//matchs widget
	QDockWidget *matchesWidget = new QDockWidget("Matches");
	matchesWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	matchesWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
	addDockWidget(Qt::BottomDockWidgetArea, matchesWidget);
	matchesEdit = new TextEditor(this);
	matchesEdit->setPlainText("Boost\nRegex\nTest");
	matchesWidget->setWidget(matchesEdit);
}

void MainWnd::setupActions()
{
	connect(sourceEdit, SIGNAL (textChanged()), this, SLOT(regexMatch()));
	connect(regexEdit, SIGNAL (textChanged()), this, SLOT(regexMatch()));
	connect(icaseCheckBox, SIGNAL (stateChanged(int)), this, SLOT(icaseChanged(int)));
}

void MainWnd::icaseChanged(int state)
{
	regexMatch();
}
void MainWnd::regexMatch()
{
	matchesEdit->clear();
	if(sourceEdit->toPlainText().isEmpty() || regexEdit->toPlainText().isEmpty())
		return;

	std::wstring source, regex;
	source.resize(sourceEdit->toPlainText().length());
	source.resize(sourceEdit->toPlainText().toWCharArray(&(*source.begin())));
	regex.resize(regexEdit->toPlainText().length());
	regex.resize(regexEdit->toPlainText().toWCharArray(&(*regex.begin())));

	boost::regex_constants::syntax_option_type regex_flags = boost::regex::no_except;
	if(icaseCheckBox->checkState() == Qt::Checked)
		regex_flags |= boost::regex::icase;

	boost::wregex expression(regex,regex_flags);
	//Returns zero if the expression contains a valid regular expression, otherwise an error code.
	if(0 != expression.status())
		return;
	std::wstring::const_iterator start, end; 
	start = source.begin(); 
	end = source.end(); 
	boost::match_results<std::wstring::const_iterator> what; 
	boost::match_flag_type match_flags = boost::match_default; 
	while(boost::regex_search(start, end, what, expression, match_flags)) 
	{ 
		std::wstring &str = std::wstring(what[0].first, what[0].second);
		matchesEdit->appendPlainText(QString::fromWCharArray(str.c_str()));
		// update search position: 
		if(start == what[0].second)
			break;
		start = what[0].second; 
		// update flags: 
		match_flags |= boost::match_prev_avail; 
		match_flags |= boost::match_not_bob; 
	} 
}
