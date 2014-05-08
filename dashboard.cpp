#include <QHBoxLayout>
#include <QPushButton>
#include "dashboard.h"

DashBoard::DashBoard(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this) ;
    QPushButton* startbt = new QPushButton(tr("Start/Pause")) ;
    layout->addWidget( startbt ) ;
    layout->addWidget(new QPushButton(tr("test"))) ;

    connect( startbt, &QPushButton::clicked, this, &DashBoard::startPauseEA  ) ;

    this->setLayout(layout) ;
}


