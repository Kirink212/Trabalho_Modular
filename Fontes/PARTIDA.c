#include "PARTIDA.h"
#include "MESA.h"
#include "BARALHO.h"

PAR_tpCondRet PAR_GerenciarPartida(int numeroTotalJogadores)
{
   int indiceMao = 0;
   LIS_tppLista estruturaPrincipal = LIS_CriarLista( NULL ) ;
   
   LIS_tppLista baralho = BAR_CriarBaralho( ) ;
   
   // Assertiva que verifica se baralho está vazio
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
          printf( "Mão de número %d terminada com sucesso", indiceMao+1 );
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
void PAR_GerenciarRodada()
{
    int jogada ;
    LIS_tppLista BAR_CriarBaralho( ) ;
    BAR_tpCondRet BAR_EmbaralharCartas( LIS_tppLista baralho ) ;
    BAR_tpCondRet BAR_DistribuirCartas( LIS_tppLista baralho , LIS_tppLista jogador ) ;
    int BAR_EscolherManilha( LIS_tppLista baralho ) ;
}
void PAR_IniciarMaoDeOnze(int indiceEquipe, int numeroTotalJogadores)
{
    //integrantes do Equipe podem vizualizar a carta de seus parceiros
    
    
}
void PAR_IniciarMaoDeFerro()
{
//ninguém consegue vizualizar suas próprias cartas
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