typedef enum {
	PAR_CondRetEquipeUmVenceu ,
	PAR_CondRetEquipeDoisVenceu ,
	PAR_CondRetEmpate ,
	PAR_CondRetAceitaAumento ,
	PAR_CondRetRecusaAumento ,
	PAR_CondRetEquipeUmTruco ,
	/* Equipe 1 ganhou porque equipe 2 recusou truco*/
	PAR_CondRetEquipeDoisTruco ,
	/* Equipe 2 ganhou porque equipe 1 recusou truco*/
} PAR_tpCondRet ;

void PAR_GerenciarPartida();

PAR_tpCondRet PAR_GerenciarRodada( int manilha , char* manilhaString );

PAR_tpCondRet PAR_GerenciarMao();

PAR_tpCondRet PAR_PedirAumento(int equipeAtual , int jogadorAtual );

void PAR_LimparMesa();

void PAR_LimparMao();