#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>


class QPushButton ;
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

public slots:
    void printLine( const QString& line ) ;

private:

    QPushButton* startbt ;
    QPushButton* stopbt ;
    QPushButton* setbt ;
    QTextEdit* infoViewer ;

};

#endif // DASHBOARD_H
