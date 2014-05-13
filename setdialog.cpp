#include <QSpinBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "setdialog.h"


SetDialog::SetDialog(    int f_length, int r_sens,  int r_comm,
                         int pop, int t_gen, double m_rate, double c_rate ) :
    field_length(f_length),
    rad_sens(r_sens),
    rad_comm(r_comm),
    pop_size(pop),
    total_gen(t_gen),
    mut_rate(m_rate),
    cross_rate(c_rate)
{
    QGridLayout* layout = new QGridLayout(this) ;

    inFieldLength = new QSpinBox(this) ;
    inRadSens = new QSpinBox(this) ;
    inRadComm = new QSpinBox(this) ;
    inPopSize = new QSpinBox(this) ;
    inTotalGen = new QSpinBox(this) ;
    inCrossRate = new QSpinBox(this) ;
    inMutRate = new QSpinBox(this) ;

    QLabel* label ;

    label = new QLabel(tr("Field Length:"), this );
    layout->addWidget( label, 0, 0, 1, 1 );
    label = new QLabel(tr("Radius of Sensing:"), this );
    layout->addWidget( label, 1, 0, 1, 1 );
    label = new QLabel(tr("Radius of Communication:"), this );
    layout->addWidget( label, 2, 0, 1, 1 );
    label = new QLabel(tr("Population:"), this );
    layout->addWidget( label, 3, 0, 1, 1 );
    label = new QLabel(tr("Total Generations:"), this );
    layout->addWidget( label, 4, 0, 1, 1 );
    label = new QLabel(tr("Crossover Rate(%):"), this );
    layout->addWidget( label, 5, 0, 1, 1 );
    label = new QLabel(tr("Mutation Rate(%):"), this );
    layout->addWidget( label, 6, 0, 1, 1 );

    inFieldLength->setRange( 0, 500 );
    inRadSens->setRange( 0, 100 );
    inRadComm->setRange( 0, 100 );
    inPopSize->setRange( 0, 500 );
    inTotalGen->setRange( 0, 5000 ) ;
    inCrossRate->setRange( 0, 100 );
    inMutRate->setRange( 0, 100 ) ;

    inFieldLength->setValue( field_length ) ;
    inRadSens->setValue( rad_sens );
    inRadComm->setValue( rad_comm );
    inPopSize->setValue( pop_size );
    inTotalGen->setValue( total_gen );
    inCrossRate->setValue( 100*cross_rate );
    inMutRate->setValue( 100*mut_rate );


    layout->addWidget( inFieldLength, 0, 1, 1, 1 );
    layout->addWidget( inRadSens, 1, 1, 1, 1 );
    layout->addWidget( inRadComm, 2, 1, 1, 1 );
    layout->addWidget( inPopSize, 3, 1, 1, 1 );
    layout->addWidget( inTotalGen, 4, 1, 1, 1 );
    layout->addWidget( inCrossRate, 5, 1, 1, 1 );
    layout->addWidget( inMutRate, 6, 1, 1, 1 );

    QHBoxLayout* vLayout = new QHBoxLayout ;

    QPushButton* okey = new QPushButton("Okey") ;
    QPushButton* cancel = new QPushButton("Cancel") ;

    vLayout->addWidget( okey, 0 ) ;
    vLayout->addWidget( cancel, 0 ) ;
    layout->addLayout( vLayout, 7, 0, 1, 2 ) ;

    this->setLayout( layout );


    connect( okey, &QPushButton::clicked, this, &SetDialog::setData ) ;
    connect( cancel, &QPushButton::clicked, this, &SetDialog::reject ) ;

}

SetDialog::~SetDialog()
{
    delete inFieldLength ;
    delete inRadSens ;
    delete inRadComm ;
    delete inPopSize ;
    delete inTotalGen ;
    delete inCrossRate ;
    delete inMutRate ;
}

void SetDialog::setData()
{
    field_length = inFieldLength->value() ;
    rad_sens = inRadSens->value() ;
    rad_comm = inRadComm->value() ;
    pop_size = inPopSize->value() ;
    total_gen = inTotalGen->value() ;
    cross_rate = inCrossRate->value()/100.0 ;
    mut_rate = inMutRate->value()/100.0 ;

    emit accept() ;
}
