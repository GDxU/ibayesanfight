#include 	"inc/dictsys.h"
#include	"mtower.h"

extern U8	g_GameMTNearEnd,g_GameMTDeadLine,g_GameMTEnd,g_GameMTGameOver,g_GameMTInit,g_GameMTQuit;
extern U8	g_GameMTReadKey,g_GameMTTimeOut,g_GameMTTopFloor,g_GameMTHeroLv,g_GameMTCurTime;
extern U16	g_GameMTKBState;
extern U8	g_GameMTMapX,g_GameMTMapY,g_GameMTHeroX,g_GameMTHeroY,g_GameMTJuidgeX,g_GameMTJuidgeY;
extern U8	g_GameMTBuf[1920],g_GameMTKey[3],g_GameMTCheck[7];
extern U16	g_GameMTHeroDamige,g_GameMTHeroDefence,g_GameMTHeroMoney,g_GameMTHeroExp;
extern U8	g_GameMTHeroDir,g_GameMTFloor,*g_GameMTCurMap;
extern U32 g_GameMTHeroLife;
extern U8	*g_GameMTJuidgeNow;

extern	U8	GameMTUnitPic[][32];
extern	U8	GameMTWorkPad[];
extern	U8	GameMTTalkData[][20];
extern	U8	GameMTTalkSide[];
extern	U8	GameMTTalkDown[];
extern	U8	GameMTTalkUp[];
extern	U8	GameMTTalkSigh[][26];
extern	U8	GameMTHeroPic[][32];
extern	U8	GameMTNum39[];
extern	U8	GameMTNum35[];
extern	U8	GameMTNum78[];
extern	U8	GameMTCeng[];
extern	U8	GameMTDi[];
extern	U8	GameMTLiKai[];
extern	U8	GameMTBattlePad[];
extern	U8	GameMTChar[][20];
extern	U8	GameMTNotice[];
extern	U16	GameMTMonData[][5];
extern	U8	GameMTVictory[];
extern	U8	GameMTStartPoint[][4];
extern	U8	GameMTUnknown[];
extern	U8	GameMTMonName[];
extern	U8	GameMTMainFace[];
extern	U8	GameMTHappyEnd[];
extern	U8	GameMTEagle[];

/***********************************************************************
 * 函数名:	GameMTEvent()
 * 说明:		游戏事件处理主函数
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void	GameMTEvent()
{
		U8	temp[20];
		U8	*g_GameMTJuidgeNow;
		GameMTGetInput();
		if(g_GameMTQuit)return;
		switch(g_GameMTReadKey)
		{
			case	1:
					if(g_GameMTHeroX+1>1)
					{
						g_GameMTJuidgeX=g_GameMTHeroX-1;
						g_GameMTJuidgeY=g_GameMTHeroY;
					}
					if(g_GameMTHeroDir==6)g_GameMTHeroDir=7;
						else	g_GameMTHeroDir=6;
					SysPicture((g_GameMTHeroX-g_GameMTMapX)*16,(g_GameMTHeroY-g_GameMTMapY)*16,(g_GameMTHeroX-g_GameMTMapX)*16+15,(g_GameMTHeroY-g_GameMTMapY)*16+15,GameMTHeroPic[g_GameMTHeroDir],0);
					break;
			case	2:
					if(g_GameMTHeroX<10)
					{
						g_GameMTJuidgeX=g_GameMTHeroX+1;
						g_GameMTJuidgeY=g_GameMTHeroY;
					}
					if(g_GameMTHeroDir==4)g_GameMTHeroDir=5;
						else	g_GameMTHeroDir=4;
					SysPicture((g_GameMTHeroX-g_GameMTMapX)*16,(g_GameMTHeroY-g_GameMTMapY)*16,(g_GameMTHeroX-g_GameMTMapX)*16+15,(g_GameMTHeroY-g_GameMTMapY)*16+15,GameMTHeroPic[g_GameMTHeroDir],0);
					break;
			case	3:
					if(g_GameMTHeroY+1>1)
					{
						g_GameMTJuidgeY=g_GameMTHeroY-1;
						g_GameMTJuidgeX=g_GameMTHeroX;
					}
					if(g_GameMTHeroDir+1==1)g_GameMTHeroDir=1;
						else	g_GameMTHeroDir=0;
					SysPicture((g_GameMTHeroX-g_GameMTMapX)*16,(g_GameMTHeroY-g_GameMTMapY)*16,(g_GameMTHeroX-g_GameMTMapX)*16+15,(g_GameMTHeroY-g_GameMTMapY)*16+15,GameMTHeroPic[g_GameMTHeroDir],0);
					break;
			case	4:
					if(g_GameMTHeroY<10)
					{
						g_GameMTJuidgeY=g_GameMTHeroY+1;
						g_GameMTJuidgeX=g_GameMTHeroX;
					}
					if(g_GameMTHeroDir==2)g_GameMTHeroDir=3;
						else	g_GameMTHeroDir=2;
					SysPicture((g_GameMTHeroX-g_GameMTMapX)*16,(g_GameMTHeroY-g_GameMTMapY)*16,(g_GameMTHeroX-g_GameMTMapX)*16+15,(g_GameMTHeroY-g_GameMTMapY)*16+15,GameMTHeroPic[g_GameMTHeroDir],0);
					break;
			case	6:
					if(g_GameMTCurMap[1089]!=18)GameMTChaFloor();
					/*GameMTTalk(5,246,1);
					GameMTBattle(0);
					g_GameMTFloor++;
					if(g_GameMTFloor==22)g_GameMTFloor=0;
					GameMTRefresh();*/
					return;
			case	7:
					SysMemcpy(temp,"确 定 退 出\0",12);
					if(!GuiQueryBox(0,0,temp))g_GameMTQuit=TRUE;
					break;
			case	8:
					if(g_GameMTCurMap[232]+1==1)GameMTCheckMon();
					return;
			case	16:
					if(g_GameMTNearEnd)GameMTReNewR();
					return;
			default:
					return;
		}
		g_GameMTJuidgeNow=&g_GameMTCurMap[(U16)g_GameMTFloor*121+g_GameMTJuidgeY*11+g_GameMTJuidgeX];
		switch(*g_GameMTJuidgeNow)
		{
			case	1:
				if(g_GameMTKey[0]+1>1)
				{
					GameMTOpenDoor();
					g_GameMTKey[0]--;
					*g_GameMTJuidgeNow=0;
					GameMTReNewR();
				}
				else
				{
					SysMemcpy(temp,"  需要1号钥匙\0",14);
					GuiMsgBox(temp,50);
				}
				break;
			case	2:
				if(g_GameMTKey[1]+1>1)
				{
					GameMTOpenDoor();
					g_GameMTKey[1]--;
					*g_GameMTJuidgeNow=0;
					GameMTReNewR();
				}
				else
				{
					SysMemcpy(temp,"  需要2号钥匙\0",14);
					GuiMsgBox(temp,50);
				}
				break;
			case	3:
				if(g_GameMTKey[2]+1>1)
				{
					GameMTOpenDoor();
					g_GameMTKey[2]--;
					*g_GameMTJuidgeNow=0;
					GameMTReNewR();
				}
				else
				{
					SysMemcpy(temp,"  需要3号钥匙\0",14);
					GuiMsgBox(temp,50);
				}
				break;
			case	4:
				g_GameMTFloor++;
				GameMTReNewR();
				if(g_GameMTFloor>g_GameMTTopFloor)g_GameMTTopFloor=g_GameMTFloor;
				g_GameMTHeroX=GameMTStartPoint[g_GameMTFloor][0];
				g_GameMTHeroY=GameMTStartPoint[g_GameMTFloor][1];
				GameMTNewFloor();
				break;
			case	5:
				break;
			case	6:
				if(g_GameMTFloor==3)GameMTShop(5);
				else GameMTShop(6);
				break;
			case	7:
				break;
			case	8:
				GameMTOpenDoor();
				*g_GameMTJuidgeNow=0;
				break;
			case	9:
				if(g_GameMTFloor+1>1)
				{
					g_GameMTFloor--;
					GameMTReNewR();
					g_GameMTHeroX=GameMTStartPoint[g_GameMTFloor][2];
					g_GameMTHeroY=GameMTStartPoint[g_GameMTFloor][3];
					GameMTNewFloor();
				}
				else
				{
					GameMTEnd();
				}
				break;
			case	10:
			case	11:
				break;
			case	12:
				if(g_GameMTFloor==18&&g_GameMTCurMap[2298]+1==1)
				{
					GameMTTalk(2,242,0);
					GameMTTalk(2,244,0);
					GameMTTalk(4,248,0);
					GameMTTalk(2,250,0);
					GameMTTalk(2,252,0);
					GameMTTalk(5,254,1);
					GameMTTalk(3,259,0);
					GameMTTalk(2,262,0);
					GameMTTalk(4,265,0);
					GameMTTalk(3,269,0);
					GameMTTalk(5,272,1);
					GameMTTalk(3,277,0);
					g_GameMTCurMap[2298]=4;
				}
				else if(g_GameMTFloor==18&&g_GameMTCurMap[2298]==4)
				{
					GameMTTalk(2,280,0);
					GameMTTalk(2,282,0);
				}
				else if(g_GameMTFloor==21&&g_GameMTCurMap[2557]==57)
				{
					GameMTTalk(2,302,0);
					GameMTTalk(2,304,0);
				}
				else
				{
					GameMTTalk(2,352,0);
					GameMTTalk(1,354,0);
					g_GameMTCurMap[2555]=0;
				}
				break;
			case	13:
				if(g_GameMTFloor==4&&g_GameMTCurMap[309]==70)
				{
					GameMTTalk(2,149,0);
					GameMTTalk(5,151,1);
					GameMTTalk(5,156,1);
					GameMTTalk(2,161,0);
					GameMTTalk(3,163,0);
					GameMTTalk(3,166,0);
					GameMTTalk(1,169,0);
					GameMTTalk(1,170,0);
					GameMTTalk(2,171,0);
					GameMTTalk(5,173,1);
					GameMTTalk(1,178,0);
					GameMTTalk(3,179,0);
					g_GameMTCurMap[309]=0;
				}
				else if(g_GameMTFloor==4&&g_GameMTCurMap[309]+1==1&&g_GameMTCurMap[1462]==31)
				{
					GameMTTalk(2,182,0);
					GameMTTalk(2,184,0);
					g_GameMTFloor=4;
				}
				else if(g_GameMTFloor==4&&g_GameMTCurMap[309]+1==1&&g_GameMTCurMap[1462]+1==1)
				{
					GameMTTalk(2,186,0);
					GameMTTalk(4,188,0);
					g_GameMTCurMap[2271]=0;
					g_GameMTCurMap[2282]=0;
					g_GameMTCurMap[489]=0;
					g_GameMTFloor=4;
				}
				else if(g_GameMTFloor==21&&g_GameMTCurMap[2557]==57)
				{
					GameMTTalk(3,306,0);
					GameMTTalk(4,309,0);
					GameMTTalk(2,313,0);
				}
				else if(g_GameMTFloor==21&&g_GameMTCurMap[2557]+1==1&&g_GameMTCurMap[2555]==12)
				{
					GameMTTalk(2,356,0);
					GameMTTalk(2,360,0);
				}
				else
				{
					GameMTTalk(2,356,0);
					GameMTTalk(2,358,0);
					g_GameMTCurMap[2622]=0;
					g_GameMTCurMap[2624]=0;
					g_GameMTCurMap[2559]=0;
				}
				break;
			case	14:
				if(g_GameMTFloor==2)
				{
						GameMTTalk(2,132,0);
						GameMTTalk(5,134,0);
						GameMTTalk(2,139,0);
						GameMTTalk(5,141,1);
						GameMTTalk(1,146,0);
						GameMTTalk(2,397,0);
						g_GameMTHeroDefence+=85;
						*g_GameMTJuidgeNow=0;
						GameMTReNewR();
				}
				if(g_GameMTFloor==5)GameMTShop(3);
				if(g_GameMTFloor==12)GameMTShop(4);
				if(g_GameMTFloor==15)
				{
						GameMTTalk(5,206,1);
						GameMTTalk(1,211,0);
						GameMTTalk(2,212,0);
						GameMTTalk(5,214,1);
						GameMTTalk(1,219,0);
						GameMTTalk(1,220,0);
						if(g_GameMTHeroMoney>799)
						{
							g_GameMTHeroMoney-=800;
							GameMTTalk(2,221,0);
							GameMTTalk(1,223,0);
							GameMTTalk(2,425,0);
							g_GameMTHeroDefence+=120;
							*g_GameMTJuidgeNow=0;
							GameMTReNewR();
						}
						else
						{
							GameMTTalk(1,230,0);
							GameMTTalk(3,232,0);
						}
				}
				break;
			case	15:
				if(g_GameMTFloor==2)
					{
						GameMTTalk(2,115,0);
						GameMTTalk(5,117,0);
						GameMTTalk(3,122,0);
						GameMTTalk(5,125,1);
						GameMTTalk(2,130,0);
						GameMTTalk(2,395,0);
						g_GameMTHeroDamige+=70;
						*g_GameMTJuidgeNow=0;
						GameMTReNewR();
					}
				if(g_GameMTFloor==5)GameMTShop(1);
				if(g_GameMTFloor==13)GameMTShop(2);
				if(g_GameMTFloor==15)
				{
						GameMTTalk(5,192,1);
						GameMTTalk(4,197,0);
						if(g_GameMTHeroExp>499)
						{
							g_GameMTHeroExp-=500;
							GameMTTalk(2,201,0);
							GameMTTalk(3,203,0);
							GameMTTalk(2,423,0);
							g_GameMTHeroDamige+=120;
							*g_GameMTJuidgeNow=0;
							GameMTReNewR();
						}
						else
						{
							GameMTTalk(3,224,0);
							GameMTTalk(3,227,0);
						}
				}
				break;
			case	16:
				if(g_GameMTCurMap[93]==16)
				{
					GameMTTalk(1,34,0);
					GameMTTalk(1,35,0);
					GameMTTalk(2,36,0);
					GameMTTalk(3,38,0);
					GameMTTalk(2,41,0);
					GameMTTalk(3,43,0);
					GameMTTalk(2,46,0);
					GameMTTalk(3,48,0);
					GameMTTalk(4,51,0);
					GameMTTalk(5,55,1);
					GameMTTalk(1,60,0);
					GameMTTalk(2,61,0);
					GameMTTalk(3,63,0);
					GameMTTalk(2,66,0);
					GameMTTalk(5,68,1);
					GameMTTalk(5,73,1);
					GameMTTalk(2,78,0);
					GameMTTalk(2,80,0);
					GameMTTalk(5,82,1);
					GameMTTalk(5,87,1);
					GameMTTalk(3,92,0);
					GameMTTalk(2,95,0);
					GameMTTalk(5,97,1);
					GameMTTalk(1,102,0);
					g_GameMTKey[0]=1;
					g_GameMTKey[1]=1;
					g_GameMTKey[2]=1;
					GameMTReNewR();
					g_GameMTCurMap[93]=0;
					g_GameMTCurMap[92]=16;
				}
				else if(g_GameMTCurMap[896]==32)
				{
					GameMTTalk(2,103,0);
					GameMTTalk(2,105,0);
				}
				else
				{
					GameMTTalk(2,103,0);
					GameMTTalk(2,107,0);
					GameMTTalk(5,109,1);
					GameMTTalk(1,114,0);
					g_GameMTHeroDamige+=g_GameMTHeroDamige/3;
					g_GameMTHeroDefence+=g_GameMTHeroDefence/3;
					g_GameMTHeroLife+=g_GameMTHeroLife/3;
					GameMTReNewR();
					g_GameMTCurMap[92]=0;
				}
				break;
			case	17:
				SysMemcpy(temp,"大血瓶：生命+500\0",17);
				GuiMsgBox(temp,50);
				g_GameMTHeroLife+=500;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	18:
				GameMTTalk(5,431,0);
				*g_GameMTJuidgeNow=0;
				break;
			case	19:
				GameMTTalk(2,410,0);
				g_GameMTHeroDefence+=30;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	20:
				GameMTTalk(2,408,0);
				g_GameMTHeroDamige+=50;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	21:
				GameMTTalk(2,429,0);
				g_GameMTHeroDefence+=190;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	22:
				SysMemcpy(temp,"防御宝石：防御+3\0",17);
				GuiMsgBox(temp,50);
				g_GameMTHeroDefence+=3;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	23:
				SysMemcpy(temp,"攻击宝石：攻击+3\0",17);
				GuiMsgBox(temp,50);
				g_GameMTHeroDamige+=3;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	24:
				GameMTTalk(5,436,0);
				*g_GameMTJuidgeNow=0;
				break;
			case	25:
				GameMTTalk(3,419,0);
				g_GameMTHeroLife*=2;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	26:
				GameMTTalk(2,485,0);
				g_GameMTHeroDefence+=10;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	27:
				GameMTTalk(2,483,0);
				g_GameMTHeroDamige+=10;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	28:
				GameMTTalk(2,399,0);
				g_GameMTHeroLv+=1;
				g_GameMTHeroLife+=1000;
				g_GameMTHeroDamige+=7;
				g_GameMTHeroDefence+=7;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	29:
				SysMemcpy(temp,"小血瓶：生命+200\0",17);
				GuiMsgBox(temp,50);
				g_GameMTHeroLife+=200;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	30:
				GameMTTalk(2,427,0);
				g_GameMTHeroDamige+=150;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	31:
				GameMTTalk(5,412,0);
				*g_GameMTJuidgeNow=0;
				break;
			case	32:
				GameMTTalk(5,403,0);
				*g_GameMTJuidgeNow=0;
				break;
			case	33:
				GameMTTalk(2,393,0);
				g_GameMTKey[0]+=1;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	34:
				GameMTTalk(2,445,0);
				g_GameMTKey[1]+=1;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	35:
				GameMTTalk(2,391,0);
				g_GameMTKey[2]+=1;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	36:
				GameMTTalk(2,389,0);
				g_GameMTKey[0]+=1;
				g_GameMTKey[1]+=1;
				g_GameMTKey[2]+=1;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	37:
				GameMTTalk(2,417,0);
				g_GameMTHeroLv+=3;
				g_GameMTHeroLife+=3000;
				g_GameMTHeroDamige+=21;
				g_GameMTHeroDefence+=21;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			case	57:
				if(g_GameMTFloor==19)
				{
					GameMTTalk(2,284,0);
					GameMTTalk(5,286,0);
					GameMTTalk(2,291,0);
					GameMTBattle(*g_GameMTJuidgeNow-38);
					if((*g_GameMTJuidgeNow)+1==1)
					{
						GameMTTalk(5,293,1);
						GameMTTalk(2,298,0);
						GameMTTalk(2,300,0);
					}
				}
				else
				{
					GameMTTalk(2,315,0);
					GameMTTalk(3,317,0);
					GameMTTalk(3,320,0);
					GameMTTalk(2,323,0);
					GameMTTalk(2,325,0);
					GameMTTalk(3,327,0);
					GameMTTalk(2,330,0);
					GameMTTalk(3,332,0);
					GameMTTalk(2,335,0);
					GameMTTalk(2,337,0);
					GameMTBattle(32);
					if((*g_GameMTJuidgeNow)+1==1)
					{
						GameMTTalk(4,339,0);
						GameMTTalk(3,343,0);
						GameMTTalk(5,346,1);
						GameMTTalk(1,351,0);
						g_GameMTCurMap[115]=9;
						GameMTEndFace();
					}
				}
				break;
			case	47:
				if(g_GameMTFloor==16)
				{
					GameMTTalk(2,235,0);
					GameMTTalk(3,237,0);
					GameMTTalk(2,240,0);
					GameMTBattle(*g_GameMTJuidgeNow-38);
				}
				else GameMTBattle(31);
				break;
			case	38:
			case	39:
			case	40:
			case	41:
			case	42:
			case	43:
			case	44:
			case	45:
			case	46:
			case	48:
			case	49:
			case	50:
			case	51:
			case	52:
			case	53:
			case	54:
			case	55:
			case	56:
			case	58:
			case	59:
			case	60:
			case	61:
			case	62:
			case	63:
			case	64:
			case	65:
			case	66:
			case	67:
			case	68:
				GameMTBattle(*g_GameMTJuidgeNow-38);
				break;
			case	69:
				break;
			case	70:
				GameMTTalk(2,147,0);
				break;
			case	71:
				GameMTTalk(2,401,0);
				g_GameMTHeroMoney+=300;
				*g_GameMTJuidgeNow=0;
				GameMTReNewR();
				break;
			default:
					GameMTMove();
		}
		GameMTRefresh();
		/*if(g_GameMTReadKey!=16)GameMTRefresh();*/
}

/***********************************************************************
 * 函数名:	GameMTMainMenu()
 * 说明:		游戏主菜单
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void GameMTMainMenu()
{
	U8 choice,timeout;
	choice=1;
	timeout=0;
	SysPicture(0,0,158,95,GameMTMainFace,0);
	SysRect(15,38,50,56);
	while(1)
	{
		GameMTGetInput();
		if(g_GameMTReadKey==7)g_GameMTQuit=TRUE;
		if(g_GameMTQuit)break;
		if(g_GameMTReadKey==16)
		{
			timeout++;
			if(timeout==1)
			{
				SysPicture(123,14,129,17,GameMTEagle,0);
				SysPicture(133,28,139,31,GameMTEagle,0);
				SysPicture(140,15,146,18,GameMTEagle,0);
			}
			if(timeout==5||timeout==9)
			{
				SysPicture(123,14,129,17,GameMTEagle+8,0);
				SysPicture(133,28,139,31,GameMTEagle+8,0);
				SysPicture(140,15,146,18,GameMTEagle+8,0);
			}
			if(timeout==7)
			{
				SysPicture(123,14,129,17,GameMTEagle+4,0);
				SysPicture(133,28,139,31,GameMTEagle+4,0);
				SysPicture(140,15,146,18,GameMTEagle+4,0);
			}
			if(timeout==11)timeout=0;
		}
		if(g_GameMTReadKey==3)
		{
			choice=1;
			SysRect(15,38,50,56);
			SysRectClear(15,57,50,75);
		}
		if(g_GameMTReadKey==4)
		{
			choice=2;
			SysRect(15,57,50,75);
			SysRectClear(15,38,50,56);
		}
		if(g_GameMTReadKey==6)
		{
			if(choice==1)break;
			if(choice==2)
			{
				GameMTTalk(3,487,0);
				GameMTTalk(2,490,0);
				GameMTTalk(2,492,0);
			}
		}
	}
}

/***********************************************************************
 * 函数名:	GameMTEnd()
 * 说明:		游戏结束函数
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void GameMTEnd()
{
	U8	temp[8];
	g_GameMTInit=TRUE;
	SysLcdPartClear(0,0,158,95);
	if(g_GameMTDeadLine+1>1)
	{
		GameMTTalk(5,366,1);
		GameMTTalk(4,371,1);
		GameMTTalk(5,375,1);
		GameMTTalk(3,380,0);
		SysRect(31,9,128,74);
		SysPicture(32,10,127,73,GameMTHappyEnd,0);
		SysMemcpy(temp,"THE END\0",8);
		SysPrintString(52,78,temp);
		while(1)
		{
			GameMTGetInput();if(g_GameMTQuit)break;
			if(g_GameMTReadKey==7)return;
		}
	}
	else
	{
		GameMTTalk(4,383,0);
		GameMTTalk(2,387,0);
	}
}
