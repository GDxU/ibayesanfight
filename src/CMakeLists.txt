cmake_minimum_required(VERSION 2.4)

add_executable(baye.js 
FgtCount.c
FgtPkAi.c
Fight.c
FightSub.c
PublicFun.c
Size.c
citycmd.c
citycmdb.c
citycmdc.c
citycmdd.c
citycmde.c
cityedit.c
comIn.c
comOut.c
datman.c
debug.c
gamEng.c
infdeal.c
itoa.c
paccount.c
pconst.c
pstring.c
showface.c
strcnt.c
tactic.c
varma.c
platform/js/fsys.c
platform/js/sem.c
platform/js/timer.c
platform/js/main.c
platform/common/bios.c
platform/common/gui.c
platform/common/sys.c
)

target_include_directories(baye.js PRIVATE . ./platform/common)

set (CMAKE_C_FLAGS
    "-s EMTERPRETIFY=1 -s EMTERPRETIFY_ASYNC=1 -s ASSERTIONS=1"
)

