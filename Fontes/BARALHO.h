/***************************************************************************
*
*  $MCD M�dulo de defini��o: BAR  Baralho de Cartas
*
*  Arquivo gerado:              BARALHO.h
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes 
*								de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Autores: Lu�s Fernando Teixeira Bicalho (lfer),  
*			Leonardo Lages de Alencar(llages) e 
*			Bruno D'Almeida Franco (bfranco)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o	Autor		Data				Observa��es
*     5         llages  08/maio/2016        altera��o do nome de
*                                           vari�veis para seguir
*                                           os padr�es e adi��o de
*                                           assertivas
*     4			lfer	05/maio/2016		adi��o e revis�o de 
*											coment�rios no c�digo
*     3			lfer	03/maio/2016		cria��o das condi��es 
*											de retorno e adi��o de 
*                                           fun��es
*     2			llages	22/abr/2016			revis�o de implementa��o
*     1			lfer e	16/abr/2016			in�cio desenvolvimento
*				bfranco
*
*  $ED Descri��o do m�dulo
*     Implementa o representativo do baralho no jogo de Truco, podendo
*	  cri�-lo contendo 40 cartas, com valores entre 10 enumerados e naipes
*	  dentre 4 enumerados, al�m de liber�-lo e embaralh�-lo de forma 
*	  rand�mica.
*	  Al�m dessas tr�s a��es, os jogadores poder�o receber as cartas
*	  atrav�s da distribui��o delas a partir do topo do baralho, a��o feita
*	  pela fun��o de distribui��o.
*	  A��es como escolher a manilha da rodada e obter valores e naipes de
*	  respectivas quartas tamb�m s�o requisitos funcionais englobados pelo
*	  c�digo a seguir.
*
***************************************************************************/

#include <stdlib.h>
#include "LISTA.h"

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma carta */
typedef struct carta * BAR_tppCarta;

typedef enum {

         BAR_CondRetOK ,
               /* Concluiu corretamente */

         BAR_CondRetCartaNaoCriada ,
               /* Erro na cria��o da carta */

         BAR_CondRetFaltouMemoria ,
               /* Erro na inser��o de carta, falta de mem�ria*/

         BAR_CondRetCartaNaoExcluida ,
               /* Erro na exclus�o da carta */

         BAR_CondRetErroAndarListaVazia
               /* Erro ao tentar andar em uma lista vazia */

} BAR_tpCondRet ;

/***********************************************************************
*
*  $FC Fun��o: BAR &Cria baralho
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista de 40 
*	  cartas, ou seja, para o baralho, estando estas inicialmente
*	  inicializadas com valores em ordem crescente de naipe e valor.
*
*     Este ponteiro ser� utilizado pelas fun��es que utilizem o baralho.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados 
*     errados, a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/
	LIS_tppLista BAR_CriarBaralho( ) ;

/***********************************************************************
*
*  $FC Fun��o: BAR  &Liberar baralho
*
*  $ED Descri��o da fun��o
*     Libera a mem�ria relativa ao baralho fornecido como par�metro.
*     O par�metro ponteiro para a lista de cartas n�o � modificado.
*
*  $EP Par�metros
*     baralho - ponteiro para a lista de cartas a ser liberada
*
*  $FV Valor retornado
*     BAR_CondRetCartaNaoExcluida - baralho n�o foi liberado com sucesso
*     BAR_CondRetOK    - baralho liberado
*
***********************************************************************/

	BAR_tpCondRet BAR_LiberarBaralho( LIS_tppLista baralho ) ;

/***********************************************************************
*
*  $FC Fun��o: BAR  &Embaralhar cartas
*
*  $ED Descri��o da fun��o
*     Recebe como par�metro uma lista de cartas, embaralhando-as atrav�s
*	  da utiliza��o das fun��es rand() e srand(), que regularizam a
*     aleatoriedade.
*
*  $EP Par�metros
*     baralho - ponteiro para a lista de cartas a ser embaralhada
*
*  $FV Valor retornado
*     BAR_CondRetErroAndarListaVazia - lista de cartas vazia no elemento
*									   corrente.
*	  BAR_CondRetCartaNaoExcluida - carta n�o foi retirado do baralho
*	  BAR_CondRetFaltouMemoria - erro de falta de mem�ria
*     BAR_CondRetOK - baralho embaralhado
*
***********************************************************************/

	BAR_tpCondRet BAR_EmbaralharCartas( LIS_tppLista baralho ) ;

/***********************************************************************
*
*  $FC Fun��o: BAR  &Distribuir cartas
*
*  $ED Descri��o da fun��o
*     Distribui tr�s cartas do baralho j� embaralhado para cada um
*	  dos jogadores indo do primeiro ao �ltimo da lista jogador.
*
*  $EP Par�metros
*     baralho - ponteiro para a lista de cartas a ser distribu�da
*     jogador - ponteiro para a lista de jogadores que receber�o as cartas
*
*  $FV Valor retornado
*     BAR_CondRetCartaNaoExcluida - falha na transfer�ncia de cartas
*     BAR_CondRetOK    - cartas transferidas com sucesso
*
***********************************************************************/

	BAR_tpCondRet BAR_DistribuirCartas( LIS_tppLista baralho , LIS_tppLista jogador ) ;

/***********************************************************************
*
*  $FC Fun��o: BAR  &Escolher manilha
*
*  $ED Descri��o da fun��o
*     Escolher a manilha depois do baralho, o qual � passado como 
*     par�metro ter sido embaralhado e distribu�do para os jogadores.
*     A palavra que corresponde � manilha � escrita no ponteiro
*     recebido como par�metro.
*
***********************************************************************/

	int BAR_EscolherManilha( LIS_tppLista baralho , char* manilha ) ;

/***********************************************************************
*
*  $FC Fun��o: BAR  &Obter valor
*
*  $ED Descri��o da fun��o
*     Obt�m o valor da carta cujo ponteiro � passado como par�metro,
*     preenchendo a vari�vel "valor" caso seja passado um endere�o.
*
***********************************************************************/

	int BAR_ObterValor( BAR_tppCarta carta , char* valor ) ;

/***********************************************************************
*
*  $FC Fun��o: BAR  &Obter naipe
*
*  $ED Descri��o da fun��o
*     Obt�m o naipe da carta cujo ponteiro � passado como par�metro,
*     preenchendo a vari�vel "naipe" caso seja passado um endere�o.
*
***********************************************************************/

	int BAR_ObterNaipe( BAR_tppCarta carta , char* naipe ) ;