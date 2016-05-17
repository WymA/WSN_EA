#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>


class QPushButton ;
class QRadioButton ;
class QTextEdit;

class DashBoard : public QWidget
{
    Q_OBJECT
public:
    explicit DashBoard(QWidget *parent = 0);

signals:
    void startPauseEA() ;
    void stopEA() ;
    void settingSignal() ;
    void outputSignal() ;

    void displayCoverage() ;
    void displayNodes() ;
    void displayEnergy() ;

public slots:
    void printLine( const QString& line ) ;


private:

    QPushButton* startbt ;
    QPushButton* stopbt ;
    QPushButton* setbt ;
    QPushButton* outputbt ;
    QTextEdit* infoViewer ;



    QRadioButton* bCovergaeBt ;
    QRadioButton* bNodesBt ;
    QRadioButton* bEnergyBt ;
};

#endif // DASHBOARD_H
