#include <stdlib.h>
#include "LISTA.h"

/* Tipo refer�ncia para uma carta */
typedef struct carta Carta;

typedef enum {

         BAR_CondRetOK ,
               /* Concluiu corretamente */

         BAR_CondRetCartaNaoCriada ,
               /* Erro na cria��o da carta */

		 BAR_CondRetFaltouMemoria ,
               /* Erro na inser��o de carta, falta de mem�ria*/

         BAR_CondRetCartaNaoExcluida ,
               /* Erro na exclus�o da carta */

         BAR_CondRetErroAndarListaVazia
               /* Erro ao tentar andar em uma lista vazia */

} BAR_tpCondRet ;

LIS_tppLista BAR_CriarBaralho();

BAR_tpCondRet BAR_LiberarBaralho(LIS_tppLista baralho);

BAR_tpCondRet BAR_EmbaralharCartas(LIS_tppLista baralho);

BAR_tpCondRet BAR_DistribuirCartas(LIS_tppLista bar, LIS_tppLista jog);

int BAR_EscolherManilha(LIS_tppLista bar);

int BAR_ObterValor(Carta* card);

int BAR_ObterNaipe(Carta* card);