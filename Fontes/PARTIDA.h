/*********************************************************************************
*
*  $MCD Módulo de definição: PAR Partida para o jogo de Truco - Módulo Principal
*
*  Arquivo gerado:              MESA.h
*  Letras identificadoras:      MES
*
*  Nome da base de software:    Arcabouço para a automação de testes de 
*								programas redigidos em C
*
*  Projeto: INF 1301 - T4 de Programação Modular - Implementação do Truco
*  Autores: lfer, llages e bfranco
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data       Observações
*     2       llages   27/jun/2016  retirada de funções e adição de novas
*									como por exemplo a LimparMesa e a LimparMao
*     1       lfer	   11/jun/2016  início desenvolvimento
*
*  $ED Descrição do módulo
*     Módulo principal que chama todos os outros módulos, criando todo o ambiente
*	  propício para um jogo de Truco ser simulado e jogado, com interação com o 
*	  jogador, criação de baralho, escolha de manilha, tratamento de empates, 
*	  dentre outras funcionalidades próprias deste jogo.
*
*********************************************************************************/

/***** Condições de retorno para verificações internas desta função*****/
typedef enum {
		PAR_CondRetEquipeUmVenceu ,
		/* Equipe 1 venceu a Mão atual */

		PAR_CondRetEquipeDoisVenceu ,
		/* Equipe 2 venceu a Mão atual */

		PAR_CondRetEmpate ,
		/* Empate entre equipe 1 e equipe 2*/

		PAR_CondRetAceitaAumento ,
		/* Alguma equipe aceitou a proposta de aumento pelos adversários
		 * de pontuação da Mão */

		PAR_CondRetRecusaAumento ,
		/* Alguma equipe recusou a proposta de aumento pelos adversários
		 * de pontuação da Mão */

		PAR_CondRetEquipeUmTruco ,
		/* Equipe 1 ganhou porque equipe 2 recusou truco*/

		PAR_CondRetEquipeDoisTruco ,
		/* Equipe 2 ganhou porque equipe 1 recusou truco*/
} PAR_tpCondRet ;

/***********************************************************************
*
*  $FC Função: PAR  &Gerenciar Partida
*
*  $ED Descrição da função
*     Gerencia todas as funcionalidades relacionadas à partida, como
*	  contabilização da pontuação geral e inserção de elementos na 
*	  estrutura principal
*
***********************************************************************/
void PAR_GerenciarPartida();

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
PAR_tpCondRet PAR_GerenciarRodada( int manilha , char* manilhaString );

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
PAR_tpCondRet PAR_GerenciarMao();

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
***********************************************************************/PAR_tpCondRet PAR_PedirAumento(int equipeAtual , int jogadorAtual );

/***********************************************************************
*
*  $FC Função: PAR &Limpar mesa
*
*  $ED Descrição da função
*     Reinicia todas as variáveis referentes à Mesa após o fim de uma
*	  rodada
*
***********************************************************************/
void PAR_LimparMesa();

/***********************************************************************
*
*  $FC Função: PAR &Limpar mao
*
*  $ED Descrição da função
*     Reinicia todas as variáveis referentes à Mão após o fim de uma
*	  partida
*
***********************************************************************/
void PAR_LimparMao();