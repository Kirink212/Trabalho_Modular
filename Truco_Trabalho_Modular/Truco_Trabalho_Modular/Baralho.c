#include "Baralho.h"
#include <stdio.h>
#include <time.h>

typedef enum valor {QUATRO, CINCO, SEIS, SETE, DAMA, VALETE, REI, AS, DOIS, TRES}Valor;
typedef enum naipe {OUROS, ESPADAS, COPAS, PAUS} Naipe;

struct carta{
	Valor valor;
	Naipe naipe;
};

LIS_tppLista BAR_criaBaralho()
{
	int i, j;
	Valor val[10] = {QUATRO, CINCO, SEIS, SETE, DAMA, VALETE, REI, AS, DOIS, TRES};
	Naipe nap[4] = {OUROS, ESPADAS, COPAS, PAUS};
	LIS_tppLista bar = LIS_CriarLista(NULL);
	for(i=0; i<4; i++)
	{
		Carta* card = (Carta*) malloc(sizeof(Carta));
		if(card == NULL)
		{
			printf("Erro na criação de cartas");
			exit(1);
		}
		card->naipe = nap[i];
		for(j=0; j<10 ;j++)
		{
			card->valor = val[j];
			if(LIS_InserirElementoApos(bar, card) != LIS_CondRetOK)
			{
				printf("Erro na inserção de carta");
				exit(1);
			}
		}
	}
	return bar;
}

void BAR_liberaBaralho(LIS_tppLista baralho)
{
	IrInicioLista(baralho);
	void* carta=LIS_ObterValor(baralho);
	while(carta != NULL) {
		if (LIS_ExcluirElemento(baralho) != LIS_CondRetOK) {
			printf("Erro na exclusao de carta");
			exit(1);
		}
		free(carta);
		carta=LIS_ObterValor(baralho);
	}
}

void BAR_embaralhaCartas(LIS_tppLista baralho){
	srand(time(NULL));
	int random,i;
	for(i=0;i<50;i++) {
		random = rand(0,39);
		IrInicioLista(baralho);
		if (LIS_AvancarElementoCorrente(baralho, random) != LIS_CondRetOK) {
			printf("Erro ao tentar andar na lista");
			exit(1);
		}
		void* carta=LIS_ObterValor(baralho);
		if (LIS_ExcluirElemento(baralho) != LIS_CondRetOK) {
			printf("Erro na exclusao de carta");
			exit(1);
		}
		random = rand(0,39);
		IrInicioLista(baralho);
		if (LIS_AvancarElementoCorrente(baralho, random) != LIS_CondRetOK) {
			printf("Erro ao tentar andar na lista");
			exit(1);
		}
		if (LIS_InserirElementoAntes(baralho, carta) != LIS_CondRetOK) {
			printf("Erro ao tentar inserir valor na lista");
			exit(1);
		}
	}
}

void BAR_distribuiCartas(LIS_tppLista bar, LIS_tppLista jog)
{
	void* card;
	int i;
	for(i=0; i<3; i++)
	{
		IrInicioLista(bar);
		card = LIS_ObterValor(bar) ;
		if(LIS_ExcluirElemento(bar) != LIS_CondRetOK)
		{
			printf("Erro na exclusão de carta");
			exit(1);
		}
		LIS_InserirElementoApos(jog, card);
	}
}