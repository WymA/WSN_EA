#ifndef EATHREAD_H
#define EATHREAD_H

#include <QThread>


class EABase ;
class NSGA2 ;
class MOEAD ;
class Controller ;



class EAThread : public QThread
{
    Q_OBJECT
public:
    explicit EAThread(QObject *parent = 0);
    ~EAThread() ;

    void set2NSGA2() ;
protected:
    void run() ;

private:
    Controller* controller ;
    EABase* ea ;

};

#endif // EATHREAD_H
