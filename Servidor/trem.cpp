#include "trem.h"
#include "semaforo.h"

#include <iostream>

using namespace std;

Trem::Trem(int id, int x, int y)
{
    this->s1 = new Semaforo(0001, 1, IPC_CREAT|0600);
    this->s2 = new Semaforo(0002, 1, IPC_CREAT|0600);
    this->s3 = new Semaforo(0003, 1, IPC_CREAT|0600);

    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 250;
    enable = true;
}

Trem::~Trem()
{
    threadTrem.join();
}

void Trem::setVelocidade(int velocidade)
{
    this->velocidade = velocidade;
}

int Trem::getVelocidade()
{
    return this->velocidade;
}

void Trem::setEnable(bool enable)
{
    this->enable = enable;
}

void Trem::start()
{
    threadTrem = std::thread(&Trem::run,this);
}

void Trem::run()
{
    while(true){
        switch(id){


        case 0:
            if (enable)
            {
                //controle do semaforo entre AREA 0, ÁREA 1 e ÁREA 2
                if(x == 260 && y == 120){
                    s2->P();
                }else if(x == 290 && y == 100){
                    s2->V();
                }



                //controle do semaforo entre ÁREA 0 e ÁREA 1
                if(x == 150 && y == 100){
                    s1->P();
                }else if(x == 290 && y == 100){
                    s1->V();
                }


                emit updateGUI(id,x,y);
                if (x > 150 && y == 20)
                    x-=10;
                else if (x == 150 && y < 120)
                    y+=10;
                else if (x < 290 && y == 120)
                    x+=10;
                else
                   y-=10;
            }
        break;


        case 1:
            if (enable)
            {


                //controle do semaforo entre ÁREA 1 e ÁREA 2
               if(x == 270 && y == 120){

                    cout<<"Trem 1 entrou na zona critica"<<endl;

                    s2->P();
                }
               if(x == 270 && y == 220){

                   cout<<"Trem 1 saiu da zona critica"<<endl;

                    s2->V();
                }



                //controle do semaforo entre ÁREA 0 e ÁREA 1
                if(x == 150 && y == 140){
                    s1->P();
                }else if(x == 290 && y == 140){
                    s1->V();
                }



                emit updateGUI(id,x,y);
                if (y == 120 && x <290)
                    x+=10;
                else if (x == 290 && y < 220)
                    y+=10;
                else if (x > 150 && y == 220)
                    x-=10;
                else
                    y-=10;
            }
            break;
        case 2:
            if (enable)
            {



                //controle do semaforo entre ÁREA 1 e ÁREA 2
                if(x == 310 && y == 220){

                    cout<<"Trem 2 entrou na zona critica"<<endl;

                    s2->P();
                }
                if(x == 310 && y == 120){

                    cout<<"Trem 2 saiu da zona critica"<<endl;

                    s2->V();
                }

                //controle do semaforo entre ÁREA 2 e ÁREA 3
                if(x == 430 && y == 200){
                    s3->P();
                }else if(x == 290 && y == 200){
                    s3->V();
                }

                emit updateGUI(id,x,y);
                if (y == 120 && x < 430)
                    x+=10;
                else if (x == 430 && y < 220)
                    y+=10;
                else if (x > 290 && y == 220)
                    x-=10;
                else
                    y-=10;
            }
            break;

        case 3:
            if (enable)
            {

                //controle do semaforo entre ÁREA 1, ÁREA 2 e AREA 3
                if(x == 290 && y == 250){
                    s2->P();
                }else if(x == 320 && y == 220){
                    s2->V();
                }


                //controle do semaforo entre ÁREA 2 e ÁREA 3
                if(x == 290 && y == 250){
                    s3->P();
                }else if(x == 430 && y == 250){
                    s3->V();
                }




                emit updateGUI(id,x,y);
                if (y == 220 && x < 430)
                    x+=10;
                else if (x == 430 && y < 320)
                    y+=10;
                else if (x > 290 && y == 320)
                    x-=10;
                else
                    y-=10;
            }
            break;

        default:
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}
