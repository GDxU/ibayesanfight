@echo off
@del	err.txt	>null
 
@c6502 -C -d   -aa_dwnhead downhpsn.c >err.txt
@if	errorlevel == 1 goto	errend            

@del	test.tsk > null
link 	downpsn.cfg >err.txt

@if	not exist test.tsk	goto	errend
dir 	test.tsk

ReCbin test.tsk dwnpsn.cfg
rem filecomb dwnapp.bin /f dwncob.cfg
filecomb 魔塔.gam /r 00 test.bin 30000 43fff

@echo .
@echo .
@echo .		生成《魔塔》程序文件——魔塔.gam
@echo ==============================   OK !!! ==================================

@goto	normalend

:errend
type err.txt

:normalend

