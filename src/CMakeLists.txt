cmake_minimum_required(VERSION 2.4)

project(baye)

set (bayelib_SRCS
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
data-bind.c
bind-objects.c
touch.c
config.c
platform/js/fsys.c
platform/js/sem.c
platform/js/timer.c
platform/js/script.c
platform/js/sys-js.c
platform/common/bios.c
platform/common/gui.c
platform/common/sys.c
)

add_library(bayeliba ${bayelib_SRCS})

add_executable(baye
platform/js/main.c
)

#target_link_libraries(baye bayeliba msgpackc-static)
target_link_libraries(baye bayeliba)

target_include_directories(baye PRIVATE . ./platform/common)
target_include_directories(bayeliba PRIVATE . ./platform/common)
#target_include_directories(bayeliba PRIVATE ${msgpack_SOURCE_DIR}/include)
# -s EMTERPRETIFY_ADVISE=1
set (CMAKE_C_FLAGS
    "-s EMTERPRETIFY=1\
 -s EMTERPRETIFY_ASYNC=1 \
 -s ASSERTIONS=0 \
 -s EMTERPRETIFY_WHITELIST='@whitelist.json' \
 "
)

