/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Autores: Luís Fernando Teixeira Bicalho (lfer),  
*			Leonardo Lages de Alencar(llages) e 
*			Bruno D'Almeida Franco (bfranco)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data        Observações
*     1       lfer   16/abr/2016   início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa o representativo do baralho no jogo de Truco
*
*     
*
***************************************************************************/

#include <stdlib.h>
#include "LISTA.h"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma carta */
typedef struct carta Carta;

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
*	  dos jogadores indo do primeiro ao último da lista jog.
*
*  $EP Parâmetros
*     bar - ponteiro para a lista de cartas a ser distribuída
*     jog - ponteiro para a lista de jogadores que receberão as cartas
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
*
***********************************************************************/

	int BAR_EscolherManilha( LIS_tppLista baralho ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Obter valor
*
*  $ED Descrição da função
*     Obtém o valor da carta cujo ponteiro é passado como parâmetro
*
***********************************************************************/

	int BAR_ObterValor( Carta* carta ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Obter naipe
*
*  $ED Descrição da função
*     Obtém o naipe da carta cujo ponteiro é passado como parâmetro
*
***********************************************************************/

	int BAR_ObterNaipe( Carta* carta ) ;