#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>

class DashBoard : public QWidget
{
    Q_OBJECT
public:
    explicit DashBoard(QWidget *parent = 0);

signals:
    void startPauseEA() ;


public slots:

};

#endif // DASHBOARD_H
