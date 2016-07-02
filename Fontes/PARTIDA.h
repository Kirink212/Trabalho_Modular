/*********************************************************************************
*
*  $MCD M�dulo de defini��o: PAR Partida para o jogo de Truco - M�dulo Principal
*
*  Arquivo gerado:              MESA.h
*  Letras identificadoras:      MES
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de 
*								programas redigidos em C
*
*  Projeto: INF 1301 - T4 de Programa��o Modular - Implementa��o do Truco
*  Autores: lfer, llages e bfranco
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor      Data       Observa��es
*     2       llages   27/jun/2016  retirada de fun��es e adi��o de novas
*									como por exemplo a LimparMesa e a LimparMao
*     1       lfer	   11/jun/2016  in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     M�dulo principal que chama todos os outros m�dulos, criando todo o ambiente
*	  prop�cio para um jogo de Truco ser simulado e jogado, com intera��o com o 
*	  jogador, cria��o de baralho, escolha de manilha, tratamento de empates, 
*	  dentre outras funcionalidades pr�prias deste jogo.
*
*********************************************************************************/

/***** Condi��es de retorno para verifica��es internas desta fun��o*****/
typedef enum {
		PAR_CondRetEquipeUmVenceu ,
		/* Equipe 1 venceu a M�o atual */

		PAR_CondRetEquipeDoisVenceu ,
		/* Equipe 2 venceu a M�o atual */

		PAR_CondRetEmpate ,
		/* Empate entre equipe 1 e equipe 2*/

		PAR_CondRetAceitaAumento ,
		/* Alguma equipe aceitou a proposta de aumento pelos advers�rios
		 * de pontua��o da M�o */

		PAR_CondRetRecusaAumento ,
		/* Alguma equipe recusou a proposta de aumento pelos advers�rios
		 * de pontua��o da M�o */

		PAR_CondRetEquipeUmTruco ,
		/* Equipe 1 ganhou porque equipe 2 recusou truco*/

		PAR_CondRetEquipeDoisTruco ,
		/* Equipe 2 ganhou porque equipe 1 recusou truco*/
} PAR_tpCondRet ;

/***********************************************************************
*
*  $FC Fun��o: PAR  &Gerenciar Partida
*
*  $ED Descri��o da fun��o
*     Gerencia todas as funcionalidades relacionadas � partida, como
*	  contabiliza��o da pontua��o geral e inser��o de elementos na 
*	  estrutura principal
*
***********************************************************************/
void PAR_GerenciarPartida();

/***********************************************************************
*
*  $FC Fun��o: MES  &Exibir placar
*
*  $ED Descri��o da fun��o
*     Exibe dois valores associando-os cada um a uma equipe.
*
*  $EP Par�metros
*     valor1 - valor a ser associado � equipe 1.
*     valor2 - valor a ser associado � equipe 2.
*
*  $FV Valor retornado
*     MES_CondRetOK    - placar exibido
*
***********************************************************************/
PAR_tpCondRet PAR_GerenciarRodada( int manilha , char* manilhaString );

/***********************************************************************
*
*  $FC Fun��o: MES  &Exibir placar
*
*  $ED Descri��o da fun��o
*     Exibe dois valores associando-os cada um a uma equipe.
*
*  $EP Par�metros
*     valor1 - valor a ser associado � equipe 1.
*     valor2 - valor a ser associado � equipe 2.
*
*  $FV Valor retornado
*     MES_CondRetOK    - placar exibido
*
***********************************************************************/
PAR_tpCondRet PAR_GerenciarMao();

/***********************************************************************
*
*  $FC Fun��o: MES  &Exibir placar
*
*  $ED Descri��o da fun��o
*     Exibe dois valores associando-os cada um a uma equipe.
*
*  $EP Par�metros
*     valor1 - valor a ser associado � equipe 1.
*     valor2 - valor a ser associado � equipe 2.
*
*  $FV Valor retornado
*     MES_CondRetOK    - placar exibido
*
***********************************************************************/PAR_tpCondRet PAR_PedirAumento(int equipeAtual , int jogadorAtual );

/***********************************************************************
*
*  $FC Fun��o: PAR &Limpar mesa
*
*  $ED Descri��o da fun��o
*     Reinicia todas as vari�veis referentes � Mesa ap�s o fim de uma
*	  rodada
*
***********************************************************************/
void PAR_LimparMesa();

/***********************************************************************
*
*  $FC Fun��o: PAR &Limpar mao
*
*  $ED Descri��o da fun��o
*     Reinicia todas as vari�veis referentes � M�o ap�s o fim de uma
*	  partida
*
***********************************************************************/
void PAR_LimparMao();