//
//  mtower.h
//  baye-ios
//
//  Created by loong on 2018/8/10.
//
//

#ifndef mtower_h
#define mtower_h
#include <inc/dictsys.h>

FAR void GameMTTalk(U8 line,U16 number,U8	flag);
FAR void GameMTGetInput();
FAR void GameMTPrintNum(U8 flag,U32 number,U8 x,U8 y);
FAR void GameMTGetTalk(U16 number,U8	*chars);

FAR void GameMTNewFloor();
FAR void GameMTReNewR();
FAR void GameMTRefresh();
FAR void GameMTListMon(U8 scoll);
FAR U32	GameMTCountLose(U8 monster);

FAR void GameMTEnd();

FAR void GameMTChaFloor();
FAR void GameMTCheckMon();
FAR void GameMTOpenDoor();
FAR	void GameMTShop(U8 kind);
FAR U8	GameMTBattle(U8	number);
FAR void GameMTEndFace();
FAR void	GameMTMove();
void	GameMTInit();
FAR void	GameMTEvent();
FAR void GameMTMainMenu();
FAR void GameMTGetMapData();

#define SysPicture(a,b,c,d,e,f) SysPicture(a,b,c,d,e,f, 1)

#endif /* mtower_h */
