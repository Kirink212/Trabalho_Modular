/***************************************************************************
*  $MCI Módulo de implementação: TBAR Teste baralho de cartas para truco
*
*  Arquivo gerado:              TestBAR.c
*  Letras identificadoras:      TBAR
*
*  Projeto: INF 1301 / 1628 Módulo baralho para jogo de truco
*  Autores: llages
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data       Observações
*     1		  llages  03/mai/2016   início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Baralho.h"
#include    "Lista.h"


static const char RESET_BARALHO_CMD        [ ] = "=resetteste"        ;
static const char CRIAR_BARALHO_CMD        [ ] = "=criarbaralho"      ;
static const char LIBERAR_BARALHO_CMD      [ ] = "=liberarbaralho"    ;
static const char EMBARALHAR_CARTAS_CMD    [ ] = "=embaralharcartas"  ;
static const char DISTRIBUIR_CARTAS_CMD    [ ] = "=distribuircartas"  ;
static const char ESCOLHER_MANILHA_CMD     [ ] = "=escolhermanilha"   ;
static const char OBTER_VALOR_CMD          [ ] = "=obtervalor"        ;
static const char OBTER_NAIPE_CMD          [ ] = "=obternaipe"        ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_BARALHO   5
#define DIM_VALOR        100

LIS_tppLista   vtBaralhos[ DIM_VT_BARALHO ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxBaralho( int inxBaralho , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TBAR &Testar baralho
*
*  $ED Descrição da função
*     Podem ser criados até 5 baralhos, identificados pelos índices 0 a 4
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de baralhos. Provoca vazamento de memória
*     =criarbaralho                   inxBaralho
*     =liberarbaralho                 inxBaralho  CondRetEsp
*     =embaralharcartas               inxBaralho  CondRetEsp
*     =distribuircartas               inxBaralho  CondRetEsp
*     =escolhermanilha                inxBaralho
*     =obtervalor                     carta       CondRetEsp
*     =obternaipe                     carta       CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxBaralho  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char   StringDado[  DIM_VALOR ] ;

      int i ;
	  
	  LIS_tppLista jogador ;
	  Carta* carta ;
	  int valor ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de baralho */

         if ( strcmp( ComandoTeste , RESET_BARALHO_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_BARALHO ; i++ )
            {
               vtBaralhos[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de baralhos */

      /* Testar CriarBaralho */

         else if ( strcmp( ComandoTeste , CRIAR_BARALHO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
					   &inxBaralho) ;

            if (( numLidos != 1 )
				|| ( ! ValidarInxBaralho( inxBaralho , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtBaralhos[ inxBaralho ] =
                 BAR_CriarBaralho(  ) ;

            return TST_CompararPonteiroNulo( 1 , vtBaralhos[ inxBaralho ] ,
               "Erro em ponteiro de novo baralho."  ) ;

         } /* fim ativa: Testar CriarBaralho */

      /* Testar LiberarBaralho */

         else if ( strcmp( ComandoTeste , LIBERAR_BARALHO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxBaralho , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxBaralho( inxBaralho , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = BAR_LiberarBaralho( vtBaralhos[ inxBaralho ] ) ;
			
			return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao liberar baralho." ) ;

         } /* fim ativa: Testar LiberarBaralho */
		 
	/* Testar EmbaralharCartas */
		else if ( strcmp( ComandoTeste , EMBARALHAR_CARTAS_CMD ) == 0 )
		{
				
			numLidos = LER_LerParametros( "ii" ,
								&inxBaralho , &CondRetEsp ) ;
								
			if ( ( numLidos != 2 )
			  || ( ! ValidarInxBaralho( inxBaralho, NAO_VAZIO )))
			{
				return TST_CondRetParm ;
			}
			
			CondRet = BAR_EmbaralharCartas( vtBaralhos[ inxBaralho ] ) ;
			
			return TST_CompararInt( CondRetEsp , CondRet ,
					 "Condicao de retorno errada ao embaralhar cartas." ) ;
			
		} /* fim ativa: Testar EmbaralharCartas */
		
	/* Testar DistribuirCartas */
		else if ( strcmp( ComandoTeste , DISTRIBUIR_CARTAS_CMD ) == 0 )
		{
				
			numLidos = LER_LerParametros( "ii" ,
							  &inxBaralho , &CondRetEsp ) ;
							  
			if ( ( numLidos != 2 )
			  || ( ! ValidarInxBaralho( inxBaralho , NAO_VAZIO )))
			{
				return TST_CondRetParm ;
			} /* if */
			
			jogador = LIS_CriarLista( NULL ) ;
			
			BAR_DistribuirCartas( vtBaralhos[ inxBaralho ] , jogador ) ;
			
			CondRet = BAR_DistribuirCartas( jogador , vtBaralhos[ inxBaralho ] ) ;
			
			return TST_CompararInt( CondRetEsp , CondRet ,
					  "Condicao de retorno errada ao distribuir cartas." ) ;
					  
		} /* fim ativa: Testar DistribuirCartas */
		
	/* Testar EscolherManilha */
		else if ( strcmp( ComandoTeste , ESCOLHER_MANILHA_CMD ) == 0 )
		{
				
			numLidos = LER_LerParametros( "i" ,
							  &inxBaralho ) ;
							  
			if ( ( numLidos != 1 )
			  || ( ! ValidarInxBaralho( inxBaralho , NAO_VAZIO )))
			{
				return TST_CondRetParm ;
			} /* if */
			
			CondRet = BAR_EscolherManilha( vtBaralhos[ inxBaralho ] ) ;
			
			return TST_CompararInt( CondRetEsp , CondRet ,
					  "Condicao de retorno errada ao escolher manilha." ) ;
		} /* fim ativa: Testar EscolherManilha */
		
	/* Testar ObterValor */
		else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
		{
			 
			numLidos = LER_LerParametros( "pi" ,
							  &carta , &CondRetEsp ) ;
							  
			if ( numLidos != 2 )
			{
				return TST_CondRetParm ;
			} /* if */
			
			valor = BAR_ObterValor( carta ) ;
			
			return TST_CompararInt( CondRetEsp , valor ,
					  "Condicao de retorno errada ao obter valor." ) ;
		} /* fim ativa: Testar ObterValor */
		
	/* Testar ObterNaipe */
		else if ( strcmp( ComandoTeste , OBTER_NAIPE_CMD ) == 0 )
		{
			 
			numLidos = LER_LerParametros( "pi" ,
							  &carta , &CondRetEsp ) ;
							  
			if ( numLidos != 2 )
			{
				return TST_CondRetParm ;
			} /* if */
			
			valor = BAR_ObterNaipe( carta ) ;
			
			return TST_CompararInt( CondRetEsp , valor ,
					  "Condicao de retorno errada ao obter naipe." ) ;
		} /* fim ativa: Testar ObterNaipe */
		
      return TST_CondRetNaoConhec ;

   } /* Fim função: TBAR &Testar baralho */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TBAR -Validar indice de baralho
*
***********************************************************************/

   int ValidarInxBaralho( int inxBaralho , int Modo )
   {

      if ( ( inxBaralho <  0 )
        || ( inxBaralho >= DIM_VT_BARALHO ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtBaralhos[ inxBaralho ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtBaralhos[ inxBaralho ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TBAR -Validar indice de baralho */

/********** Fim do módulo de implementação: TBAR Teste baralho de cartas para truco **********/

