#ifndef TREM_H
#define TREM_H

#include <QObject>
#include <thread>
#include <chrono>
#include "semaforo.h"

using namespace std;

class Trem : public QObject
{
    Q_OBJECT
public:
    Trem(int,int,int);
    ~Trem();
    void start();
    void run();
    void setVelocidade(int);
    int getVelocidade();
    void setEnable(bool);

signals:
    void updateGUI(int,int,int);

private:
   std::thread threadTrem;
   Semaforo *s1;
   Semaforo *s2;
   Semaforo *s3;
   int id;
   int x;
   int y;
   int velocidade;
   bool enable;
};

#endif // TREM_H
