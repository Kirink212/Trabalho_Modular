/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#ifdef _DEBUG
	#include   "conta.h" 
	#include   "cespdin.h"
#endif

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {
		#ifdef _DEBUG
		 LIS_tppLista cabecaLista ;
			   /* Ponteiro para a cabe�a de lista */
		#endif

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* N�mero de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

   } LIS_tpLista ;
   
/************************************************************************
*
*  $TC Tipo de dados: LIS Id Tipo de Espaco
*
*
*************************************************************************/

#ifdef _DEBUG
	typedef enum {
   
		 CED_ID_TIPO_VALOR_NULO ,
		   /* Tipo de espa�o com valor nulo */
		 
		 LIS_TipoEspacoCabeca ,
		   /* Tipo de espa�o Cabe�a de Lista */
		 
		 LIS_TipoEspacoElemento ,
		   /* Tipo de espa�o Elemento de Lista */
		 
		 CED_ID_TIPO_NULL   = 99998 ,
		   /* Tipo de espa�o nulo */
		 
		 CED_ID_TIPO_ILEGAL = 99999 
		   /* Tipo de espa�o ilegal */
		 
	} LIS_tpIdTipoEspaco ;
#endif

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

      LIS_tpLista * pLista = NULL ;
      
      #ifdef _DEBUG
         CNT_CONTAR( "Criacao da uma lista" );
      #endif
      
      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "Lista nao existe, criar lista" );
         #endif
         
         return NULL ;
      } /* if */
	  
	  #ifdef _DEBUG
		 CED_DefinirTipoEspaco( pLista , LIS_TipoEspacoCabeca ) ;
	  #endif
     
     #ifdef _DEBUG
            CNT_CONTAR( "Lista existe, criar lista" );
     #endif
      
      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor ;

      return pLista ;

   } /* Fim fun��o: LIS  &Criar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {
      #ifdef _DEBUG
            CNT_CONTAR( "Destruir lista, inicio" );
      #endif
      
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
      
      #ifdef _DEBUG
            CNT_CONTAR( "Destruir lista, lista existente" );
      #endif
      
      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
*
*  Fun��o: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;
      
      #ifdef _DEBUG
            CNT_CONTAR( "Esvaziar lista, inicio" );
      #endif
      
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
      
      #ifdef _DEBUG
            CNT_CONTAR( "Esvaziar lista, lista existente" );
      #endif
      
      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "Esvaziar lista, repete" );
         #endif
         
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim fun��o: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        )
   {

      tpElemLista * pElem ;
      
      #ifdef _DEBUG
            CNT_CONTAR( "Inserir elemento antes, inicio" );
      #endif
      
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inserir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Inserir elemento antes, elemento nao existe" );
            #endif
            
            return LIS_CondRetFaltouMemoria ;
         } /* if */
         
         #ifdef _DEBUG
            CNT_CONTAR( "Inserir elemento antes, elemento existe" );
         #endif
      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Inserir elemento antes, elemento corrente nulo" );
            #endif
            
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Inserir elemento antes, elemento corrente nao nulo" );
            #endif
            
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Inserir elemento antes, anterior nao nulo" );
               #endif
               
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Inserir elemento antes, anterior nulo" );
               #endif
               
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento ap�s
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;
      
      #ifdef _DEBUG
            CNT_CONTAR( "Inserir elemento apos, inicio" );
      #endif
      
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir ap�s */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Inserir elemento apos, elemento nao existe" );
            #endif
            
            return LIS_CondRetFaltouMemoria ;
         } /* if */
         
         #ifdef _DEBUG
            CNT_CONTAR( "Inserir elemento apos, elemento existe" );
         #endif
      /* Encadear o elemento ap�s o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Inserir elemento apos, elemento corrente nulo" );
            #endif
            
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Inserir elemento apos, elemento corrente nao nulo" );
            #endif
            
            if ( pLista->pElemCorr->pProx != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Inserir elemento apos, proximo nao nulo" );
               #endif
               
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Inserir elemento apos, proximo nulo" );
               #endif
               
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      
      #ifdef _DEBUG
            CNT_CONTAR( "Excluir elemento, inicio" );
      #endif
      
      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "Excluir elemento, corrente nulo" );
         #endif
         
         return LIS_CondRetListaVazia ;
      } /* if */
      #ifdef _DEBUG
            CNT_CONTAR( "Excluir elemento, corrente nao nulo" );
      #endif
      
      pElem = pLista->pElemCorr ;

      /* Desencadeia � esquerda */

         if ( pElem->pAnt != NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Excluir elemento, desencadear esq anterior nao nulo" );
            #endif
            
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            #ifdef _DEBUG
               CNT_CONTAR( "Excluir elemento, desencadear esq anterior nulo" );
            #endif
            
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia � direita */

         if ( pElem->pProx != NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Excluir elemento, desencadear dir prox nao nulo" );
            #endif
            
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Excluir elemento, desencadear dir prox nulo" );
            #endif
            
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*  ****/

   void * LIS_ObterValor( LIS_tppLista pLista )
   {
      #ifdef _DEBUG
            CNT_CONTAR( "Obter valor, inicio" );
      #endif

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
      
      #ifdef _DEBUG
            CNT_CONTAR( "Obter valor, lista nao nula" );
      #endif
      
      if ( pLista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "Obter valor, elemento corrente nulo" );
         #endif
        
        return NULL ;
      } /* if */
      
      #ifdef _DEBUG
            CNT_CONTAR( "Obter valor, elemento corrente nao nulo" );
      #endif
      
      return pLista->pElemCorr->pValor ;

   } /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento inicial
*  ****/

   void LIS_IrInicioLista( LIS_tppLista pLista )
   {
      #ifdef _DEBUG
            CNT_CONTAR( "Ir inicio lista, inicio" );
      #endif

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
      
      #ifdef _DEBUG
            CNT_CONTAR( "Ir inicio lista, lista nao nula" );
      #endif
      
      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento final
*  ****/

   void LIS_IrFinalLista( LIS_tppLista pLista )
   {
      #ifdef _DEBUG
            CNT_CONTAR( "Ir final lista, inicio" );
      #endif

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
      
      #ifdef _DEBUG
            CNT_CONTAR( "Ir final lista, lista nao nula" );
      #endif
      
      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;
      
      #ifdef _DEBUG
            CNT_CONTAR( "Avancar elemento corrente, inicio" );
      #endif
      
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
      
      #ifdef _DEBUG
            CNT_CONTAR( "Avancar elemento corrente, lista nao nula" );
      #endif
      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Avancar elemento corrente, elemento corrente nulo" );
            #endif
            
            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */
         #ifdef _DEBUG
            CNT_CONTAR( "Avancar elemento corrente, elemento corrente nao nulo" );
         #endif
      /* Tratar avan�ar para frente */

         if ( numElem > 0 )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Avancar elemento corrente, num elemento > 0" );
            #endif
            
            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Avancar elemento corrente, repete" );
               #endif
               
               if ( pElem == NULL )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "Avancar elemento corrente, elemento nulo" );
                  #endif
                  
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Avancar elemento corrente, elemento nao nulo" );
               #endif
               
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */

         else if ( numElem < 0 )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "Avancar elemento corrente, num elemento < 0" );
            #endif
            
            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Avancar elemento corrente, repete2" );
               #endif
               
               if ( pElem == NULL )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR( "Avancar elemento corrente, elemento nulo2" );
                  #endif
                  
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "Avancar elemento corrente, elemento nao nulo2" );
               #endif
               
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar */
         #ifdef _DEBUG
            CNT_CONTAR( "Avancar elemento corrente, nao avanca" );
         #endif
         
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;
      
      #ifdef _DEBUG
            CNT_CONTAR( "Procurar valor, inicio" );
      #endif
      
      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif
      
      #ifdef _DEBUG
            CNT_CONTAR( "Procurar valor, lista nao nula" );
      #endif
      
      if ( pLista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "Procurar valor, elemento corrente nulo" );
         #endif
         
         return LIS_CondRetListaVazia ;
      } /* if */
      
      #ifdef _DEBUG
            CNT_CONTAR( "Procurar valor, elemento corrente nao nulo" );
      #endif
      
      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "Procurar valor, repete" );
         #endif
         
         if ( pElem->pValor == pValor )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */
      
      #ifdef _DEBUG
            CNT_CONTAR( "Procurar valor, nao encontrou valor" );
      #endif
      
      return LIS_CondRetNaoAchou ;

   } /* Fim fun��o: LIS  &Procurar elemento contendo valor */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {
      #ifdef _DEBUG
            CNT_CONTAR( "Liberar elemento, inicio" );
      #endif
      
      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         #ifdef _DEBUG
            CNT_CONTAR( "Liberar elemento, excluir e valor nao nulos" );
         #endif
         
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */
      
      #ifdef _DEBUG
            CNT_CONTAR( "Liberar elemento, excluir ou valor nulo" );
      #endif
      
      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;
      
      #ifdef _DEBUG
            CNT_CONTAR( "Criar elemento, inicio" );
      #endif
      
      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "Criar elemento, elemento nulo" );
         #endif
         
         return NULL ;
      } /* if */
	  
     #ifdef _DEBUG
      CNT_CONTAR( "Criar elemento, elemento nao nulo" );
     #endif
	  
     #ifdef _DEBUG
		CED_DefinirTipoEspaco( pElem , LIS_TipoEspacoElemento ) ;
		pElem->cabecaLista = pLista ;
	  #endif

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim fun��o: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {
      #ifdef _DEBUG
         CNT_CONTAR( "Limpar cabeca" );
      #endif
      
      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim fun��o: LIS  -Limpar a cabe�a da lista */

/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/

