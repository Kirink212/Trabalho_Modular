#include "LISTA.h"

typedef enum {
	
	MES_CondRetOK,
	
	MES_CondRetFaltouMemoria,
	
	MES_CondRetListaVazia,
	
	MES_CondRetMensagemVazia,
	
} MES_tpCondRet ;

MES_tpCondRet MES_ExibirPlacar( int valor1 , int valor2 ) ;

MES_tpCondRet MES_ExibirCartas( tppLista cartas ) ;

MES_tpCondRet MES_ExibirValorMao( int valor ) ;

MES_tpCondRet MES_ExibirMensagem( char* mensagem ) ;

MES_tpCondRet MES_ReceberComando( int* comando ) ;