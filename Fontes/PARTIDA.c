/***************************************************************************
*  $MCI M�dulo de implementa��o: BAR  Baralho de Cartas
*
*  Arquivo gerado:              BARALHO.c
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes 
*								de programas redigidos em C
*
*  Projeto: INF 1301 - T2 de Programa��o Modular - Implementa��o do Truco
*  Autores: Lu�s Fernando Teixeira Bicalho (lfer),  
*			Leonardo Lages de Alencar(llages) e 
*			Bruno D'Almeida Franco (bfranco)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o	Autor		Data				Observa��es
*     6         llages  01/jul/2016         implementa��o da "Mao de Onze"
*											internamente na GerenciarMao
*     5         llages  30/jun/2016			adi��o e revis�o de 
*											coment�rios no c�digo
*     4			lfer	28/jun/2016			implementa��o das fun��es
*											de gerenciamento de m�o e
*											rodada
*     3			lfer	26/jun/2016			cria��o da nova estrutura
*											para a jogada
*     2			lfer	22/jun/2016			implementa��o da fun��o 
*											de gerenciamente da Partida
*     1			lfer	16/jun/2016			in�cio desenvolvimento
*
***************************************************************************/

#include "PARTIDA.h"
#include "BARALHO.h"
#include <stdlib.h>
#include "LISTA.h"
#include "MESA.h"

/***********************************************************************
*
*  $TC Tipo de dados: PAR Lista de Jogadas
*
*  $ED Descri��o do tipo
*     Armazenamento dos dados respectivos a cada jogada realizada
*	  em uma rodada.
*
***********************************************************************/
typedef struct jogada PAR_tppJogada ;
struct jogada {

	BAR_tppCarta carta ;
				 /* Carta utilizada na realiza��o da jogada */
	int equipe ,
		/* �ndice respectivo � equipe do jogador indexado */
		jogador ;
		/* �ndice respectivo ao jogador realizando a jogada */
} ;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Dados globais
*
*  $ED Descri��o do tipo
*     Estrutura Pincipal (Lista de Listas), seguida das vari�veis
*	  globais do m�dulo Partida.
*
*****************************************************************************/
static LIS_tppLista estruturaPrincipal ;

static int numeroTotalJogadores ,
		   /* Referencia o n�mero total de jogadores */
		   pontuacaoPartidaEquipeUm ,
		   /* Referencia a pontua��o total da equipe um 
			* na Partida atual */
		   pontuacaoPartidaEquipeDois ,
		   /* Referencia a pontua��o total da equipe dois
		    * na Partida atual */
		   pontuacaoMaoEquipeUm ,
		   /* Referencia a pontua��o total da equipe um
		    * na M�o atual */
		   pontuacaoMaoEquipeDois ,
		   /* Referencia a pontua��o total da equipe dois
		    * na M�o atual */
		   valorMao ,
		   /* A pontua��o que ser� adicionada ao ganhador
		    * da M�o atual */
		   equipeMaoDeOnze = -1 ,
		   /* Inicializa��o da vari�vel que referencia 
		    * equipe que chegou aos 11 pontos primeiramente */
		   equipeVencedora = 1 ,
		   /* Referencia a equpe vencedora da Rodada atual */
		   jogadorVencedor = 0 ;
		   /*Referencia o jogador vencedor da Rodada atual*/

/***************************************************************************
*
*  Fun��o: BAR  &Criar baralho
*  ****/
void PAR_GerenciarPartida( )
{
   int numeroAtualJogadores ,
	   vencedorMao ,
	   retornoLista ;
   
   LIS_tppLista equipeUm ,
				equipeDois ,
				jogador ;
				
   /* Criar a estrutura principal */
   estruturaPrincipal = LIS_CriarLista ( NULL ) ;
   
   MES_ExibirMensagem( "Qual o numero de jogadores?\n1 - 2\n2 - 4\n3 - 6" , 0 ) ;
   MES_ReceberComando( &numeroTotalJogadores , 1 , 3 ) ;
   system( "cls" ) ;
   numeroTotalJogadores = numeroTotalJogadores * 2 ;
				
   /* Faltam as checagens de retorno do lista */
   /* Criar as equipes */
   equipeUm = LIS_CriarLista ( NULL ) ;
   equipeDois = LIS_CriarLista ( NULL ) ;
   
   /* Inserir as equipes na lista de listas */
   LIS_InserirElementoApos( estruturaPrincipal , equipeUm ) ;
   LIS_InserirElementoApos( estruturaPrincipal , equipeDois ) ;
   
   /* Criar e inserir os jogadores nas equipes */
   for ( numeroAtualJogadores = 0 ;
		 numeroAtualJogadores < numeroTotalJogadores ;
		 numeroAtualJogadores += 2 )
   {
		jogador = LIS_CriarLista( NULL ) ;
		LIS_InserirElementoAntes( equipeUm , jogador ) ;
		jogador = LIS_CriarLista( NULL ) ;
		LIS_InserirElementoAntes( equipeDois , jogador ) ;
   }
   
   /* Ok! A lista de listas est� pronta.
   *  A cria��o do baralho � por parte da m�o, pois cada
   *  uma ir� utilizar um baralho novo. A mesa tamb�m ser�
   *  criada l�, pois ap�s cada rodada ser� limpa. Agora
   *  � hora de iniciar a m�o. */
   /* A partida ir� durar at� que alguma das equipes
   *  chegue a 12 pontos. */
   while ( pontuacaoPartidaEquipeUm < 12 &&
		   pontuacaoPartidaEquipeDois < 12 )
   {
	   vencedorMao = PAR_GerenciarMao() ;
	   if ( vencedorMao == PAR_CondRetEquipeUmVenceu )
	   {
		   pontuacaoPartidaEquipeUm += valorMao ;
	   }
	   else if ( vencedorMao == PAR_CondRetEquipeDoisVenceu )
	   {
		   pontuacaoPartidaEquipeDois += valorMao ;
	   }

	   /* Se alguma equipe atingir 11 pontos, a m�o
	   *  de onze � ativada. */
	   if ( equipeMaoDeOnze == -1 )
	   {
		   if ( pontuacaoPartidaEquipeUm == 11 )
		   {
			   equipeMaoDeOnze = 1 ;
		   }/* if */
		   else if ( pontuacaoPartidaEquipeDois == 11 )
		   {
			   equipeMaoDeOnze = 2 ;
		   }/* else if */
	   }/* if */
   }/* while */

   MES_ExibirPlacar( pontuacaoPartidaEquipeUm ,
					 pontuacaoPartidaEquipeDois ) ;

   /* O �nico jeito de sair do loop � com
   *  alguma equipe atingindo 12 ou mais pontos.
   *  Como apenas uma equipe pode pontuar por vez,
   *  com certeza uma tem mais pontos que a outra. */
   if ( pontuacaoPartidaEquipeUm >
		pontuacaoPartidaEquipeDois )
   {
	   MES_ExibirMensagem( "Equipe 1 venceu." , 1 ) ;
   }/* if */

   else
   {
	   MES_ExibirMensagem( "Equipe 2 venceu." , 1 ) ;
   }/* else */
   
   /* Limpar as listas de jogadores e a estrutura
   *  principal. */
   LIS_IrInicioLista( equipeUm ) ;
   jogador = ( LIS_tppLista ) LIS_ObterValor( equipeUm ) ;
   if ( jogador )
   {
	   LIS_DestruirLista( jogador ) ;
   }/* if */
   retornoLista = LIS_ExcluirElemento( equipeUm ) ;
   
   while( retornoLista != LIS_CondRetListaVazia )
   {
	   jogador = ( LIS_tppLista ) LIS_ObterValor( equipeUm ) ;

	   if ( jogador )
	   {
		   LIS_DestruirLista( jogador ) ;
	   }/* if */

	   retornoLista = LIS_ExcluirElemento( equipeUm ) ;
   }/* while */
   
   LIS_DestruirLista( equipeUm ) ;

   LIS_IrInicioLista( equipeDois ) ;

   jogador = ( LIS_tppLista ) LIS_ObterValor( equipeDois ) ;

   if ( jogador )
   {
	   LIS_DestruirLista( jogador ) ;
   }/* if */

   retornoLista = LIS_ExcluirElemento( equipeUm ) ;
   
   while( retornoLista != LIS_CondRetListaVazia )
   {
	   jogador = ( LIS_tppLista ) LIS_ObterValor( equipeDois ) ;

       if ( jogador )
	   {
		   LIS_DestruirLista( jogador ) ;
	   }/* if */

	   retornoLista = LIS_ExcluirElemento( equipeDois ) ;
   }/* while */
   
   LIS_DestruirLista( equipeDois ) ;

   LIS_DestruirLista( estruturaPrincipal ) ;

}

/***************************************************************************
*
*  Fun��o: BAR  &Criar baralho
*  ****/
PAR_tpCondRet PAR_GerenciarRodada( int manilha , char* manilhaString )
{
    int quantidadeJogadas ,
		equipeAtual = equipeVencedora - 1 ,
		retornoLista ,
		jogadorAtual = jogadorVencedor ,
		quantidadeCartas ,
		comando ,
		valorCarta ,
		valorMaiorCarta ,
		respostaAumento = -1 ;
	
	PAR_tppJogada *novaJogada ,
		   *jogadaMaiorCarta ;
	
	LIS_tppLista mesa ,
				 *equipes ,
				 jogador ,
				 cartasNaMesa ;
				 
	/* Criar a mesa */
	mesa = LIS_CriarLista( NULL ) ;
	/* Criar lista de cartas na mesa */
	cartasNaMesa = LIS_CriarLista( NULL ) ;
   
	/* Inserir a mesa na lista de listas */
	LIS_IrFinalLista( estruturaPrincipal ) ;
	LIS_InserirElementoApos( estruturaPrincipal , mesa ) ;
	
	/* Agora vamos pegar as equipes. Vamos utilizar
	*  um vetor para facilitar a transi��o entre equipes
	*  na realiza��o de jogadas. */
	equipes = ( LIS_tppLista* ) malloc( 2 * sizeof( LIS_tppLista ) ) ;
	LIS_IrInicioLista( estruturaPrincipal ) ;
	LIS_AvancarElementoCorrente( estruturaPrincipal , 1 ) ;
	equipes[0] = ( LIS_tppLista ) LIS_ObterValor( estruturaPrincipal ) ;
	LIS_AvancarElementoCorrente( estruturaPrincipal , 1 ) ;
	equipes[1] = ( LIS_tppLista ) LIS_ObterValor( estruturaPrincipal ) ;
	
	/* Ok, temos as listas das duas equipes. Agora temos
	*  que organizar os elementos correntes para os
	*  jogadores corretamente. */
	LIS_IrInicioLista( equipes[0] ) ;
	LIS_IrInicioLista( equipes[1] ) ;
	
	/* Ambos os elementos correntes est�o no come�o.
	*  Se a equipe 1 venceu, os �ndices dos jogadores
	*  que come�am a rodada s�o os mesmos, mas se a
	*  equipe 2 venceu, o �ndice do jogador da equipe
	*  1 � 1 a mais que o da equipe 2. */
	if ( equipeVencedora == 1 )
	{
		/* Equipe 1 venceu, jogadores de mesmo �ndice */
		LIS_AvancarElementoCorrente( equipes[0] , jogadorVencedor ) ;
		LIS_AvancarElementoCorrente( equipes[1] , jogadorVencedor ) ;
	}
	else
	{
		/* Equipe 2 venceu, jogador da equipe 1 com �ndice
		*  1 a mais que o da equipe 2. Se passar do fim da
		*  lista, volta ao jogador inicial. */
		LIS_AvancarElementoCorrente( equipes[1] , jogadorVencedor ) ;
		retornoLista = LIS_AvancarElementoCorrente( equipes[0] , jogadorVencedor + 1) ;
		if (retornoLista == LIS_CondRetFimLista )
		{
			LIS_IrInicioLista( equipes[0] ) ;
		}
	}
	
	/* Realizar a contagem de cartas para saber quantas op��es
	*  de jogada o jogador tem. Tanto faz o jogador, todos
	*  devem ter a mesma quantidade de cartas. */
	jogador = ( LIS_tppLista ) LIS_ObterValor( equipes[0] ) ;
	LIS_IrInicioLista( jogador ) ;
	for ( quantidadeCartas = 1 ;;
		  quantidadeCartas++)
	{
		if ( LIS_AvancarElementoCorrente( jogador , 1 ) == LIS_CondRetFimLista )
		{
			break ;
		}
	}
	/* Agora os elementos correntes est�o nas posi��es corretas
	*  para iniciar a rodada. */
	for ( quantidadeJogadas = 0 ; 
		  quantidadeJogadas < numeroTotalJogadores ;
		  quantidadeJogadas++ )
	{
		jogador = ( LIS_tppLista ) LIS_ObterValor( equipes[equipeAtual] ) ;
		/* Exibir placar da partida */
		MES_ExibirMensagem( "Placar da partida:" , 0 ) ;
		MES_ExibirPlacar( pontuacaoPartidaEquipeUm ,
						  pontuacaoPartidaEquipeDois ) ;
						  
		/* Exibir placar da m�o */
		MES_ExibirMensagem( "Placar da mao:" , 1 ) ;
		MES_ExibirPlacar( pontuacaoMaoEquipeUm ,
						  pontuacaoMaoEquipeDois ) ;
						  
		/* Exibir o valor atual da m�o */
		MES_ExibirMensagem( "O valor atual da mao e: " , 1 ) ;
		MES_ExibirValor( valorMao ) ;
		
		/* Exibir cartas na mesa */
		MES_ExibirMensagem( "As cartas atualmente na mesa sao:" , 1 ) ;
		MES_ExibirCartas( cartasNaMesa ) ;
		/* Falta implementar exibi��o de cartas na mesa */
		
		/* Exibir qual carta � a manilha */
		MES_ExibirMensagem( "A manilha desta mao e: " , 1 ) ;
		MES_ExibirMensagem( manilhaString , 0 ) ;
		
		/* Exibir qual jogador de qual equipe estar� jogando */
		MES_ExibirMensagem( "E a vez do jogador " , 1 ) ;
		MES_ExibirValor( jogadorAtual + 1 ) ;
		MES_ExibirMensagem( " da equipe " , 0 ) ;
		MES_ExibirValor( equipeAtual + 1 ) ;
		MES_ExibirMensagem( " jogar. Suas opcoes sao:" , 0 ) ;
		
		/* Exibir op��es do jogador */
		MES_ExibirCartas( jogador ) ;
		MES_ExibirMensagem( "" , 1 ) ;
		if ( valorMao < 12 )
		{
			MES_ExibirValor( quantidadeCartas + 1) ;
			MES_ExibirMensagem( " - Pedir truco" , 0 ) ;
			/* Perguntar qual comando o jogador deseja executar */
			MES_ReceberComando( &comando , 1 , quantidadeCartas + 1 ) ;
		}
		else
		{
			/* Perguntar qual comando o jogador deseja executar */
			MES_ReceberComando( &comando , 1 , quantidadeCartas ) ;
		}
		
		system( "cls" ) ;
		
		/* Comando recebido. Se for um n�mero at� quantidadeCartas,
		*  � um comando de jogar carta. */
		if ( comando <= quantidadeCartas )
		{
			/* Jogador escolheu jogar uma carta. */
			
			/* Chegar at� a carta escolhida. */
			LIS_AvancarElementoCorrente( jogador , comando - 1 ) ;
			
			/* Criar a nova jogada. */
			novaJogada = ( PAR_tppJogada* ) malloc( sizeof( PAR_tppJogada ) ) ;
			
			/* Armazenar a carta jogada, juntamente � equipe
			*  do jogador que a jogou e qual jogador foi. */
			novaJogada->carta = ( BAR_tppCarta ) LIS_ObterValor( jogador ) ;
			novaJogada->equipe = equipeAtual ;
			novaJogada->jogador = jogadorAtual ;
			
			/* Inserir carta na lista de cartas da mesa */
			LIS_InserirElementoApos( cartasNaMesa , LIS_ObterValor( jogador ) ) ;
			
			/* Inserir a jogada na mesa. */
			LIS_InserirElementoApos( mesa , novaJogada ) ;
			
			/* Remover a carta do jogador. */
			LIS_ExcluirElemento( jogador ) ;
		}
		else
		{
			/* Jogador pediu truco. */
			respostaAumento = PAR_PedirAumento( equipeAtual + 1 , jogadorAtual ) ;
			/* Caso seja recusado, */
			if ( respostaAumento == PAR_CondRetRecusaAumento )
			{
				if ( equipeAtual == 0 )
				{
					MES_ExibirMensagem( "Equipe 2 recusou o truco.\n" , 0 ) ;
					PAR_LimparMesa() ;
					LIS_DestruirLista( cartasNaMesa ) ;
					free( equipes ) ;
					return PAR_CondRetEquipeUmTruco ;
				}
				else
				{
					MES_ExibirMensagem( "Equipe 1 recusou o truco.\n" , 0 ) ;
					PAR_LimparMesa() ;
					LIS_DestruirLista( cartasNaMesa ) ;
					free( equipes ) ;
					return PAR_CondRetEquipeDoisTruco ;
				}
			}
		}
		/* Andar o elemento corrente da equipe para o pr�ximo
		*  jogador, apenas se n�o houve pedido de aumento. */
		if ( respostaAumento == -1 )
		{
			retornoLista = LIS_AvancarElementoCorrente( equipes[equipeAtual] , 1 ) ;
			if (retornoLista == LIS_CondRetFimLista )
			{
				LIS_IrInicioLista( equipes[equipeAtual] ) ;
			}
			
			/* Passar a jogada para a pr�xima equipe. */
			equipeAtual++ ;
			if ( equipeAtual > 1 )
			{
				equipeAtual = 0 ;
				jogadorAtual++ ;
				if ( jogadorAtual >= numeroTotalJogadores / 2 )
				{
					jogadorAtual = 0 ;
				}
			}
		}
		/* Se houve pedido de aumento, vamos apenas
		*  sinalizar que pode ser pedido novamente e
		*  retornar a vez ao jogador. */
		else
		{
			respostaAumento = -1 ;
			quantidadeJogadas-- ;
		}
	}
	
	/* Todos os jogadores jogaram suas cartas. Caso haja um pedido
	*  de truco, este foi aceito, caso contr�rio a m�o j� foi
	*  cancelada. � hora de comparar as cartas para decidir o
	*  vencedor. */
	
	/* A primeira jogada come�ar� sendo a de maior valor. */
	LIS_IrInicioLista( mesa ) ;
	jogadaMaiorCarta = ( PAR_tppJogada* ) LIS_ObterValor( mesa ) ;
	valorMaiorCarta = BAR_ObterValor( jogadaMaiorCarta->carta , NULL ) ;
	retornoLista = LIS_AvancarElementoCorrente( mesa , 1 ) ;
	while ( retornoLista != LIS_CondRetFimLista )
	{
		/* A partir da primeira, vamos comparar os valores. */
		novaJogada = ( PAR_tppJogada* ) LIS_ObterValor( mesa ) ;
		valorCarta = BAR_ObterValor( novaJogada->carta , NULL ) ;
		/* Se a maior carta for a manilha e a carta sendo analisada
		*  tamb�m for a manilha, ent�o deve-se checar o naipe. */
		if ( valorMaiorCarta == manilha && valorCarta == manilha )
		{
			/* Caso o naipe da carta sendo analisada seja maior que
			*  o naipe da maior carta, a primeira ser� a nova maior. */
			if ( BAR_ObterNaipe( novaJogada->carta , NULL ) >
				 BAR_ObterNaipe( jogadaMaiorCarta->carta , NULL ) )
			{
				/* N�o h� necessidade de alterar o valor, pois
				*  ambas s�o a manilha. */
				jogadaMaiorCarta = novaJogada ;
			}
		}
		/* Se a maior carta n�o for a manilha e for igual �
		*  carta sendo analisada, ent�o h� um empate. */
		else if ( valorMaiorCarta != manilha && valorCarta == valorMaiorCarta )
		{
			/* Limpar mesa, ainda falta implementar */
			MES_ExibirMensagem( "A rodada empatou.\n" , 0 ) ;
			PAR_LimparMesa() ;
			LIS_DestruirLista( cartasNaMesa ) ;
			free( equipes ) ;
			return PAR_CondRetEmpate ;
		}
		/* Se a maior carta n�o for a manilha, ent�o podemos
		*  comparar os valores. */
		else if ( valorMaiorCarta != manilha && valorCarta > valorMaiorCarta )
		{
			jogadaMaiorCarta = novaJogada ;
			valorMaiorCarta = valorCarta ;
		}
		/* Passamos para a pr�xima jogada. */
		retornoLista = LIS_AvancarElementoCorrente( mesa , 1 ) ;
	}
	
	/* Ao fim do loop, teremos a jogada de maior valor.
	*  Dela, tiramos o jogadorVencedor e a equipeVencedora. */
	jogadorVencedor = jogadaMaiorCarta->jogador ;
	equipeVencedora = jogadaMaiorCarta->equipe + 1 ;
	
	if ( equipeVencedora == 1 )
	{
		/* Limpar mesa, ainda falta implementar */
		MES_ExibirMensagem( "Equipe 1 venceu a rodada.\n" , 0 ) ;
		PAR_LimparMesa() ;
		LIS_DestruirLista( cartasNaMesa ) ;
		free( equipes ) ;
		return PAR_CondRetEquipeUmVenceu ;
	}
	else
	{
		/* Limpar mesa, ainda falta implementar */
		MES_ExibirMensagem( "Equipe 2 venceu a rodada.\n" , 0 ) ;
		PAR_LimparMesa() ;
		LIS_DestruirLista( cartasNaMesa ) ;
		free( equipes ) ;
		return PAR_CondRetEquipeDoisVenceu ;
	}
}
/***************************************************************************
*
*  Fun��o: BAR  &Criar baralho
*  ****/
PAR_tpCondRet PAR_GerenciarMao( )
{
	int retornoLista ,
		i ,
		vencedorRodada ,
		valorRodada = 1 ,
		vencedorPrimeiraRodada = 0 ,
		manilha ,
		comando ;
		
	char * manilhaString ;
		
	LIS_tppLista equipe ,
				 jogador ,
				 baralho ;
				 
	/* Resetar a pontua��o de m�o das equipes */
	pontuacaoMaoEquipeUm = 0 ;
	pontuacaoMaoEquipeDois = 0 ;
	/* Resetar o valor da m�o para pedidos de
	*  truco. */
	valorMao = 1 ;
	/* Criar o baralho */
	baralho = BAR_CriarBaralho( ) ;
	
	/* Inserir o baralho na lista de listas
	*  lembrando que o baralho � o primeiro da lista */
	LIS_IrInicioLista( estruturaPrincipal ) ;
	LIS_InserirElementoAntes( estruturaPrincipal , baralho ) ;
	
	/* Realizar embaralhamento */
    BAR_EmbaralharCartas( baralho ) ;
	
	/* Avisar a m�o de onze */
	if ( equipeMaoDeOnze != -1 )
	{
		MES_ExibirMensagem( "Uma equipe atingiu 11 pontos." , 0 ) ;
		MES_ExibirMensagem( "A mao de onze sera ativada agora." , 1 ) ;
	}
	
	/* Ok, a lista de listas est� pronta para ser utilizada.
	*  Precisamos agora distribuir as cartas. Avan�amos 1 casa
	*  na lista para chegar � primeira equipe. Como o processo
	*  para as duas equipes � an�logo, basta fazer uma repeti��o. */
	for ( i = 0 ; i < 2 ; i++ )
	{
		LIS_IrInicioLista( estruturaPrincipal ) ;
		LIS_AvancarElementoCorrente( estruturaPrincipal , i + 1 ) ;
		equipe = ( LIS_tppLista ) LIS_ObterValor( estruturaPrincipal ) ;
		
		/* Vamos agora percorrer a lista de jogadores da equipe
		*  e passar 3 cartas para cada um. */
		LIS_IrInicioLista( equipe ) ;
		jogador = ( LIS_tppLista ) LIS_ObterValor( equipe ) ;
		BAR_DistribuirCartas( baralho , jogador ) ;
		retornoLista = LIS_AvancarElementoCorrente( equipe , 1 ) ;
		/* Se o jogador for da equipe da m�o de onze, devemos
		*  mostrar suas cartas. */
		if ( i + 1 == equipeMaoDeOnze )
		{
			MES_ExibirMensagem( "Cartas do jogador:" , 1 ) ;
			MES_ExibirCartas( jogador ) ;
		}
		
		while ( retornoLista != LIS_CondRetFimLista )
		{
			jogador = ( LIS_tppLista ) LIS_ObterValor( equipe ) ;
			BAR_DistribuirCartas( baralho , jogador ) ;
			retornoLista = LIS_AvancarElementoCorrente( equipe , 1 ) ;
			/* Se o jogador for da equipe da m�o de onze, devemos
			*  mostrar suas cartas. */
			if ( i + 1 == equipeMaoDeOnze )
			{
				MES_ExibirMensagem( "Cartas do jogador:" , 1 ) ;
				MES_ExibirCartas( jogador ) ;
			}
		}
	}
	
	if ( equipeMaoDeOnze != -1 )
	{
		MES_ExibirMensagem( "A equipe " , 1 ) ;
		MES_ExibirValor( equipeMaoDeOnze ) ;
		MES_ExibirMensagem( " deseja desistir desta mao?" , 0 ) ;
		MES_ExibirMensagem( "1 - Sim\n2 - Nao" , 1 ) ;
		MES_ReceberComando( &comando , 1 , 2 ) ;
		system( "cls" ) ;
		if ( comando == 1 )
		{
			PAR_LimparMao() ;
			BAR_LiberarBaralho( baralho ) ;
			LIS_IrInicioLista( estruturaPrincipal ) ;
			LIS_ExcluirElemento( estruturaPrincipal ) ;
			if ( equipeMaoDeOnze == 1 )
			{
				MES_ExibirMensagem( "Equipe 2 venceu a mao." , 0 ) ;
				return PAR_CondRetEquipeDoisVenceu ;
			}
			else
			{
				MES_ExibirMensagem( "Equipe 1 venceu a mao." , 0 ) ;
				return PAR_CondRetEquipeUmVenceu ;
			}
		}
	}
	
	/* Distribu�mos todas as cartas necess�rias. � hora de
	*  escolher a manilha. */
	manilhaString = ( char* ) malloc( 7 * sizeof( char ) ) ;
	manilha = BAR_EscolherManilha( baralho , manilhaString ) ;
	
	/* Agora ambas as equipes possuem suas cartas e a
	*  manilha j� foi definida. � hora de come�ar as
	*  rodadas. S�o no m�ximo 3 rodadas, ent�o vamos no
	*  m�ximo at� 3, mas podendo parar antes se uma equipe
	*  atingir 2 pontos. */
	for ( i = 0 ; i < 3 ; i++ )
	{
		/* Gerenciar rodada e definir o vencedor.
		*  O vencedor leva 1 ponto na m�o. */
		vencedorRodada = PAR_GerenciarRodada( manilha , manilhaString ) ;
		if ( vencedorRodada == PAR_CondRetEquipeUmTruco )
		{
			MES_ExibirMensagem( "Equipe 1 venceu a mao." , 0 ) ;
			PAR_LimparMao() ;
			BAR_LiberarBaralho( baralho ) ;
			LIS_IrInicioLista( estruturaPrincipal ) ;
			LIS_ExcluirElemento( estruturaPrincipal ) ;
			free( manilhaString ) ;
			return PAR_CondRetEquipeUmVenceu ;
		}
		else if ( vencedorRodada == PAR_CondRetEquipeDoisTruco )
		{
			MES_ExibirMensagem( "Equipe 2 venceu a mao." , 0 ) ;
			PAR_LimparMao() ;
			BAR_LiberarBaralho( baralho ) ;
			LIS_IrInicioLista( estruturaPrincipal ) ;
			LIS_ExcluirElemento( estruturaPrincipal ) ;
			free( manilhaString ) ;
			return PAR_CondRetEquipeDoisVenceu ;
		}
		else if ( vencedorRodada == PAR_CondRetEquipeUmVenceu )
		{
			pontuacaoMaoEquipeUm += valorRodada ;
			if ( i == 0 )
			{
				vencedorPrimeiraRodada = 1 ;
			}
		}
		else if ( vencedorRodada == PAR_CondRetEquipeDoisVenceu )
		{
			pontuacaoMaoEquipeDois += valorRodada ;
			if ( i == 0 )
			{
				vencedorPrimeiraRodada = 2 ;
			}
		}
		else if ( vencedorRodada == PAR_CondRetEmpate )
		{
			/* Situa��es mais complicadas de se resolver.
			*  Cada caso deve ser avaliado separadamente. */
			
			/* Empate na primeira rodada: Quem ganhar a
			*  segunda rodada vence a m�o. */
			if ( i == 0 )
			{
				valorRodada = 2 ;
			}
			/* Empate na segunda rodada sem empate na
			*  primeira: Quem ganhou a primeira rodada
			*  vence a m�o. */
			else if ( i == 1 && vencedorPrimeiraRodada != 0 )
			{
				if ( pontuacaoMaoEquipeUm > pontuacaoMaoEquipeDois )
				{
					/* Limpar m�o dos jogadores e destruir
					*  baralho */
					MES_ExibirMensagem( "Equipe 1 venceu a mao.\n" , 1 ) ;
					PAR_LimparMao() ;
					BAR_LiberarBaralho( baralho ) ;
					LIS_IrInicioLista( estruturaPrincipal ) ;
					LIS_ExcluirElemento( estruturaPrincipal ) ;
					free( manilhaString ) ;
					return PAR_CondRetEquipeUmVenceu ;
				}
				else
				{
					/* Limpar m�o dos jogadores e destruir
					*  baralho */
					MES_ExibirMensagem( "Equipe 2 venceu a mao.\n" , 1 ) ;
					PAR_LimparMao() ;
					BAR_LiberarBaralho( baralho ) ;
					LIS_IrInicioLista( estruturaPrincipal ) ;
					LIS_ExcluirElemento( estruturaPrincipal ) ;
					free( manilhaString ) ;
					return PAR_CondRetEquipeDoisVenceu ;
				}
			}
			/* Empate na terceira rodada: Quem ganhou a
			*  primeira rodada vence a m�o. Se todas as
			*  rodadas empataram, ningu�m ganha ponto. */
			else if ( i == 2 )
			{
				if ( vencedorPrimeiraRodada == 1 )
				{
					/* Limpar m�o dos jogadores e destruir
					*  baralho */
					MES_ExibirMensagem( "Equipe 1 venceu a mao.\n" , 0 ) ;

					PAR_LimparMao() ;

					BAR_LiberarBaralho( baralho ) ;

					LIS_IrInicioLista( estruturaPrincipal ) ;

					LIS_ExcluirElemento( estruturaPrincipal ) ;

					free( manilhaString ) ;

					return PAR_CondRetEquipeUmVenceu ;

				}/* if */
				else if ( vencedorPrimeiraRodada == 2 )
				{
					/* Limpar m�o dos jogadores e destruir
					*  baralho */
					MES_ExibirMensagem( "Equipe 2 venceu a mao.\n" , 0 ) ;

					PAR_LimparMao() ;

					BAR_LiberarBaralho( baralho ) ;

					LIS_IrInicioLista( estruturaPrincipal ) ;

					LIS_ExcluirElemento( estruturaPrincipal ) ;

					free( manilhaString ) ;

					return PAR_CondRetEquipeDoisVenceu ;
				}/* else if */
				else
				{
					/* Limpar m�o dos jogadores e destruir
					*  baralho */
					MES_ExibirMensagem( "A mao empatou.\n" , 0 ) ;

					PAR_LimparMao() ;

					BAR_LiberarBaralho( baralho ) ;

					LIS_IrInicioLista( estruturaPrincipal ) ;

					LIS_ExcluirElemento( estruturaPrincipal ) ;

					free( manilhaString ) ;

					return PAR_CondRetEmpate ;
				}/* else */
			}
		}
		/* A mesa � limpa no final de cada rodada, antes da
		*  fun��o GerenciaRodada retornar. */
		
		/* Checar se h� um ganhador. Se a diferen�a de
		*  pontos for pelo menos 2, ent�o houve empate
		*  na primeira e algu�m ganhou a segunda ou
		*  uma equipe ganhou as duas primeiras. */
		if ( pontuacaoMaoEquipeUm - pontuacaoMaoEquipeDois >= 2
			 || pontuacaoMaoEquipeDois - pontuacaoMaoEquipeUm >= 2 )
		{
			break ;
		}/* if */
	}

	/* Para os casos de:
	*  1. Uma equipe ganhar as duas primeiras rodadas
	*  2. A primeira rodada empatar e uma equipe ganhar
	*     a segunda rodada.
	*  3. Serem jogadas as 3 rodadas, sem empate nenhum. */
	if ( pontuacaoMaoEquipeUm > pontuacaoMaoEquipeDois )
	{
		/* Limpar m�o dos jogadores e destruir
		*  baralho */
		MES_ExibirMensagem( "Equipe 1 venceu a mao.\n" , 0 ) ;

		PAR_LimparMao() ;

		BAR_LiberarBaralho( baralho ) ;

		LIS_IrInicioLista( estruturaPrincipal ) ;

		LIS_ExcluirElemento( estruturaPrincipal ) ;

		free( manilhaString ) ;

		return PAR_CondRetEquipeUmVenceu ;
	}
	else
	{
		/* Limpar m�o dos jogadores e destruir
		*  baralho */
		MES_ExibirMensagem( "Equipe 1 venceu a mao.\n" , 0 ) ;

		PAR_LimparMao() ;

		BAR_LiberarBaralho( baralho ) ;

		LIS_IrInicioLista( estruturaPrincipal ) ;

		LIS_ExcluirElemento( estruturaPrincipal ) ;

		free( manilhaString ) ;

		return PAR_CondRetEquipeDoisVenceu ;
	}
}
/***************************************************************************
*
*  Fun��o: PAR  &Pedir Aumento
*  ****/
PAR_tpCondRet PAR_PedirAumento( int equipeAtual , int jogadorAtual )
{
	int resposta ;

    /* O jogador X da equipe Y pediu aumento.
	*  A equipe Z precisa responder se aceita
	*  ou n�o. */
	MES_ExibirMensagem( "Valor atual da mao: " , 0 ) ;

	MES_ExibirValor( valorMao ) ;

	MES_ExibirMensagem( "O jogador " , 1 ) ;

	MES_ExibirValor( jogadorAtual + 1 ) ;

	MES_ExibirMensagem( " da equipe " , 0 ) ;

	MES_ExibirValor( equipeAtual ) ;

	MES_ExibirMensagem( " pediu truco.\nA equipe adversaria aceita?" , 0 ) ;

	MES_ExibirMensagem( "1 - Sim\n2 - Nao" , 1 ) ;

	MES_ReceberComando( &resposta , 1 , 2 ) ;

	system( "cls" ) ;

	if ( resposta == 1 )
	{
		if ( valorMao == 1 )
		{
			valorMao = 3 ;
		}/* if */

		else
		{
			valorMao += 3 ;
		}/* else */
		
		return PAR_CondRetAceitaAumento ;
	}/* if */

	else
	{
		return PAR_CondRetRecusaAumento ;
	}/* else */
}

/***************************************************************************
*
*  Fun��o: PAR  &Limpar mesa
*  ****/
void PAR_LimparMesa( )
{	
	PAR_tppJogada *jogada ;
	
	LIS_tppLista mesa ,
				 baralho ;
	
	/* Para limpar a mesa, devemos come�ar pegando
	*  o come�o da lista de jogadas. A mesa � o �ltimo
	*  elemento da lista de listas. */
	LIS_IrFinalLista( estruturaPrincipal ) ;

	mesa = ( LIS_tppLista ) LIS_ObterValor( estruturaPrincipal ) ;

	LIS_IrInicioLista( mesa ) ;
	
	/* Tamb�m precisamos do baralho para jogar as
	*  cartas para l�. */
	LIS_IrInicioLista( estruturaPrincipal ) ;

	baralho = ( LIS_tppLista ) LIS_ObterValor( estruturaPrincipal ) ;
	
	/* Agora temos a mesa. A partir de ent�o, pegamos
	*  cada jogada e descobrimos a carta associada a
	*  esta. A carta pode voltar para o baralho, pois
	*  este n�o ser� mais utilizado e posteriormente
	*  liberar� todas as cartas nele. */
	jogada = ( PAR_tppJogada* ) LIS_ObterValor( mesa ) ;

	while ( jogada != NULL )
	{
		/* Se ainda h� jogadas na mesa, devemos
		*  retir�-la da mesa e passar a carta para o
		*  baralho. Ap�s isso, podemos liberar a
		*  jogada. */
		LIS_ExcluirElemento( mesa ) ;

		LIS_InserirElementoAntes( baralho , jogada->carta ) ;

		free( jogada ) ;

		jogada = ( PAR_tppJogada* ) LIS_ObterValor( mesa ) ;
	}
	
	/* Passamos todas as cartas da mesa para o baralho
	*  e limpamos as jogadas da mesa. Agora � s� retirar
	*  a mesa da lista de listas. */
	LIS_IrFinalLista( estruturaPrincipal ) ;

	LIS_ExcluirElemento( estruturaPrincipal ) ;

	LIS_DestruirLista( mesa ) ;
	
}

/***************************************************************************
*
*  Fun��o: PAR  &Limpar Mao
*  ****/
void PAR_LimparMao( )
{
	int i ,
		j ;
	
	BAR_tppCarta carta ;
	
	LIS_tppLista equipe ,
				 jogador ,
				 baralho ;
				 
	/* Vamos come�ar pegando o baralho. */
	LIS_IrInicioLista( estruturaPrincipal ) ;

	baralho = ( LIS_tppLista ) LIS_ObterValor( estruturaPrincipal ) ;
	
	/* Para limpar a m�o de cada jogador,
	*  devemos come�ar pegando uma equipe
	*  e, dentro desta, retirar todas as
	*  cartas de todos os jogadores, 
	*  passando as cartas para o baralho. */
	for( i = 1 ; i < 3 ; i++ )
	{
		LIS_IrInicioLista( estruturaPrincipal ) ;

		/* Avan�amos o elemento para pegar a
		*  equipe que trataremos no momento. */
		LIS_AvancarElementoCorrente( estruturaPrincipal , i ) ;

		equipe = ( LIS_tppLista ) LIS_ObterValor( estruturaPrincipal ) ;

		LIS_IrInicioLista( equipe ) ;
		
		/* Temos a equipe. Agora vamos tratar
		*  todos os jogadores. Temos X jogadores
		*  no total, ent�o s�o X/2 em cada
		*  equipe. Sendo assim, podemos fazer um
		*  loop pr�-definido. */
		for ( j = 0 ; j < numeroTotalJogadores / 2 ; j++ )
		{
			jogador = ( LIS_tppLista ) LIS_ObterValor( equipe ) ;
			
			/* Temos o nosso jogador. O jogador
			*  � uma lista de cartas. Temos que
			*  pegar cada carta e passar para o
			*  baralho. */

			carta = ( BAR_tppCarta ) LIS_ObterValor( jogador ) ;

			while ( carta != NULL )
			{
				LIS_ExcluirElemento( jogador ) ;

				LIS_InserirElementoAntes( baralho , carta ) ;

				carta = ( BAR_tppCarta ) LIS_ObterValor( jogador ) ;
			}/* while */
			
			/* Limpamos as cartas do jogador.
			*  Agora s� temos que passar para
			*  o pr�ximo. */

			LIS_AvancarElementoCorrente( equipe , 1 ) ;
		}
		
		/* Limpamos as cartas de todos os
		*  jogadores da equipe. Quando o loop
		*  recome�ar, iremos para a pr�xima
		*  equipe e faremos o mesmo. */
	}/* for */
}

/* Fun��o MAIN para executar a chamada da 
 * fun��o PAR_GerenciarPartida*/
int main ( void )
{
	PAR_GerenciarPartida() ;
	return 0 ;
}