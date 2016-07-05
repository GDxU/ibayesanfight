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
    "-s EMTERPRETIFY=1\
 -s EMTERPRETIFY_ASYNC=1 \
 -s ASSERTIONS=0 \
 -s EMTERPRETIFY_WHITELIST='[\"_AccractbusinessMake\", \"_AlienateMake\", \"_ArmamentOrderMenu\", \"_AssartMake\", \"_BanishMake\", \"_BattleDrv\", \"_BattleMake\", \"_BeNewKingNote\", \"_CanvassDrv\", \"_CanvassMake\", \"_CitiesUpDataDate\", \"_CityCommon\", \"_ConditionUpdate\", \"_ConfiscateMake\", \"_ConscriptionMake\", \"_CounterespiongeDrv\", \"_CounterespiongeMake\", \"_DepredateDrv\", \"_DepredateMake\", \"_DiplomatismOrderMenu\", \"_DistributeMake\", \"_ExchangeMake\", \"_FatherMake\", \"_FgtAtkAction\", \"_FgtAtvShowNum\", \"_FgtChgWeather\", \"_FgtChkAtkEnd\", \"_FgtCmdAimGet\", \"_FgtDealBout\", \"_FgtDealCmp\", \"_FgtDealMan\", \"_FgtDrvCmd\", \"_FgtDrvState\", \"_FgtDrvWeiG\", \"_FgtExeCmd\", \"_FgtFrashGen\", \"_FgtGenMove\", \"_FgtGetControl\", \"_FgtGetFoucs\", \"_FgtGetJNIdx\", \"_FgtGetMCmd\", \"_FgtGetMCmdNear\", \"_FgtGetPCmd\", \"_FgtInit\", \"_FgtIntScr\", \"_FgtJNAction\", \"_FgtMainMenu\", \"_FgtShowChgSpe\", \"_FgtShowGetExp\", \"_FgtShowHlp\", \"_FgtShowSNum\", \"_FgtShowView\", \"_FightResultDeal\", \"_FunctionMenu\", \"_GamBaYeEng\", \"_GamDelay\", \"_GamFight\", \"_GamGetKing\", \"_GamGetMsg\", \"_GamLoadRcd\", \"_GamMainChose\", \"_GamMakerInf\", \"_GamMovie\", \"_GamMsgBox\", \"_GamPicMenu\", \"_GamRecordMan\", \"_GamSaveRcd\", \"_GamShowErrInf\", \"_GameDevDrv\", \"_GetArmy\", \"_GetCitySet\", \"_GetFood\", \"_GetMoney\", \"_GuiGetMsg\", \"_InduceDrv\", \"_InduceMake\", \"_InspectionMake\", \"_InteriorOrderMenu\", \"_KillMake\", \"_KingDeadNote\", \"_KingOverDeal\", \"_LargessMake\", \"_MainOrderMenu\", \"_MoveMake\", \"_NewKingNote\", \"_NumOperate\", \"_OrderExec\", \"_OrderMenu\", \"_PlayerTactic\", \"_PlcGraMsgBox\", \"_PlcMovie\", \"_PlcSplMenu\", \"_PolicyExec\", \"_RandEvents\", \"_ReconnoitreMake\", \"_ReportCalamity\", \"_SearchDrv\", \"_SearchMake\", \"_ShowAttackNote\", \"_ShowCityPro\", \"_ShowConstStrMsg\", \"_ShowDMsg\", \"_ShowFightLossNote\", \"_ShowFightNote\", \"_ShowFightWinNote\", \"_ShowGReport\", \"_ShowGoodsControl\", \"_ShowPersonControl\", \"_ShowTacticNote\", \"_SurrenderDrv\", \"_SurrenderMake\", \"_TheLoserDeal\", \"_TransportationDrv\", \"_TransportationMake\", \"_TreatMake\", \"_WeightOverNote\", \"_WonPersonNoet\", \"_gam_sem_wait\", \"_main\", \"_msg_queue_get\"]' \
 "
)

