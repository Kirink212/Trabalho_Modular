#include "PARTIDA.h"

void PAR_GerenciarPartida();
void PAR_ReiniciarPartida();
void PAR_GerenciarRodada();
void PAR_GerenciarMao();
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