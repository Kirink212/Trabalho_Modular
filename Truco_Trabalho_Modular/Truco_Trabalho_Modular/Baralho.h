#include<stdlib.h>
#include "LISTA.h"

typedef struct carta Carta;

LIS_tppLista BAR_criaBaralho();

void BAR_liberaBaralho(LIS_tppLista baralho);

void BAR_embaralhaCartas(LIS_tppLista baralho);

void BAR_distribuiCartas(LIS_tppLista bar, LIS_tppLista jog);