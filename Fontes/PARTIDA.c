#include "PARTIDA.h"
#include "BARALHO.h"
#include <stdlib.h>
#include "LISTA.h"
#include "MESA.h"

typedef struct jogada Jogada ;
struct jogada {
	BAR_tppCarta carta ;
	int equipe ,
		jogador ;
} ;

static LIS_tppLista estruturaPrincipal ;

static int numeroTotalJogadores ,
		   pontuacaoPartidaEquipeUm ,
		   pontuacaoPartidaEquipeDois ,
		   pontuacaoMaoEquipeUm ,
		   pontuacaoMaoEquipeDois ,
		   valorMao ,
		   equipeMaoDeOnze = -1 ,
		   equipeVencedora = 1 ,
		   jogadorVencedor = 0 ;
		   /* As vari�veis de vencedores representam os
		   *  vencedores da �ltima rodada realizada. */

void PAR_GerenciarPartida( )
{
   int indiceMao = 0 ,
       numeroAtualJogadores ,
	   vencedorMao ;
   
   LIS_tppLista equipeUm ,
				equipeDois ,
				jogador ;
				
   /* Criar a estrutura principal */
   estruturaPrincipal = LIS_CriarLista ( NULL ) ;
   
   MES_ExibirMensagem( "Qual o numero de jogadores?\n1 - 2\n2 - 4\n3 - 6" , 1 ) ;
   MES_ReceberComando( &numeroTotalJogadores , 1 , 3 ) ;
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
		   }
		   else if ( pontuacaoPartidaEquipeDois == 11 )
		   {
			   equipeMaoDeOnze = 2 ;
		   }
	   }
   }
   /* O �nico jeito de sair do loop � com
   *  alguma equipe atingindo 12 ou mais pontos.
   *  Como apenas uma equipe pode pontuar por vez,
   *  com certeza uma tem mais pontos que a outra. */
   if ( pontuacaoPartidaEquipeUm >
		pontuacaoPartidaEquipeDois )
   {
	   MES_ExibirMensagem( "Equipe 1 venceu." , 1 ) ;
   }
   else
   {
	   MES_ExibirMensagem( "Equipe 2 venceu." , 1 ) ;
   }
}

PAR_tpCondRet PAR_GerenciarRodada( int manilha , char* manilhaString )
{
    int quantidadeJogadas ,
		equipeAtual = equipeVencedora - 1 ,
		retornoLista ,
		jogadorAtual = jogadorVencedor ,
		quantidadeCartas ,
		comando ,
		valorCarta ,
		valorMaiorCarta ;
	
	Jogada *novaJogada ,
		   *jogadaMaiorCarta ;
	
	LIS_tppLista mesa ,
				 *equipes ,
				 jogador ;
				 
	/* Criar a mesa */
	mesa = LIS_CriarLista( NULL ) ;
   
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
		system( "cls" ) ;
		MES_ExibirMensagem( "Placar da partida:" , 0 ) ;
		MES_ExibirPlacar( pontuacaoPartidaEquipeUm ,
						  pontuacaoPartidaEquipeDois ) ;
						  
		/* Exibir placar da m�o */
		MES_ExibirMensagem( "Placar da mao:" , 1 ) ;
		MES_ExibirPlacar( pontuacaoMaoEquipeUm ,
						  pontuacaoMaoEquipeDois ) ;
						  
		/* Exibir cartas na mesa */
		MES_ExibirMensagem( "As cartas atualmente na mesa sao:" , 1 ) ;
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
		MES_ExibirValor( quantidadeCartas + 1) ;
		MES_ExibirMensagem( " - Pedir truco" , 0 ) ;
		
		/* Perguntar qual comando o jogador deseja executar */
		MES_ReceberComando( &comando , 1 , quantidadeCartas + 1 ) ;
		
		/* Comando recebido. Se for um n�mero at� quantidadeCartas,
		*  � um comando de jogar carta. */
		if ( comando <= quantidadeCartas )
		{
			/* Jogador escolheu jogar uma carta. */
			
			/* Chegar at� a carta escolhida. */
			LIS_AvancarElementoCorrente( jogador , comando - 1 ) ;
			
			/* Criar a nova jogada. */
			novaJogada = ( Jogada* ) malloc( sizeof( Jogada ) ) ;
			
			/* Armazenar a carta jogada, juntamente � equipe
			*  do jogador que a jogou e qual jogador foi. */
			novaJogada->carta = ( BAR_tppCarta ) LIS_ObterValor( jogador ) ;
			novaJogada->equipe = equipeAtual ;
			novaJogada->jogador = jogadorAtual ;
			
			/* Inserir a jogada na mesa. */
			LIS_InserirElementoApos( mesa , novaJogada ) ;
			
			/* Remover a carta do jogador. */
			LIS_ExcluirElemento( jogador ) ;
		}
		else
		{
			/* Jogador pediu truco. Ainda deve ser implementado. */
			PAR_PedirAumento( equipeAtual + 1 , jogadorAtual ) ;
		}
		/* Andar o elemento corrente da equipe para o pr�ximo
		*  jogador. */
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
	
	/* Todos os jogadores jogaram suas cartas. Caso haja um pedido
	*  de truco, este foi aceito, caso contr�rio a m�o j� foi
	*  cancelada. � hora de comparar as cartas para decidir o
	*  vencedor. */
	
	/* A primeira jogada come�ar� sendo a de maior valor. */
	LIS_IrInicioLista( mesa ) ;
	jogadaMaiorCarta = ( Jogada* ) LIS_ObterValor( mesa ) ;
	valorMaiorCarta = BAR_ObterValor( jogadaMaiorCarta->carta , NULL ) ;
	retornoLista = LIS_AvancarElementoCorrente( mesa , 1 ) ;
	while ( retornoLista != LIS_CondRetFimLista )
	{
		/* A partir da primeira, vamos comparar os valores. */
		novaJogada = ( Jogada* ) LIS_ObterValor( mesa ) ;
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
			PAR_LimparMesa() ;
			equipes[0] = NULL ;
			equipes[1] = NULL ;
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
		PAR_LimparMesa() ;
		equipes[0] = NULL ;
		equipes[1] = NULL ;
		free( equipes ) ;
		return PAR_CondRetEquipeUmVenceu ;
	}
	else if ( equipeVencedora == 2 )
	{
		/* Limpar mesa, ainda falta implementar */
		PAR_LimparMesa() ;
		equipes[0] = NULL ;
		equipes[1] = NULL ;
		free( equipes ) ;
		return PAR_CondRetEquipeDoisVenceu ;
	}
}

PAR_tpCondRet PAR_GerenciarMao( )
{
	int retornoLista ,
		i ,
		vencedorRodada ,
		valorRodada = 1 ,
		vencedorPrimeiraRodada = 0 ,
		manilha ;
		
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
		
		while ( retornoLista != LIS_CondRetFimLista )
		{
			jogador = ( LIS_tppLista ) LIS_ObterValor( equipe ) ;
			BAR_DistribuirCartas( baralho , jogador ) ;
			retornoLista = LIS_AvancarElementoCorrente( equipe , 1 ) ;
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
		if ( vencedorRodada == PAR_CondRetEquipeUmVenceu )
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
					PAR_LimparMao() ;
					BAR_LiberarBaralho( baralho ) ;
					LIS_IrInicioLista( estruturaPrincipal ) ;
					LIS_ExcluirElemento( estruturaPrincipal ) ;
					free( manilhaString ) ;
					return PAR_CondRetEquipeUmVenceu ;
				}
				else if ( vencedorPrimeiraRodada == 2 )
				{
					/* Limpar m�o dos jogadores e destruir
					*  baralho */
					PAR_LimparMao() ;
					BAR_LiberarBaralho( baralho ) ;
					LIS_IrInicioLista( estruturaPrincipal ) ;
					LIS_ExcluirElemento( estruturaPrincipal ) ;
					free( manilhaString ) ;
					return PAR_CondRetEquipeDoisVenceu ;
				}
				else
				{
					/* Limpar m�o dos jogadores e destruir
					*  baralho */
					PAR_LimparMao() ;
					BAR_LiberarBaralho( baralho ) ;
					LIS_IrInicioLista( estruturaPrincipal ) ;
					LIS_ExcluirElemento( estruturaPrincipal ) ;
					free( manilhaString ) ;
					return PAR_CondRetEmpate ;
				}
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
		}
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
		PAR_LimparMao() ;
		BAR_LiberarBaralho( baralho ) ;
		LIS_IrInicioLista( estruturaPrincipal ) ;
		LIS_ExcluirElemento( estruturaPrincipal ) ;
		free( manilhaString ) ;
		return PAR_CondRetEquipeDoisVenceu ;
	}
}
void PAR_IniciarMaoDeOnze(int indiceEquipe, int numeroTotalJogadores)
{
    //integrantes do Equipe podem vizualizar a carta de seus parceiros
    
    
}

PAR_tpCondRet PAR_PedirAumento( int equipeAtual , int jogadorAtual )
{
    /* O jogador X da equipe Y pediu aumento.
	*  A equipe Z precisa responder se aceita
	*  ou n�o. */
	MES_ExibirMensagem( "" , 1 ) ;
}

void PAR_LimparMesa( )
{	
	Jogada *jogada ;
	
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
	jogada = ( Jogada* ) LIS_ObterValor( mesa ) ;
	while ( jogada != NULL )
	{
		/* Se ainda h� jogadas na mesa, devemos
		*  retir�-la da mesa e passar a carta para o
		*  baralho. Ap�s isso, podemos liberar a
		*  jogada. */
		LIS_ExcluirElemento( mesa ) ;
		LIS_InserirElementoAntes( baralho , jogada->carta ) ;
		free( jogada ) ;
		jogada = ( Jogada* ) LIS_ObterValor( mesa ) ;
	}
	
	/* Passamos todas as cartas da mesa para o baralho
	*  e limpamos as jogadas da mesa. Agora � s� retirar
	*  a mesa da lista de listas. */
	LIS_IrFinalLista( estruturaPrincipal ) ;
	LIS_ExcluirElemento( estruturaPrincipal ) ;
	LIS_DestruirLista( mesa ) ;
	
}

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
			}
			
			/* Limpamos as cartas do jogador.
			*  Agora s� temos que passar para
			*  o pr�ximo. */
			LIS_AvancarElementoCorrente( equipe , 1 ) ;
		}
		
		/* Limpamos as cartas de todos os
		*  jogadores da equipe. Quando o loop
		*  recome�ar, iremos para a pr�xima
		*  equipe e faremos o mesmo. */
	}
}