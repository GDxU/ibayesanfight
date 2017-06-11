#ifndef	_FUNDEC_H
#define	_FUNDEC_H
#include "fight.h"
#include "baye/attribute.h"

GamEng U8		GamRecordMan(U8 flag);

PublicFun U8		PlcMovie(U16 speid, U16 index,U8 startfrm,U8 endfrm,U8 keyflag,U8 x,U8 y);
PublicFun U8		PlcSplMenu(RECT *pRect,U8 pIdx,U8 *buf);
PublicFun U8		PlcExtract(U16 num);
PublicFun U16		PlcArmsMax(PersonID id);
PublicFun U16		PlcArmsMaxP(PersonType* p);
PublicFun void		PlcGraMsgBox(U8 *buf,U8 delay,U8 line);
PublicFun void		PlcMidShowStr(U8 x,U8 y,U8 *buf);
PublicFun void		PlcStrShowS(RECT *big,RECT *small,U8 *buf);
PublicFun void		PlcNumShow(U8 x,U8 y,U32 num,U8 dig,U8 *vs);
PublicFun void		PlcRPicShow(U16 id,U8 idx,U8 x,U8 y,U8 flag);
PublicFun void      PlcRPicShowEx(U16 id, U8 item, U8 idx,U8 x,U8 y,U8 flag);
PublicFun void      GamDrawImage(U16 id, U8 item, U8 idx, U32 x, U32 y);
Debug void		gamPrintNum(U8 x,U8 y, U32 num, U8 base,U8 sign);
Debug void		gamTraceP(U32 num);
Debug void		gamTracel(U32 num);
Debug void		gamPause();

Fight U8		GamFight(void);
Fight void		FgtSetFocus(U8 foc);
Fight void		FgtFrashGen(U8 idx,U8 cnt);

FightSub U8		FgtGenPIdx(U8 i);
FightSub U8		FgtMainMenu(void);
FightSub U8		*FgtGetJNPtr(U8 param);
FightSub U8		FgtGetTerrain(U8 x,U8 y);
FightSub U8		FgtGetGenIdx(U8 x,U8 y);
FightSub U8		FgtDrvCmd(FGTCMD *pcmd);
FightSub void		FgtDealEnd(U8 *genbak);
FightSub void		FgtShowHlp(void);
FightSub void		FgtChgWeather(void);
FightSub U8		FgtCheckIdx(void);

FgtCount void		CountMoveP(U8 i);
FgtCount U16		CountAtkHurt(void);
FgtCount U16		CountPlusSub(U16 *a,U16 v);
FgtCount U16		CountOverAdd(U16 *a,U16 v,U16 up);
FgtCount void		CountSklHurt(U8 param,U16 *arms,U16 *prov, U8 origin, U8*state);
FgtCount void		FgtCountPath(U8 idx);
FgtCount void		BuiltAtkAttr(U8 idx,U8 pIdx);
FgtCount void		CountProvUse(void);
FgtCount void		CountInitGen(void);
FgtCount void		FgtCountWon(void);



FgtPkAi U8		FgtGetJNIdx(U8 idx,RECT *pRect,U8 *buf);
FgtPkAi bool		FgtGetMCmd(FGTCMD *pcmd);
FgtPkAi U8		FgtJNChkAim(U8 param,U8 same,U8 aidx);
FgtPkAi void		FgtGetCmdRng(U8 type,U8 param,U8 idx);
FgtPkAi void		FgtShowMvRng(void);
FgtPkAi void		FgtShowView(void);

U16 sqrt32(U32 a);

#endif	/* _FUNDEC_H */
