#include <stdlib.h>
#include "LISTA.h"

/* Tipo refer�ncia para uma carta */
typedef struct carta Carta;

typedef enum {

         BAR_CondRetOK ,
               /* Concluiu corretamente */

         BAR_CondRetCartaNaoCriada ,
               /* Erro na cria��o da carta */

		 BAR_CondRetCartaNaoInseridaAntes ,
               /* Erro na inser��o de carta antes em uma lista*/

         BAR_CondRetCartaNaoExcluida ,
               /* Erro na exclus�o da carta */

         BAR_CondRetErroAndarListaVazia
               /* Erro ao tentar andar em uma lista vazia */

} BAR_tpCondRet ;

LIS_tppLista BAR_criaBaralho();

BAR_tpCondRet BAR_liberaBaralho(LIS_tppLista baralho);

BAR_tpCondRet BAR_embaralhaCartas(LIS_tppLista baralho);

BAR_tpCondRet BAR_distribuiCartas(LIS_tppLista bar, LIS_tppLista jog);

void* BAR_EscolheManilha(LIS_tppLista bar);

void exibeBaralho(LIS_tppLista baralho);