#include "PARTIDA.h"
#include "MESA.h"
#include "BARALHO.h"
void PAR_GerenciarPartida()
{
   while(pontuacaoPartidaGrupo1 != 12 && pontuacaoPartidaGrupo2 != 12)
   {
       if(PAR_GerenciarMao() == 1)
       {
          pontucaoPartidaGrupo1 += pontuacaoMao;
       }
       else if(PAR_GerenciarMao() == 2)
       {
          pontucaoPartidaGrupo2 += pontuacaoMao;
       }
   }
}
void PAR_ReiniciarPartida()
{
    pontuacaoPartidaGrupo1 = pontuacaoPartidaGrupo2 = 0;
    PAR_GerenciarPartida();
}
int PAR_GerenciarMao()
{
    int contabiliza = pontucaoMaoGrupo1 - pontucaoMaoGrupo2 ;
    bool ganhador = false ;
    while(!ganhador)
    {
        if(contabiliza == 0)
        {
            if(pontuacaoMaoGrupo1 == 3)
            {
                ganhador = true ;
                return 0 ;
            }
            else
            {
                PAR_GerenciarRodada() ;
            }
        }
        else if(contabiliza > 0)
        {
            if(pontuacaoMaoGrupo1 == 2)
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
            if(pontuacaoMaoGrupo2 == 2)
            {
                ganhador = true ;
                return 1 ;
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
    BAR_CriarBaralho() ;
    BAR_EmbaralharCartas() ;
    BAR_DistribuirCartas() ;
    BAR_EscolherManilha() ;
}
void PAR_IniciarMaoDeOnze(int grupoIndex)
{
//integrantes do grupo podem vizualizar a carta de seus parceiros
    
}
void PAR_IniciarMaoDeFerro()
{
//ninguém consegue vizualizar suas próprias cartas
}
int PAR_PedirAumento(int n, int *pontuacaoMao)
{
    if(PAR_ResponderAumento(n, pontuacaoMao) == 1)
    {
        *pontuacao_mao = n;
        return 1;
    }
    else if(PAR_ResponderAumento(n, pontuacaoMao) == 2)
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
    return PAR_FalhaAumento; //cond ret #1
}