/***************************************************************************
*
*  $MCD Módulo de definição: BAR  Baralho de Cartas
*
*  Arquivo gerado:              BARALHO.h
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Arcabouço para a automação de testes 
*								de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Autores: Luís Fernando Teixeira Bicalho (lfer),  
*			Leonardo Lages de Alencar(llages) e 
*			Bruno D'Almeida Franco (bfranco)
*
*  $HA Histórico de evolução:
*     Versão	Autor		Data				Observações
*     5         llages  08/maio/2016        alteração do nome de
*                                           variáveis para seguir
*                                           os padrões e adição de
*                                           assertivas
*     4			lfer	05/maio/2016		adição e revisão de 
*											comentários no código
*     3			lfer	03/maio/2016		criação das condições 
*											de retorno e adição de 
*                                           funções
*     2			llages	22/abr/2016			revisão de implementação
*     1			lfer e	16/abr/2016			início desenvolvimento
*				bfranco
*
*  $ED Descrição do módulo
*     Implementa o representativo do baralho no jogo de Truco, podendo
*	  criá-lo contendo 40 cartas, com valores entre 10 enumerados e naipes
*	  dentre 4 enumerados, além de liberá-lo e embaralhá-lo de forma 
*	  randômica.
*	  Além dessas três ações, os jogadores poderão receber as cartas
*	  através da distribuição delas a partir do topo do baralho, ação feita
*	  pela função de distribuição.
*	  Ações como escolher a manilha da rodada e obter valores e naipes de
*	  respectivas quartas também são requisitos funcionais englobados pelo
*	  código a seguir.
*
***************************************************************************/

#include <stdlib.h>
#include "LISTA.h"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma carta */
typedef struct carta * BAR_tppCarta;

typedef enum {

         BAR_CondRetOK ,
               /* Concluiu corretamente */

         BAR_CondRetCartaNaoCriada ,
               /* Erro na criação da carta */

         BAR_CondRetFaltouMemoria ,
               /* Erro na inserção de carta, falta de memória*/

         BAR_CondRetCartaNaoExcluida ,
               /* Erro na exclusão da carta */

         BAR_CondRetErroAndarListaVazia
               /* Erro ao tentar andar em uma lista vazia */

} BAR_tpCondRet ;

/***********************************************************************
*
*  $FC Função: BAR &Cria baralho
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista de 40 
*	  cartas, ou seja, para o baralho, estando estas inicialmente
*	  inicializadas com valores em ordem crescente de naipe e valor.
*
*     Este ponteiro será utilizado pelas funções que utilizem o baralho.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados 
*     errados, a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/
	LIS_tppLista BAR_CriarBaralho( ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Liberar baralho
*
*  $ED Descrição da função
*     Libera a memória relativa ao baralho fornecido como parâmetro.
*     O parâmetro ponteiro para a lista de cartas não é modificado.
*
*  $EP Parâmetros
*     baralho - ponteiro para a lista de cartas a ser liberada
*
*  $FV Valor retornado
*     BAR_CondRetCartaNaoExcluida - baralho não foi liberado com sucesso
*     BAR_CondRetOK    - baralho liberado
*
***********************************************************************/

	BAR_tpCondRet BAR_LiberarBaralho( LIS_tppLista baralho ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Embaralhar cartas
*
*  $ED Descrição da função
*     Recebe como parâmetro uma lista de cartas, embaralhando-as através
*	  da utilização das funções rand() e srand(), que regularizam a
*     aleatoriedade.
*
*  $EP Parâmetros
*     baralho - ponteiro para a lista de cartas a ser embaralhada
*
*  $FV Valor retornado
*     BAR_CondRetErroAndarListaVazia - lista de cartas vazia no elemento
*									   corrente.
*	  BAR_CondRetCartaNaoExcluida - carta não foi retirado do baralho
*	  BAR_CondRetFaltouMemoria - erro de falta de memória
*     BAR_CondRetOK - baralho embaralhado
*
***********************************************************************/

	BAR_tpCondRet BAR_EmbaralharCartas( LIS_tppLista baralho ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Distribuir cartas
*
*  $ED Descrição da função
*     Distribui três cartas do baralho já embaralhado para cada um
*	  dos jogadores indo do primeiro ao último da lista jogador.
*
*  $EP Parâmetros
*     baralho - ponteiro para a lista de cartas a ser distribuída
*     jogador - ponteiro para a lista de jogadores que receberão as cartas
*
*  $FV Valor retornado
*     BAR_CondRetCartaNaoExcluida - falha na transferência de cartas
*     BAR_CondRetOK    - cartas transferidas com sucesso
*
***********************************************************************/

	BAR_tpCondRet BAR_DistribuirCartas( LIS_tppLista baralho , LIS_tppLista jogador ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Escolher manilha
*
*  $ED Descrição da função
*     Escolher a manilha depois do baralho, o qual é passado como 
*     parâmetro ter sido embaralhado e distribuído para os jogadores.
*     A palavra que corresponde à manilha é escrita no ponteiro
*     recebido como parâmetro.
*
***********************************************************************/

	int BAR_EscolherManilha( LIS_tppLista baralho , char* manilha ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Obter valor
*
*  $ED Descrição da função
*     Obtém o valor da carta cujo ponteiro é passado como parâmetro,
*     preenchendo a variável "valor" caso seja passado um endereço.
*
***********************************************************************/

	int BAR_ObterValor( BAR_tppCarta carta , char* valor ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Obter naipe
*
*  $ED Descrição da função
*     Obtém o naipe da carta cujo ponteiro é passado como parâmetro,
*     preenchendo a variável "naipe" caso seja passado um endereço.
*
***********************************************************************/

	int BAR_ObterNaipe( BAR_tppCarta carta , char* naipe ) ;