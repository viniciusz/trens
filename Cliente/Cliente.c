#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "arpa/inet.h"
#include "netdb.h"
#include "netinet/in.h"
#include "sys/wait.h"

#include <unistd.h>

#define PORTA 5001
#define ERRO -1
#define TAMMAX 5 //tamanho maximo da string

struct sockaddr_in network;

int sock, newSock, resp, strucsize;

char msg [TAMMAX];

//Se conecta com o servidor que tiver seu endereço IP passado como parâmetro
void conectar(char* endereco){
	sock = socket (AF_INET, SOCK_STREAM, 0);
	if (sock == ERRO) {
	  perror ("Socket");
	  exit (0);
	  }
	bzero ((char *)&network, sizeof (network));
	network.sin_family = AF_INET;
	network.sin_port = htons (PORTA);
	network.sin_addr.s_addr = inet_addr (endereco);
	strucsize = sizeof (network);
	resp = connect (sock, (struct sockaddr *)&network, strucsize);
	if (resp == ERRO) {
	  perror ("Connect");
	  exit (0);
	  }
	fprintf (stdout, "Conectado em %s\n", endereco);
}


//Desconecta do servidor
void desconectar(){
    close(sock);
}


//envia mensagem para o servidor
void enviar(char* msg){
	send (sock, msg, sizeof (msg), 0);
  	if (!strcmp (msg, "exit"))
    	{
    	 exit (0);
    	}
}

//Liga todos os trens
void ligarTodos(){
	char *msg = "lt\0";
	enviar(msg);
}

//Liga o trem em que seu identificador for passado como parámetro
void ligarEspecifico(int trem){
	char msg[3];
	msg[0] = 'l';
	msg[2] = '\0';
	switch(trem){
		case 0:
			msg[1] = '0';
			break;
		case 1:
			msg[1] = '1';
			break;
		case 2:
			msg[1] = '2';
			break;
		case 3:
			msg[1] = '3';
			break;
	}
	enviar(msg);	
}

//Desliga todos os trens
void desligarTodos(){
	char *msg = "dt\0";
	enviar(msg);
}

//Desliga o trem em que seu identificador for passado como parámetro
void desligarEspecifico(int trem){
	char msg[3];
	msg[0] = 'd';
	msg[2] = '\0';
	switch(trem){
		case 0:
			msg[1] = '0';
			break;
		case 1:
			msg[1] = '1';
			break;
		case 2:
			msg[1] = '2';
			break;
		case 3:
			msg[1] = '3';
			break;
	}
	enviar(msg);	
}


/*
Função que aumenta a velocidade do trem em que seu identificador for passado por parametro.
Pode assumir os valores 0 (Trem amarelo), 1(Trem vermelho) 2(Trem azul) e 3(Trem preto).
*/
void aumentarVelocidade(int trem){

	char msg[3];
	
	msg[0] = 'a';
	msg[2] = '\0';

	switch(trem){
		case 0:
			msg[1] = '0';
			break;
		case 1:
			msg[1] = '1';
			break;
		case 2:
			msg[1] = '2';
			break;
		case 3:
			msg[1] = '3';
			break;
	}

	enviar(msg);	
}

/*
Função que Reduz a velocidade do trem em que seu identificador for passado por parametro.
Pode assumir os valores 0 (Trem amarelo), 1(Trem vermelho) 2(Trem azul) e 3(Trem preto).
*/
void reduzirVelocidade(int trem){
	char msg[3];

	msg[0] = 'r';
	msg[2] = '\0';

	switch(trem){
		case 0:
			msg[1] = '0';
			break;
		case 1:
			msg[1] = '1';
			break;
		case 2:
			msg[1] = '2';
			break;
		case 3:
			msg[1] = '3';
			break;
	}
	
	enviar(msg);
}




void mostarListaDeTrens(){
	printf("---------------------------\n");
	printf("-0-----Amarelo-------------\n");
	printf("-1-----Vermelho------------\n");
	printf("-2-----Azul----------------\n");
	printf("-3-----Preto---------------\n");
	printf("---------------------------\n");
}
void mostrarMenuPrincipal(){
	printf("---------------------------\n");
	printf("-1-----Conectar------------\n");
	printf("-2-----Desconectar---------\n");
	printf("-3-----ligar todos---------\n");
	printf("-4-----ligar específico----\n");
	printf("-5-----desligar todos------\n");
	printf("-6-----desligar específico-\n");
	printf("-7-----Aumentar velocidade-\n");
	printf("-8-----Reduzir velocidade--\n");
	printf("---------------------------\n");
}

int main(){
	char ip[50];
	int conectado = 0;

	while(true){
		mostrarMenuPrincipal();
		int opcao;
		int trem;
		scanf("%d",&opcao);
		if(opcao ==1 && conectado ==1){
			printf("Voce ja esta conectado\n");
		}else if(opcao!=1 && conectado == 0){
			printf("Voce nao pode realizar esta operacao antes de se conectar ao servidor\n");
		}else{
			switch(opcao){
				case 1:
					conectado = 1;
					printf("Entre o endereco IP do servidor");
					scanf("%s",ip);
					conectar(ip);
					break;
				case 2:
					conectado = 0;
					desconectar();
					break;
				case 3:
					ligarTodos();
					break;
				case 4:
					mostarListaDeTrens();
					scanf("%d",&trem);
					ligarEspecifico(trem);
					break;
				case 5:
					desligarTodos();
					break;
				case 6:
					mostarListaDeTrens();
					scanf("%d",&trem);
					desligarEspecifico(trem);
					break;
				case 7:
					mostarListaDeTrens();
					scanf("%d",&trem);
					aumentarVelocidade(trem);
					break;
				case 8:
					mostarListaDeTrens();
					scanf("%d",&trem);
					reduzirVelocidade(trem);
					break;
			}
		}
		
	}
	return 0;
}