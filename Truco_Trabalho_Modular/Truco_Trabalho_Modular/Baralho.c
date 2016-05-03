#include "Baralho.h"
#include <stdio.h>
#include <time.h>

/***********************************************************************
*
*  $TC Tipo de dados: BAR Lista de Valores
*
*  $ED Descrição do tipo
*     Tipos de valores possíveis para um elemento do tipo carta
*
*
***********************************************************************/
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

/***********************************************************************
*
*  $TC Tipo de dados: BAR Lista de Naipes
*
*  $ED Descrição do tipo
*     Tipos de naipes possíveis para um elemento do tipo carta
*
*
***********************************************************************/
typedef enum naipe {
	OUROS,
	ESPADAS,
	COPAS,
	PAUS
} Naipe;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Tipo carta
*
*
***********************************************************************/
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
				return NULL;
			}
			card->naipe = nap[i];
			card->valor = val[j];
			if(LIS_InserirElementoApos(bar, card) != LIS_CondRetOK)
			{
				return NULL;
			}
		}
	}
	return bar;
}

BAR_tpCondRet BAR_liberaBaralho(LIS_tppLista baralho)
{
	Carta* card = (Carta*) LIS_ObterValor(baralho);
	LIS_IrInicioLista(baralho);
	while(card != NULL)
	{
		if (LIS_ExcluirElemento(baralho) != LIS_CondRetOK)
		{
			return BAR_CondRetCartaNaoExcluida;
		}
		free(card);
		card= (Carta*) LIS_ObterValor(baralho);
	}
	return BAR_CondRetOK;
}

BAR_tpCondRet BAR_embaralhaCartas(LIS_tppLista baralho)
{
	int random, i;
	void* carta;
	srand(time(NULL));
	for(i=0;i<50;i++)
	{
		random = rand()%40;
		LIS_IrInicioLista(baralho);
		if (LIS_AvancarElementoCorrente(baralho, random) == LIS_CondRetListaVazia)
		{
			return BAR_CondRetErroAndarListaVazia;
		}
		carta=LIS_ObterValor(baralho);
		if (LIS_ExcluirElemento(baralho) != LIS_CondRetOK)
		{
			return BAR_CondRetCartaNaoExcluida;
		}
		random = rand()%40;
		LIS_IrInicioLista(baralho);
		if (LIS_AvancarElementoCorrente(baralho, random) == LIS_CondRetListaVazia)
		{
			return BAR_CondRetErroAndarListaVazia;
		}
		if (LIS_InserirElementoAntes(baralho, carta) != LIS_CondRetOK)
		{
			return BAR_CondRetCartaNaoInseridaAntes;
		}
	}
	return BAR_CondRetOK;
}

BAR_tpCondRet BAR_distribuiCartas(LIS_tppLista bar, LIS_tppLista jog)
{
	void* card;
	int i;
	for(i=0; i<3; i++)
	{
		LIS_IrInicioLista(bar);
		card = LIS_ObterValor(bar) ;
		if(LIS_ExcluirElemento(bar) != LIS_CondRetOK)
		{
			return BAR_CondRetCartaNaoExcluida;
		}
		LIS_InserirElementoApos(jog, card);
	}
	return BAR_CondRetOK;
}

void* BAR_EscolheManilha(LIS_tppLista bar)
{
	int i;
	Valor val[10] = {QUATRO, CINCO, SEIS, SETE, DAMA, VALETE, REI, AS, DOIS, TRES};
	Naipe nap[4] = {OUROS, ESPADAS, COPAS, PAUS};
	Carta *vira, *manilha;
	LIS_IrInicioLista(bar);
	vira = (Carta*)LIS_ObterValor(bar);
	for(i=0; i<10; i++)
	{
		if(val[i] == vira->valor)
		{
			manilha->valor = val[i+1];
			break;
		}
	}
	manilha->naipe = vira->naipe;
	return manilha;
}


void exibeBaralho(LIS_tppLista baralho)
{
	void *carta_void=NULL;
	Carta* carta;
	int qt=0;
	LIS_IrFinalLista(baralho);
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