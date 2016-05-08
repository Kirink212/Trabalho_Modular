@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del TesteBaralho.exe

del *.obj
nmake /Ftestebaralho.make 

copy  *.err  tudo.err

notepad tudo.err

popd
