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

typedef enum {
	PAR_CondRetEquipeUmVenceu ,
	PAR_CondRetEquipeDoisVenceu ,
	PAR_CondRetEmpate ,
} PAR_tpCondRet ;

static LIS_tppLista estruturaPrincipal = LIS_CriarLista ( NULL ) ;

static int numeroTotalJogadores ,
		   pontuacaoPartidaEquipeUm ,
		   pontuacaoPartidaEquipeDois ,
		   pontuacaoMaoEquipeUm ,
		   pontuacaoMaoEquipeDois ,
		   equipeVencedora = 1 ,
		   jogadorVencedor = 0 ;
		   /* As vari�veis de vencedores representam os
		   *  vencedores da �ltima rodada realizada. */

PAR_tpCondRet PAR_GerenciarPartida()
{
   int indiceMao = 0 ,
       numeroAtualJogadores ;
   
   LIS_tppLista equipeUm ,
				equipeDois ,
				jogador ,
				mesa ;
				
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
   *  criada l�, pois ap�s cada rodada ser� limpa. */
   
   // Assertiva que verifica se baralho est� vazio
   #ifdef _DEBUG
        assert( baralho != NULL ) ;
   #endif
   
   if( LIS_InserirElementoApos( estruturaPrincipal, carta) != LIS_CondRetOK )
   {
				return PAR_CondRetErroEstruturaPrincipal ;
   }/* if */
   
   if( MES_ExibirPlacar( pontuacaoPartidaEquipe1 , 
       pontuacaoPartidaEquipe2 ) == MES_CondRetOK )
   {
       if(MES_ExibirMensagem("Partida iniciada com sucesso") == MES_CondRetOK)
       {
          return PAR_CondRetErroDeMensagem;
       }
   }
   
   while(pontuacaoPartidaEquipe1 != 12 && pontuacaoPartidaEquipe2 != 12)
   {
       if(PAR_GerenciarMao(numeroTotalJogadores) == 1)
       {
          pontuacaoPartidaEquipe1 += pontuacaoMao;
       }
       else if(PAR_GerenciarMao(numeroTotalJogadores) == 2)
       {
          pontuacaoPartidaEquipe2 += pontuacaoMao;
       }
       if(MES_ExibirPlacar( pontuacaoPartidaEquipe1 , pontuacaoPartidaEquipe2 ) == MES_CondRetOK)
       {
          printf( "M�o de n�mero %d terminada com sucesso", indiceMao+1 );
          indiceMao++ ;
       }
   }
   
   if( BAR_LiberarBaralho( baralho ) == BAR_CondRetOK )
   {
       return PAR_CondRetOK;
   }
   return PAR_CondRetFaltouMemoria ;
}

void PAR_ReiniciarPartida()
{
    pontuacaoPartidaEquipe1 = pontuacaoPartidaEquipe2 = 0;
    PAR_GerenciarPartida();
}

/* Gerenciar m�o feita logo abaixo de gerenciar rodada */
/* PAR_tpCondResultado PAR_GerenciarMao()
{
    int contabiliza = ( pontuacaoMaoEquipe1 - pontuacaoMaoEquipe2 ) ;
    bool ganhador = false ;
    while ( !ganhador )
    {
        if(contabiliza == 0)
        {
            if(pontuacaoMaoEquipe1 == 3)
            {
                ganhador = true ;
                return 0 ;
            }
            else
            {
                PAR_GerenciarRodada() ;
            }
        }
        else if( contabiliza > 0 )
        {
            if( pontuacaoMaoEquipe1 == 2 )
            {
                ganhador = true ;
                return 1 ;
            }
            else
            {
                PAR_GerenciarRodada() ;
            }
        }
        else
        {
            if( pontuacaoMaoEquipe2 == 2 )
            {
                ganhador = true ;
                return 2 ;
            }
            else
            {
                PAR_GerenciarRodada() ;
            }
        }
    }
} */

PAR_tpCondRet PAR_GerenciarRodada( int manilha )
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
			jogadaMaiorCarta ;
	
	LIS_tppLista mesa ,
				 *equipes ,
				 jogador ;
				 
	/* Criar a mesa */
	LIS_IrFinalLista( estruturaPrincipal ) ;
	mesa = LIS_CriarLista( NULL ) ;
   
	/* Inserir a mesa na lista de listas */
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
	jogador = LIS_ObterValor( equipes[0] ) ;
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
		MES_ExibirMensagem( "Placar da partida:" ) ;
		MES_ExibirPlacar( pontuacaoPartidaEquipeUm ,
						  pontuacaoPartidaEquipeDois ) ;
						  
		/* Exibir placar da m�o */
		MES_ExibirMensagem( "Placar da mao:" ) ;
		MES_ExibirPlacar( pontuacaoMaoEquipeUm ,
						  pontuacaoMaoEquipeDois ) ;
		
		/* Exibir qual jogador de qual equipe estar� jogando */
		MES_ExibirMensagem( "E a vez do jogador " ) ;
		MES_ExibirValor( jogadorAtual + 1 ) ;
		MES_ExibirMensagem( " da equipe " ) ;
		MES_ExibirValor( equipeAtual + 1 ) ;
		MES_ExibirMensagem( " jogar. Suas opcoes sao:" ) ;
		
		/* Exibir op��es do jogador */
		MES_ExibirCartas( jogador ) ;
		MES_ExibirMensagem( "" ) ;
		MES_ExibirValor( quantidadeCartas + 1) ;
		MES_ExibirMensagem( " - Pedir truco" ) ;
		
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
			PAR_PedirAumento() ;
		}
		/* Andar o elemento corrente da equipe para o pr�ximo
		*  jogador. */
		LIS_AvancarElementoCorrente( equipes[equipeAtual] , 1 ) ;
		
		/* Passar a jogada para a pr�xima equipe. */
		equipeAtual++ ;
		if ( equipeAtual > 1 )
		{
			equipeAtual = 0 ;
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
		/* Se a maior carta n�o for a manilha, ent�o podemos
		*  comparar os valores. */
		else if ( valorMaiorCarta != manilha && valorCarta > valorMaiorCarta )
		{
			jogadaMaiorCarta = novaJogada ;
			valorMaiorCarta = valorCarta ;
		}
		/* Se a maior carta n�o for a manilha e for igual �
		*  carta sendo analisada, ent�o h� um empate. */
		else if ( valorMaiorCarta != manilha && valorCarta == valorMaiorCarta )
		{
			/* Limpar mesa, ainda falta implementar */
			free( equipes ) ;
			return PAR_CondRetEmpate ;
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
		free( equipes ) ;
		return PAR_CondRetEquipeUmVenceu ;
	}
	else if ( equipeVencedora == 2 )
	{
		/* Limpar mesa, ainda falta implementar */
		free( equipes ) ;
		return PAR_CondRetEquipeDoisVenceu ;
	}
}

PAR_tpCondRet PAR_GerenciarMao( int equipeInicial , int jogadorInicial )
{
	int equipeAtual ,
		jogadorAtual ,
		retornoLista ,
		i ,
		vencedorRodada ,
		valorRodada = 1 ,
		vencedorPrimeiraRodada = 0 ,
		manilha ;
		
	LIS_tppLista equipe ,
				 jogador ;
				 
	/* Resetar a pontua��o de m�o das equipes */
	pontuacaoMaoEquipeUm = 0 ;
	pontuacaoMaoEquipeDois = 0 ;
	/* Criar o baralho */
	LIS_tppLista baralho = BAR_CriarBaralho( ) ;
	
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
		LIS_AvancarElementoCorrente( estruturaPrincipal , 1 ) ;
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
	manilha = BAR_EscolherManilha( baralho ) ;
	
	/* Agora ambas as equipes possuem suas cartas e a
	*  manilha j� foi definida. � hora de come�ar as
	*  rodadas. S�o no m�ximo 3 rodadas, ent�o vamos no
	*  m�ximo at� 3, mas podendo parar antes se uma equipe
	*  atingir 2 pontos. */
	for ( i = 0 ; i < 3 ; i++ )
	{
		/* Gerenciar rodada e definir o vencedor.
		*  O vencedor leva 1 ponto na m�o. */
		vencedorRodada = PAR_GerenciarRodada( manilha ) ;
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
			else if ( i == 1 && vencedorPrimeiraRodada == 0 )
			{
				if ( pontuacaoMaoEquipeUm > pontuacaoMaoEquipeDois )
				{
					return PAR_CondRetEquipeUmVenceu ;
				}
				else
				{
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
					return PAR_CondRetEquipeUmVenceu ;
				}
				else if ( vencedorPrimeiraRodada == 2 )
				{
					return PAR_CondRetEquipeDoisVenceu ;
				}
				else
				{
					return PAR_CondRetEmpate ;
				}
			}
		}
		/* Rodada realizada. � hora de limpar a mesa. 
		*  A cria��o da nova mesa est� no come�o do loop. */
		BAR_LiberarBaralho( mesa ) ;
		LIS_IrFinalLista( estruturaPrincipal ) ;
		LIS_ExcluirElemento( estruturaPrincipal ) ;
		
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
		return PAR_CondRetEquipeUmVenceu ;
	}
	else
	{
		return PAR_CondRetEquipeDoisVenceu ;
	}
	/* Falta a manipula��o das cartas dos jogadores para
	*  caso uma m�o seja terminada mais cedo que a terceira
	*  rodada. Esvaziar as cartas de cada jogador. */
}
void PAR_IniciarMaoDeOnze(int indiceEquipe, int numeroTotalJogadores)
{
    //integrantes do Equipe podem vizualizar a carta de seus parceiros
    
    
}
void PAR_IniciarMaoDeFerro()
{
//ningu�m consegue vizualizar suas pr�prias cartas
}
int PAR_PedirAumento(int n, int *pontuacaoMao)
{
    if( PAR_ResponderAumento( n, pontuacaoMao ) == 1 )
    {
        *pontuacao_mao = n;
        return 1;
    }
    else if( PAR_ResponderAumento( n, pontuacaoMao ) == 2)
    {
        
    }
    return 0;
}
int PAR_ResponderAumento(int n, int *pontuacao_mao)
{
    int resposta;
    if(MES_ReceberComando(&resposta) == MES_CondRetOK)
    {
        return resposta;
    }
    return PAR_CondRetFalhaAumento;
}