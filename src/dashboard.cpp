#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
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
    outputbt = new QPushButton(tr("Ouput PF")) ;

    bCovergaeBt = new QRadioButton("display current best coverage");
    bNodesBt = new QRadioButton("display current best nodes");
    bEnergyBt = new QRadioButton("display current best energy");

    bCovergaeBt->setChecked(true); ;

    layout->addWidget( bCovergaeBt, 3, 0, 1, 2 ) ;
    layout->addWidget( bNodesBt,      4, 0, 1, 2  ) ;
    layout->addWidget( bEnergyBt,     5, 0, 1, 2  ) ;

    layout->addWidget( startbt, 6, 0, 1, 1 ) ;
    layout->addWidget( stopbt, 6, 1, 1, 1  ) ;

    layout->addWidget( outputbt, 7, 1, 1, 1 );
    layout->addWidget( setbt,   7, 0, 1, 1  ) ;

    infoViewer = new QTextEdit ;
    layout->addWidget( infoViewer, 0, 0, 2, 2 );

    infoViewer->setReadOnly( true );

    connect( startbt, &QPushButton::clicked, this, &DashBoard::startPauseEA  ) ;
    connect( stopbt, &QPushButton::clicked, this, &DashBoard::stopEA  ) ;
    connect( setbt, &QPushButton::clicked, this, &DashBoard::settingSignal ) ;
    connect( outputbt, &QPushButton::clicked, this, &DashBoard::outputSignal ) ;

    connect( bCovergaeBt, &QRadioButton::clicked, this, &DashBoard::displayCoverage  ) ;
    connect( bNodesBt, &QRadioButton::clicked, this, &DashBoard::displayNodes  ) ;
    connect( bEnergyBt, &QRadioButton::clicked, this, &DashBoard::displayEnergy ) ;

    this->setLayout(layout) ;
}


void DashBoard::printLine( const QString& line )
{
    infoViewer->append( line ) ;

    QScrollBar *scrollbar = infoViewer->verticalScrollBar();
    scrollbar->setSliderPosition(scrollbar->maximum());
}
