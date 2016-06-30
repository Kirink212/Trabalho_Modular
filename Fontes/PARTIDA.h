typedef enum {
	PAR_CondRetEquipeUmVenceu ,
	PAR_CondRetEquipeDoisVenceu ,
	PAR_CondRetEmpate ,
	PAR_CondRetAceitaAumento ,
	PAR_CondRetRecusaAumento ,
} PAR_tpCondRet ;

void PAR_GerenciarPartida();
PAR_tpCondRet PAR_GerenciarRodada( int manilha , char* manilhaString );
PAR_tpCondRet PAR_GerenciarMao();
void PAR_IniciarMaoDeOnze();
PAR_tpCondRet PAR_PedirAumento(int n);
void PAR_LimparMesa();
void PAR_LimparMao();