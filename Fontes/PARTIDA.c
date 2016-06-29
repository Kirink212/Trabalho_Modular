#include "PARTIDA.h"
#include "BARALHO.h"
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

static int equipeVencedora = 1 ,
		   jogadorVencedor = 1 ;

PAR_tpCondRet PAR_GerenciarPartida(int numeroTotalJogadores)
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

PAR_tpCondResultado PAR_GerenciarMao()
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
}
void PAR_GerenciarRodada( int manilha )
{
    int jogadorDaVez ,
		equipeDaVez ;
    LIS_tppLista BAR_CriarBaralho( ) ;
    BAR_tpCondRet BAR_EmbaralharCartas( LIS_tppLista baralho ) ;
    BAR_tpCondRet BAR_DistribuirCartas( LIS_tppLista baralho , LIS_tppLista jogador ) ;
    int BAR_EscolherManilha( LIS_tppLista baralho ) ;
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
		pontuacaoEquipeUm ,
		pontuacaoEquipeDois ,
		manilha ;
		
	LIS_tppLista equipe ,
				 jogador ;
				 
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
		/* Criar a mesa */
		LIS_IrFinalLista( estruturaPrincipal ) ;
		mesa = LIS_CriarLista( NULL ) ;
	   
		/* Inserir a mesa na lista de listas */
		LIS_InserirElementoApos( estruturaPrincipal , mesa ) ;
		
		/* Gerenciar rodada e definir o vencedor.
		*  O vencedor leva 1 ponto na m�o. */
		vencedorRodada = PAR_GerenciarRodada( manilha ) ;
		if ( vencedorRodada == PAR_CondRetEquipeUmVenceu )
		{
			pontuacaoEquipeUm += valorRodada ;
			if ( i == 0 )
			{
				vencedorPrimeiraRodada = 1 ;
			}
		}
		else if ( vencedorRodada == PAR_CondRetEquipeDoisVenceu )
		{
			pontuacaoEquipeDois += valorRodada ;
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
				if ( pontuacaoEquipeUm > pontuacaoEquipeDois )
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
		if ( pontuacaoEquipeUm - pontuacaoEquipeDois >= 2
			 || pontuacaoEquipeDois - pontuacaoEquipeUm >= 2 )
		{
			break ;
		}
	}
	/* Para os casos de:
	*  1. Uma equipe ganhar as duas primeiras rodadas
	*  2. A primeira rodada empatar e uma equipe ganhar
	*     a segunda rodada.
	*  3. Serem jogadas as 3 rodadas, sem empate nenhum. */
	if ( pontuacaoEquipeUm > pontuacaoEquipeDois )
	{
		return PAR_CondRetEquipeUmVenceu ;
	}
	else
	{
		return PAR_CondRetEquipeDoisVenceu ;
	}
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