/***************************************************************************
*  $MCI Módulo de implementação: TMES Teste mesa para interagir com usuário
*
*  Arquivo gerado:              TestMES.c
*  Letras identificadoras:      TMES
*
*  Projeto: INF 1301 / 1628 Módulo mesa para jogo de truco
*  Autores: llages
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data       Observações
*     1		  llages  28/jun/2016   início desenvolvimento
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
#include    "Mesa.h"


static const char EXIBIR_PLACAR_CMD        [ ] = "=exibirplacar"      ;
static const char EXIBIR_CARTAS_CMD        [ ] = "=exibircartas"      ;
static const char EXIBIR_VALOR_CMD         [ ] = "=exibirvalor"       ;
static const char EXIBIR_MENSAGEM_CMD      [ ] = "=exibirmensagem"    ;

#define VAZIO     0
#define NAO_VAZIO 1

LIS_tppLista   Baralho = NULL ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TMES &Testar mesa
*
*  $ED Descrição da função
*
*     Comandos disponíveis:
*
*     =exibirplacar                   num1  num2  CondRetEsp
*     =exibircartas                   CondRetEsp
*     =exibirvalor                    valor  CondRetEsp
*     =exibirmensagem                 CondRetEsp  mensagem
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int numLidos   = -1 ,
          CondRetEsp = -1 ,
		  CondRet    = -1 ;


      int num1 ,
		  num2 ;
	  
	  char mensagemTemp[100] ,
		   *mensagem = NULL ;

      /* Testar Exibir placar */

         if ( strcmp( ComandoTeste , EXIBIR_PLACAR_CMD ) == 0 )
         {
			numLidos = LER_LerParametros( "iii" ,
						&num1, &num2 , &CondRetEsp ) ;
						
			if ( numLidos != 3 )
			{
				return TST_CondRetParm ;
			} /* if */
			
			CondRet = MES_ExibirPlacar( num1 , num2 ) ;
			
            return TST_CompararInt( CondRetEsp , CondRet ,
					 "Condicao de retorno errada ao exibir placar" ) ;

         } /* fim ativa: Testar Exibir placar */

      /* Testar Exibir Cartas */

         else if ( strcmp( ComandoTeste , EXIBIR_CARTAS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
					   &CondRetEsp ) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
			
			if ( CondRetEsp == MES_CondRetOK )
			{
				Baralho = BAR_CriarBaralho(  ) ;
			}
			else if ( CondRetEsp == MES_CondRetListaVazia )
			{
				Baralho = LIS_CriarLista ( NULL ) ;
			}
			
			CondRet = MES_ExibirCartas( Baralho ) ;
			
			if ( Baralho )
			{
				BAR_LiberarBaralho( Baralho ) ;
			}
			
			Baralho = NULL ;

            return TST_CompararInt( CondRetEsp , CondRet ,
					 "Condicao de retorno errada ao exibir cartas" ) ;

         } /* fim ativa: Testar Exibir Cartas */

      /* Testar Exibir Valor */

         else if ( strcmp( ComandoTeste , EXIBIR_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &num1 , &CondRetEsp ) ;

            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = MES_ExibirValor( num1 ) ;
			
			return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao exibir valor." ) ;

         } /* fim ativa: Testar Exibir Valor */
		 
	/* Testar Exibir Mensagem */
		 else if ( strcmp( ComandoTeste , EXIBIR_MENSAGEM_CMD ) == 0 )
		 {
				
			numLidos = LER_LerParametros( "is" ,
								&CondRetEsp , mensagemTemp ) ;
								
			if ( numLidos != 2 )
			{
				return TST_CondRetParm ;
			}
			
			if ( CondRetEsp != MES_CondRetMensagemVazia )
			{
				mensagem = ( char* ) malloc( ( strlen( mensagemTemp ) + 1 ) * sizeof( char ) ) ;
			
				strcpy( mensagem, mensagemTemp ) ;
			}
			
			CondRet = MES_ExibirMensagem( mensagem , 0 ) ;
			
			if ( mensagem )
			{
				free( mensagem ) ;
			}
			
			return TST_CompararInt( CondRetEsp , CondRet ,
					 "Condicao de retorno errada ao exibir mensagem." ) ;
			
		 } /* fim ativa: Testar Exibir Mensagem */
		
      return TST_CondRetNaoConhec ;

   } /* Fim função: TMES &Testar mesa */


/********** Fim do módulo de implementação: TMES Teste mesa para interagir com usuário **********/

