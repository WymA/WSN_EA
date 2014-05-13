#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QScrollBar>
#include "dashboard.h"

DashBoard::DashBoard(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this) ;
    startbt = new QPushButton(tr("Start/Pause")) ;
    stopbt = new QPushButton(tr("Stop")) ;
    setbt = new QPushButton(tr("Setting")) ;

    layout->addWidget( startbt, 3, 0, 1, 1 ) ;
    layout->addWidget( stopbt, 3, 1, 1, 1  ) ;
    layout->addWidget( setbt,   4, 0, 1, 1  ) ;

    infoViewer = new QTextEdit ;
    layout->addWidget( infoViewer, 0, 0, 2, 2 );

    infoViewer->setReadOnly( true );

    connect( startbt, &QPushButton::clicked, this, &DashBoard::startPauseEA  ) ;
    connect( stopbt, &QPushButton::clicked, this, &DashBoard::stopEA  ) ;
    connect( setbt, &QPushButton::clicked, this, &DashBoard::settingSignal ) ;

    this->setLayout(layout) ;
}


void DashBoard::printLine( const QString& line )
{
    infoViewer->setText( infoViewer->toPlainText() +'\n' +line) ;
    
    QScrollBar *scrollbar = infoViewer->verticalScrollBar();
    scrollbar->setSliderPosition(scrollbar->maximum());
}
