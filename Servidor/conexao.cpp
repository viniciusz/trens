#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h> /* close() */
#include <string.h> /* memset() */

//#include <iostream>
//#include <cstdlib>



#include "conexao.h"

#include "trem.h"

#include <iostream>

using namespace std;

int velocidade;

Conexao::Conexao()
{

}

Conexao::~Conexao()
{
    threadConexao.join();
}

void Conexao::start(Trem * trem0, Trem * trem1, Trem * trem2, Trem * trem3 )
{
    this->trem0 = trem0;
    this->trem1 = trem1;
    this->trem2 = trem2;
    this->trem3 = trem3;
    threadConexao = std::thread(&Conexao::run, this);
}


void Conexao::run(){


    cout<<"Run foi rodado uma vez"<<endl;

   int sockfd, newsockfd, portno;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n, pid;
   socklen_t clilen;
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);

   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5001;

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);

   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }

   /* Now start listening for the clients, here
      * process will go in sleep mode and will wait
      * for the incoming connection
   */

   listen(sockfd,5);
   clilen = sizeof(cli_addr);

   while (1) {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
         doprocessing(newsockfd);
         exit(0);
   }
   close(sockfd);
}


void Conexao::doprocessing (int sock) {
   int n;
   char buffer[256];
   bzero(buffer,256);



   int i = 0;   while(true){
       n = read(sock,buffer,255);

       if (n < 0) {
          perror("ERROR reading from socket");
          exit(1);
       }


        switch(buffer[0]){
            case 'd': //Deligar trem
                switch(buffer[1]){
                    case '0':
                        trem0->setEnable(false);
                        break;
                    case '1':
                        trem1->setEnable(false);
                        break;
                    case '2':
                        trem2->setEnable(false);
                        break;
                    case '3':
                        trem3->setEnable(false);
                        break;
                    case 't':  //Todos os trem
                        trem0->setEnable(false);
                        trem1->setEnable(false);
                        trem2->setEnable(false);
                        trem3->setEnable(false);
                }
                break;

            case 'l': //ligar trem
                switch(buffer[1]){
                    case '0':
                        trem0->setEnable(true);
                        break;
                    case '1':
                        trem1->setEnable(true);
                        break;
                    case '2':
                        trem2->setEnable(true);
                        break;
                    case '3':
                        trem3->setEnable(true);
                        break;
                    case 't':  //Todos trem
                        trem0->setEnable(true);
                        trem1->setEnable(true);
                        trem2->setEnable(true);
                        trem3->setEnable(true);
                }
                break;
            case 'r': //Reduzir velocidade
                switch(buffer[1]){
                    case '0':
                        velocidade =trem0->getVelocidade();
                        cout<<"Velocidade0001: "<<velocidade<<endl;
                        velocidade = velocidade + 50;
                        if(velocidade>250) velocidade = 250;

                        cout<<"Velocidade0002: "<<velocidade<<endl;

                        trem0->setVelocidade(velocidade);
                        break;
                    case '1':
                        velocidade =trem1->getVelocidade();
                        velocidade = velocidade + 50;
                        if(velocidade>250) velocidade = 250;
                        trem1->setVelocidade(velocidade);
                        break;
                    case '2':
                    velocidade =trem2->getVelocidade();
                    velocidade = velocidade + 50;
                    if(velocidade>250) velocidade = 250;
                    trem2->setVelocidade(velocidade);

                        break;
                    case '3':
                        velocidade =trem3->getVelocidade();
                        velocidade = velocidade + 50;
                        if(velocidade>250) velocidade = 250;
                        trem3->setVelocidade(velocidade);
                        break;
            }

            case 'a': //aumentar velocidade
                switch(buffer[1]){
                    case '0':
                        velocidade =trem0->getVelocidade();
                        velocidade = velocidade - 50;
                        if(velocidade<50) velocidade = 50;
                        trem0->setVelocidade(velocidade);
                        break;
                    case '1':
                        velocidade =trem1->getVelocidade();
                        velocidade = velocidade - 50;
                        if(velocidade<50) velocidade = 50;
                        trem1->setVelocidade(velocidade);
                        break;
                    case '2':
                    velocidade =trem2->getVelocidade();
                    velocidade = velocidade - 50;
                    if(velocidade<50) velocidade = 50;
                    trem2->setVelocidade(velocidade);

                        break;
                    case '3':
                        velocidade =trem3->getVelocidade();
                        velocidade = velocidade - 50;
                        if(velocidade<50) velocidade = 50;
                        trem3->setVelocidade(velocidade);
                        break;
            }

        }

       //this_thread::sleep_for(chrono::milliseconds(0));

    }

}
