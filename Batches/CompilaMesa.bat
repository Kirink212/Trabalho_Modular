@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del TesteMesa.exe

del *.obj
nmake /Ftestemesa.make 

copy  *.err  tudo.err

notepad tudo.err

popd
