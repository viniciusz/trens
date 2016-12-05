#ifndef CONEXAO_H
#define CONEXAO_H

#include <QObject>
#include <thread>
#include <chrono>

#include "trem.h"

using namespace std;

class Conexao : public QObject
{
   // Q_OBJECT
public:
    Conexao();
    ~Conexao();

    Trem *trem0;
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;

    void start(Trem * trem0, Trem * trem1, Trem * trem2, Trem * trem3 );
    void doprocessing (int sock);
    void run();
private:
   std::thread threadConexao;
};

#endif // CONEXAO_H

