#include "PARTIDA.h"

void PAR_GerenciarPartida()
{
   while(pontuacaoPartidaGrupo1 != 12 && pontuacaoPartidaGrupo2 != 12)
   {
       if(PAR_GerenciarMao() == 1)
       {
          pontucaoPartidaGrupo1++;
       }
       else if(PAR_GerenciarMao() == 2)
       {
          pontucaoPartidaGrupo2++;
       }
   }
}
void PAR_ReiniciarPartida()
{
    pontuacaoPartidaGrupo1 = pontuacaoPartidaGrupo2 = 0;

}
void PAR_GerenciarRodada();
int PAR_GerenciarMao()
{
    if(pontucaoMaoGrupo1 > pontucaoMaoGrupo2)
    {
        
    }

}
void PAR_IniciarMaoDeOnze();
void PAR_IniciarMaoDeFerro();
int PAR_PedirAumento(int n, int *pontuacao_mao)
{
	if(PAR_ResponderAumento(n, pontuacao_mao))
	{
		*pontuacao_mao = n;
		return 1;
	}
	return 0;
}
int PAR_ResponderAumento(int n, int *pontuacao_mao)
{

}