#include "Baralho.h"
#include <stdio.h>

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
	LIS_tppLista bar = LIS_CriarLista(BAR_liberaCarta);
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

void BAR_liberaCarta(void* elem)
{
	free(elem);
}

LIS_tppLista BAR_embaralhaCartas(){

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