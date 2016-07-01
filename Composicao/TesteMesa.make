##################################################
###
### Diretivas de MAKE para o construto: TesteMesa
### Gerado a partir de: TesteMesa.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteMesa


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
   $(Fobj)\TestMes.obj   $(Fobj)\Baralho.obj   $(Fobj)\Lista.obj \
   $(Fobj)\Mesa.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\TestMes.obj :  {$(Pc)}\TestMes.c \
    {$(PDEFAULT)}Baralho.h            {$(PDEFAULT)}Generico.h           {$(PDEFAULT)}LISTA.h              \
    {$(PDEFAULT)}LerParm.h            {$(PDEFAULT)}Lista.h              {$(PDEFAULT)}Mesa.h               \
    {$(PDEFAULT)}TST_Espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\Baralho.obj :  {$(Pc)}\Baralho.c \
    {$(PDEFAULT)}Baralho.h            {$(PDEFAULT)}LISTA.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\Lista.obj :  {$(Pc)}\Lista.c \
    {$(PDEFAULT)}Generico.h           {$(PDEFAULT)}LISTA.h              {$(PDEFAULT)}TST_Espc.h           \
    {$(PDEFAULT)}cespdin.h            {$(PDEFAULT)}conta.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\Mesa.obj :  {$(Pc)}\Mesa.c \
    {$(PDEFAULT)}BARALHO.h            {$(PDEFAULT)}LISTA.h              {$(PDEFAULT)}MESA.h              
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\TestMes.obj   $(Fobj)\Baralho.obj   $(Fobj)\Lista.obj \
   $(Fobj)\Mesa.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteMesa
###
##################################################

