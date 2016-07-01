##################################################
###
### Diretivas de MAKE para o construto: TesteBaralho
### Gerado a partir de: TesteBaralho.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteBaralho


### Nomes de paths

Pobj                 = .
Perr                 = .
PDEFAULT             = .
Pc                   = .

### Nomes de diretórios para geração

Fobj                 = .
Ferr                 = .
FDEFAULT             = .
Fc                   = .

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\TestBar.obj   $(Fobj)\Baralho.obj   $(Fobj)\Lista.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\TestBar.obj :  {$(Pc)}\TestBar.c \
    {$(PDEFAULT)}Baralho.h            {$(PDEFAULT)}Generico.h           {$(PDEFAULT)}LISTA.h              \
    {$(PDEFAULT)}LerParm.h            {$(PDEFAULT)}Lista.h              {$(PDEFAULT)}TST_Espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\Baralho.obj :  {$(Pc)}\Baralho.c \
    {$(PDEFAULT)}Baralho.h            {$(PDEFAULT)}LISTA.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\Lista.obj :  {$(Pc)}\Lista.c \
    {$(PDEFAULT)}Generico.h           {$(PDEFAULT)}LISTA.h              {$(PDEFAULT)}TST_Espc.h           \
    {$(PDEFAULT)}cespdin.h            {$(PDEFAULT)}conta.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\TestBar.obj   $(Fobj)\Baralho.obj   $(Fobj)\Lista.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteBaralho
###
##################################################

