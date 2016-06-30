/***************************************************************************
*
*  $MCD Módulo de definição: MES Mesa para jogo de truco
*
*  Arquivo gerado:              MESA.h
*  Letras identificadoras:      MES
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 - T4 de Programação Modular - Implementação do Truco
*  Autores: lfer, llages e bfranco
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data       Observações
*     2       llages   27/jun/2016  alterações nas funções ReceberComando
*                                    e ExibirCartas
*     1       llages   11/jun/2016  início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa a interface para interagir com o usuário de
*        um jogo de truco.
*
***************************************************************************/

#include "LISTA.h"

/***** Declarações exportadas pelo módulo *****/

typedef enum {
	
	MES_CondRetOK,
	/* Retorno OK, funcionamento correto */
	
	MES_CondRetFaltouMemoria,
	/* Faltou memória em alguma operação */
	
	MES_CondRetListaVazia,
	/* Lista a ser manipulada estava vazia */
	
	MES_CondRetMensagemVazia,
	/* Mensagem a ser escrita estava vazia */
	
	MES_CondRetMinMaiorMax,
	/* Valor minimo passado maior que o valor maximo */
	
	MES_CondRetListaNaoExiste,
	/* Lista a ser manipulada nao existe */
	
} MES_tpCondRet ;

/***********************************************************************
*
*  $FC Função: MES  &Exibir placar
*
*  $ED Descrição da função
*     Exibe dois valores associando-os cada um a uma equipe.
*
*  $EP Parâmetros
*     valor1 - valor a ser associado à equipe 1.
*     valor2 - valor a ser associado à equipe 2.
*
*  $FV Valor retornado
*     MES_CondRetOK    - placar exibido
*
***********************************************************************/

	MES_tpCondRet MES_ExibirPlacar( int valor1 , int valor2 ) ;

/***********************************************************************
*
*  $FC Função: MES  &Exibir cartas
*
*  $ED Descrição da função
*     Exibe todas as cartas contidas em uma lista.
*     A exibição das cartas consiste em numerá-las pela ordem
*      e escrever seu valor(palavra) e naipe(palavra) na tela.
*
*  $EP Parâmetros
*     pCartas - lista de cartas
*
*  $FV Valor retornado
*     MES_CondRetFaltouMemoria - faltou memória para alocação
*     MES_CondRetListaNaoExiste - parâmetro pCartas inválido
*     MES_CondRetListaVazia - lista de cartas está vazia
*     MES_CondRetOK    - cartas exibidas
*
***********************************************************************/

	MES_tpCondRet MES_ExibirCartas( LIS_tppLista pCartas ) ;

/***********************************************************************
*
*  $FC Função: MES  &Exibir valor
*
*  $ED Descrição da função
*     Exibe um valor(inteiro) na tela.
*
*  $EP Parâmetros
*     valor - valor a ser exibido.
*
*  $FV Valor retornado
*     MES_CondRetOK    - valor exibido
*
***********************************************************************/

	MES_tpCondRet MES_ExibirValor( int valor ) ;

/***********************************************************************
*
*  $FC Função: MES  &Exibir mensagem
*
*  $ED Descrição da função
*     Escreve a mensagem passada como parâmetro na tela.
*
*  $EP Parâmetros
*     mensagem - string contendo a mensagem a ser escrita.
*
*  $FV Valor retornado
*     MES_CondRetMensagemVazia - parâmetro mensagem inválido
*     MES_CondRetOK    - mensagem exibida
*
***********************************************************************/

	MES_tpCondRet MES_ExibirMensagem( char* mensagem ) ;

/***********************************************************************
*
*  $FC Função: MES  &Receber comando
*
*  $ED Descrição da função
*     Capta um valor(inteiro) que o usuário digitar e preenche
*      a variável comando com este.
*
*  $EP Parâmetros
*     comando - ponteiro para espaço onde o valor digitado será
*                armazenado.
*     min - valor mínimo que o usuário pode digitar
*     max - valor máximo que o usuário pode digitar
*
*  $FV Valor retornado
*     MES_CondRetMinMaiorMax - valor minimo maior que valor máximo
*     MES_CondRetOK    - comando recebido
*
***********************************************************************/

	MES_tpCondRet MES_ReceberComando( int* comando , int min , int max ) ;
	
/********** Fim do módulo de definição: MES  Mesa para jogo de truco **********/