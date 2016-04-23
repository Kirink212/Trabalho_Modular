#include "Baralho.h"
#include <stdio.h>
#include <time.h>

typedef enum valor {
	QUATRO,
	CINCO,
	SEIS,
	SETE,
	DAMA,
	VALETE,
	REI,
	AS,
	DOIS,
	TRES
} Valor;
typedef enum naipe {
	OUROS,
	ESPADAS,
	COPAS,
	PAUS
} Naipe;

struct carta {
	Valor valor;
	Naipe naipe;
};

LIS_tppLista BAR_criaBaralho()
{
	int i, j;
	Valor val[10] = {QUATRO, CINCO, SEIS, SETE, DAMA, VALETE, REI, AS, DOIS, TRES};
	Naipe nap[4] = {OUROS, ESPADAS, COPAS, PAUS};
	Carta* card=NULL;
	LIS_tppLista bar = LIS_CriarLista(NULL);
	for(i=0; i<4; i++)
	{
		for(j=0; j<10 ;j++)
		{
			card = (Carta*) malloc(sizeof(Carta));
			if(card == NULL)
			{
				printf("Erro na criação de carta");
				exit(1);
			}
			card->naipe = nap[i];
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
	Carta* card = (Carta*) LIS_ObterValor(baralho);
	IrInicioLista(baralho);
	while(card != NULL)
	{
		if (LIS_ExcluirElemento(baralho) != LIS_CondRetOK)
		{
			printf("Erro na exclusao de carta");
			exit(1);
		}
		free(card);
		card= (Carta*) LIS_ObterValor(baralho);
	}
}

void BAR_embaralhaCartas(LIS_tppLista baralho)
{
	int random, i;
	void* carta;
	srand(time(NULL));
	for(i=0;i<50;i++)
	{
		random = rand()%40;
		IrInicioLista(baralho);
		if (LIS_AvancarElementoCorrente(baralho, random) == LIS_CondRetListaVazia)
		{
			printf("Erro ao tentar andar em uma lista vazia");
			exit(1);
		}
		carta=LIS_ObterValor(baralho);
		if (LIS_ExcluirElemento(baralho) != LIS_CondRetOK)
		{
			printf("Erro na exclusao de carta");
			exit(1);
		}
		random = rand()%40;
		IrInicioLista(baralho);
		if (LIS_AvancarElementoCorrente(baralho, random) == LIS_CondRetListaVazia)
		{
			printf("Erro ao tentar andar em uma lista vazia");
			exit(1);
		}
		if (LIS_InserirElementoAntes(baralho, carta) != LIS_CondRetOK)
		{
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

void exibeBaralho(LIS_tppLista baralho)
{
	void *carta_void=NULL;
	Carta* carta;
	int qt=0;
	IrFinalLista(baralho);
	carta_void=LIS_ObterValor(baralho);
	carta=(Carta*) carta_void;
	while(carta != NULL)
	{
		carta=(Carta*) carta_void;
		qt++;
		printf("Valor: %d\tNaipe: %d\tQuantidade de cartas: %d\n", carta->valor, carta->naipe, qt);
		if (LIS_AvancarElementoCorrente(baralho, -1) != LIS_CondRetOK)
		{
			printf("Erro na exclusao de carta ou fim da lista\n");
			exit(1);
		}
		carta_void=LIS_ObterValor(baralho);
	}
}