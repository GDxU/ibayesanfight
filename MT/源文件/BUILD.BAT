@echo off
@del	err.txt	>null

@c6502 -C -d  main.c >err.txt
@if	errorlevel == 1 goto	errend

@c6502 -C -d  -aa_mtower magictower.c >err.txt
@if	errorlevel == 1 goto	errend

@c6502 -C -d  -aa_mtdata mtowerdata.c >err.txt
@if	errorlevel == 1 goto	errend

@c6502 -C -d  -aa_mtfar mtowerfar.c >err.txt
@if	errorlevel == 1 goto	errend

@c6502 -C -d  -aa_mtfar2 mtowerfar2.c >err.txt
@if	errorlevel == 1 goto	errend

@c6502 -C -d  -aa_mtfar3 mtowerfar3.c >err.txt
@if	errorlevel == 1 goto	errend

rem @c6502 -C -d  edittest.c >err.txt
rem @if	errorlevel == 1 goto	errend
rem 
rem @c6502 -C -d  guitest.c >err.txt
rem @if	errorlevel == 1 goto	errend
rem 
rem @c6502 -C -d  -aa_size size.c >err.txt
rem @if	errorlevel == 1 goto	errend
rem 
rem @x6502 -q -d demo.asm >err.txt
rem @if errorlevel == 1 goto ERREND

@del	test.tsk > null
@link 	main.cfg >err.txt
@if		not exist test.tsk	goto	errend
dir 	test.tsk

rem @s32 test.tsk test.s /f80000 1000 ffff /f90000 10000  40000  /ffff00 4ff00 >null
recbin test.tsk bin.cfg

@echo .
@echo .
@echo .		¡°Ä§Ëþ¡±  --------  ±àÒë³ÌÐòÖ´ÐÐ
@echo ==============================   OK !!! ==================================

@goto	normalend

:errend
type err.txt

:normalend

