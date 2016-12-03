#include "trem.h"

Trem::Trem(int id, int x, int y)
{
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
        case 1:
            //Esta funcionanado
            if (enable){
                emit updateGUI(id,x,y);

                //Verificar se ele ta entrando na zona critica
                if (y < 130 && x == 130)
                    y+=10;

                else if (y == 130 && x < 270)
                    x+=10;

                //Trilho de baixo
                else if (x == 270 && y > 30)
                    y-=10;

                //Trilho da esquerda
                else
                    x-=10;
            }
            break;

        case 2:
            //Esta funcionando
            if(enable){
                emit updateGUI(id, x, y);
                //Trilho de cima
                if (y == 140 && x < 270)
                    x+=10;
                //Trilho da direita
                else if (x == 270 && y < 240)
                    y+=10;
                //Trilho de baixo
                else if (x > 130 && y == 240)
                    x-=10;
                //Trilho da esquerda
                else
                    y-=10;
             }

            break;

        case 3:
            if(enable){
                emit updateGUI(id, x, y);
                //Trilho de cima
                if (y == 140 && x < 420)
                    x+=10;
                //Trilho da direita
                else if (x == 420 && y < 240)
                    y+=10;
                //Trilho de baixo
                else if (x > 280 && y == 240)
                    x-=10;
                //Trilho da esquerda
                else
                    y-=10;
            }
            break;

        case 4:
            if(enable){
                emit updateGUI(id, x, y);
                //Trilho de cima
                if (y == 250 && x < 420)
                    x+=10;
                //Trilho da direita
                else if (x == 420 && y < 350)
                    y+=10;
                //Trilho de baixo
                else if (x > 280 && y == 350)
                    x-=10;
                //Trilho da esquerda
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

