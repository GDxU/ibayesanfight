#include 	"inc\dictsys.h"
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
 * 函数名:	GameMTChaFloor()
 * 说明:		通过风之罗盘直接换层
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void GameMTChaFloor()
{
	U8	i,tempF,temp;
	tempF=0;
	temp=0;
	if(g_GameMTTopFloor==21)
	{
		GameMTTalk(2,494,0);
		return;
	}
	SysSaveScreen(7,1,121,94,g_GameMTBuf);
	SysLcdPartClear(7,1,121,94);
	SysRect(7,1,121,94);
	SysRect(8,2,120,93);
	SysPicture(89,82,112,90,GameMTLiKai,0);
	for(i=0;i<g_GameMTTopFloor+1;i++)
	{
		SysPicture(11+(i/8)*38,5+(i%8)*11,17+(i/8)*38,13+(i%8)*11,GameMTDi,0);
		GameMTPrintNum(2,(U32)i,24+(i/8)*38,6+(i%8)*11);
		SysPicture(34+(i/8)*38,5+(i%8)*11,41+(i/8)*38,13+(i%8)*11,GameMTCeng,0);
	}
	SysRect(10,4,42,14);
	while(1)
	{
		GameMTGetInput();if(g_GameMTQuit)break;
		if(g_GameMTReadKey==16)continue;
		if(g_GameMTReadKey==7)break;
		if(g_GameMTReadKey==6)break;
		if(g_GameMTReadKey==1)
		{
			if(tempF>7&&tempF!=23)tempF-=8;
			if(tempF==23)
			{
				if(tempF>14)tempF=15;
				else if(tempF>6)tempF=7;
				else tempF=g_GameMTTopFloor;
			}
		}
		if(g_GameMTReadKey==2)
		{
			if(tempF+7<g_GameMTTopFloor)tempF+=8;
			else if(tempF==7&&g_GameMTTopFloor<15)tempF=23;
			else if(tempF==15)tempF=23;	
		}
		if(g_GameMTReadKey==4)
		{
			if(tempF==g_GameMTTopFloor)tempF=23;
			if(tempF<g_GameMTTopFloor)tempF++;
		}
		if(g_GameMTReadKey==3)
		{
			if(tempF+1>1&&tempF!=23)tempF--;
			if(tempF==23)tempF=g_GameMTTopFloor;
		}
		SysRectClear(10+(temp/8)*38,4+(temp%8)*11,42+(temp/8)*38,14+(temp%8)*11);
		temp=tempF;
		SysRect(10+(tempF/8)*38,4+(tempF%8)*11,42+(tempF/8)*38,14+(tempF%8)*11);
	}
	if(g_GameMTReadKey==6)
		if(g_GameMTTopFloor>=tempF)
				{
					g_GameMTFloor=tempF;
					g_GameMTHeroX=GameMTStartPoint[g_GameMTFloor][0];
					g_GameMTHeroY=GameMTStartPoint[g_GameMTFloor][1];
					GameMTNewFloor();
					GameMTReNewR();
					GameMTRefresh();
					return;
				}
	SysRestoreScreen(7,1,121,94,g_GameMTBuf);
}

/***********************************************************************
 * 函数名:	GameMTCheckMon()
 * 说明:		通过圣光徽察看本层怪物信息
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void GameMTCheckMon()
{
	U8 i,j,k,scoll,timeout;
	U16 temp,temp2;
	temp2=g_GameMTHeroDamige;
	scoll=0;
	timeout=4;
	for(i=0;i<8;i++)g_GameMTCheck[i]=0;
	for(i=0;i<11;i++)
		for(j=0;j<11;j++)
		{
			temp=(U16)g_GameMTFloor*121+i*11+j;
			if(g_GameMTCurMap[temp]>37&&g_GameMTCurMap[temp]<69)
			{
				k=0;
				while(k<8)
				{
					if(g_GameMTCheck[k]+1==g_GameMTCurMap[temp]+1)break;
					else if(g_GameMTCheck[k]+1==1)
					{
						g_GameMTCheck[k]=g_GameMTCurMap[temp];
						break;
					}
					k++;
				}
			}
		}
	if(g_GameMTCheck[0]+1==1)return;
	SysSaveScreen(0,0,158,95,g_GameMTBuf);
	SysLcdPartClear(0,0,158,95);
	SysRect(0,0,158,95);
	SysRect(1,1,157,94);
	SysPicture(56,5,64,14,GameMTChar[0],0);
	SysPicture(75,5,83,14,GameMTChar[1],0);
	SysPicture(92,5,100,14,GameMTChar[2],0);
	SysPicture(107,5,115,14,GameMTChar[3],0);
	SysPicture(120,5,128,14,GameMTChar[4],0);
	SysPicture(133,5,141,14,GameMTChar[5],0);
	SysPicture(144,5,152,14,GameMTChar[6],0);
	SysPicture(24,5,32,14,GameMTChar[7],0);
	SysPicture(34,5,42,14,GameMTChar[8],0);
	g_GameMTHeroDamige=temp2;
	GameMTListMon(scoll);
	while(1)
	{
		GameMTGetInput();if(g_GameMTQuit)break;
		if(g_GameMTReadKey==16)
		{
			timeout++;
			if(timeout==5)
			{
				SysLcdPartClear(7,8,13,11);
				if(scoll+1>1)SysPicture(7,9,13,12,GameMTNotice,0);
				SysLcdPartClear(7,89,13,92);
				if(scoll<4&&g_GameMTCheck[scoll+4]+1>1)SysPicture(7,88,13,91,GameMTNotice+4,0);
			}
			if(timeout==10)
			{
				SysLcdPartClear(7,9,13,12);
				if(scoll+1>1)SysPicture(7,8,13,11,GameMTNotice,0);
				SysLcdPartClear(7,88,13,91);
				if(scoll<4&&g_GameMTCheck[scoll+4]+1>1)SysPicture(7,89,13,92,GameMTNotice+4,0);
				timeout=0;
			}
		}
		if(g_GameMTReadKey==7)break;
		if(g_GameMTReadKey==3&&scoll+1>1)
		{
			scoll--;
			GameMTListMon(scoll);
		}
		if(g_GameMTReadKey==4&&(scoll<4)&&(g_GameMTCheck[scoll+4]+1!=1))
		{
			scoll++;
			GameMTListMon(scoll);
		}
	}
	SysRestoreScreen(0,0,158,95,g_GameMTBuf);
	g_GameMTHeroDamige=temp2;
}

/***********************************************************************
 * 函数名:	GameMTListMon(U8 scoll)
 * 说明:		列出怪物信息
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void GameMTListMon(U8 scoll)
{
	U8	k;
	for(k=0;k<4;k++)
			if(g_GameMTCheck[k+scoll]+1>1)
			{
				SysPicture(3,18*k+16,18,18*k+31,GameMTUnitPic[g_GameMTCheck[k+scoll]],0);
				SysLcdPartClear(19,18*k+16,156,18*k+31);
				SysPicture(20,18*k+19,50,18*k+28,GameMTMonName+(U16)(g_GameMTCheck[k+scoll]-38)*40,0);
				if(g_GameMTCheck[k+scoll]==57&&g_GameMTFloor==21)g_GameMTCheck[k+scoll]=70;
				if(g_GameMTCheck[k+scoll]==47&&g_GameMTFloor==19)g_GameMTCheck[k+scoll]=69;
				GameMTPrintNum(1,(U32)GameMTMonData[g_GameMTCheck[k+scoll]-38][0],59,18*k+19);
				GameMTPrintNum(1,(U32)GameMTMonData[g_GameMTCheck[k+scoll]-38][1],78,18*k+19);
				GameMTPrintNum(1,(U32)GameMTMonData[g_GameMTCheck[k+scoll]-38][2],95,18*k+19);
				GameMTPrintNum(1,(U32)GameMTMonData[g_GameMTCheck[k+scoll]-38][3],110,18*k+19);
				GameMTPrintNum(1,(U32)GameMTMonData[g_GameMTCheck[k+scoll]-38][4],123,18*k+19);
				if(GameMTMonData[g_GameMTCheck[k+scoll]-38][2]<g_GameMTHeroDamige)
				{
					if(GameMTMonData[g_GameMTCheck[k+scoll]-38][1]>g_GameMTHeroDefence)
					{
						if(GameMTCountLose(g_GameMTCheck[k+scoll]-38)<100000)
							GameMTPrintNum(1,GameMTCountLose(g_GameMTCheck[k+scoll]-38),143,18*k+19);
						else SysPicture(131,18*k+19,153,18*k+27,GameMTUnknown,0);
					}
					else	GameMTPrintNum(1,0,143,18*k+19);
				}
				else	SysPicture(131,18*k+19,153,18*k+27,GameMTUnknown,0);
			}
			if(g_GameMTCheck[k+scoll]==70)g_GameMTCheck[k+scoll]=57;
			if(g_GameMTCheck[k+scoll]==69)g_GameMTCheck[k+scoll]=47;
}

/***********************************************************************
 * 函数名:	GameMTCountLose(U8 monster)
 * 说明:		计算战斗损失生命
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR U32	GameMTCountLose(U8 monster)
{
	U32 count;
		count=(U32)(GameMTMonData[monster][0]/(g_GameMTHeroDamige-GameMTMonData[monster][2])-((GameMTMonData[monster][0]%(g_GameMTHeroDamige-GameMTMonData[monster][2])+1)==1)+1)*(GameMTMonData[monster][1]-g_GameMTHeroDefence);
	return	count;
}

/***********************************************************************
 * 函数名:	GameMTShop(U8 kind)
 * 说明:		各种商店购买函数
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR	void GameMTShop(U8 kind)/*商店类型：小升级，大升级，买商人，卖商人，小神殿，大神殿*/
{
	U8	choice,temp[20],flag;
	choice=0;
	switch(kind)
	{
		case 1:
		case 2:
			GameMTTalk(4,447,0);
			break;
		case 3:
			GameMTTalk(3,458,0);
			break;
		case 4:
			GameMTTalk(3,464,0);
			break;
		case 5:
			GameMTTalk(3,470,0);
			break;
		case 6:
			GameMTTalk(4,476,0);
	}
	SysSaveScreen(0,5,158,89,g_GameMTBuf);
	SysLcdPartClear(0,5,158,89);
	SysRect(0,5,158,89);
	SysRect(2,7,156,87);
	switch(kind)
	{
		case 1:
			GameMTGetTalk(451,temp);SysPrintString(6,11,temp);
			GameMTGetTalk(452,temp);SysPrintString(6,30,temp);
			GameMTGetTalk(453,temp);SysPrintString(6,49,temp);
			break;
		case 2:
			GameMTGetTalk(455,temp);SysPrintString(6,11,temp);
			GameMTGetTalk(456,temp);SysPrintString(6,30,temp);
			GameMTGetTalk(457,temp);SysPrintString(6,49,temp);
			break;
		case 3:
			GameMTGetTalk(461,temp);SysPrintString(6,11,temp);
			GameMTGetTalk(462,temp);SysPrintString(6,30,temp);
			GameMTGetTalk(463,temp);SysPrintString(6,49,temp);
			break;
		case 4:
			GameMTGetTalk(467,temp);SysPrintString(6,11,temp);
			GameMTGetTalk(468,temp);SysPrintString(6,30,temp);
			GameMTGetTalk(469,temp);SysPrintString(6,49,temp);
			break;
		case 5:
			GameMTGetTalk(473,temp);SysPrintString(6,11,temp);
			GameMTGetTalk(474,temp);SysPrintString(6,30,temp);
			GameMTGetTalk(475,temp);SysPrintString(6,49,temp);
			break;
		case 6:
			GameMTGetTalk(480,temp);SysPrintString(6,11,temp);
			GameMTGetTalk(481,temp);SysPrintString(6,30,temp);
			GameMTGetTalk(482,temp);SysPrintString(6,49,temp);
	}
	GameMTGetTalk(454,temp);SysPrintString(6,68,temp);
	SysRect(4,9,154,28);
	while(1)
	{
		GameMTGetInput();if(g_GameMTQuit)break;
		if(g_GameMTReadKey==16)continue;
		if(g_GameMTReadKey==7)break;
		if(g_GameMTReadKey==3&&choice+1>1)
		{
			SysRectClear(4,9+choice*19,154,28+choice*19);
			choice--;
			SysRect(4,9+choice*19,154,28+choice*19);
		}
		if(g_GameMTReadKey==4&&choice<3)
		{
			SysRectClear(4,9+choice*19,154,28+choice*19);
			choice++;
			SysRect(4,9+choice*19,154,28+choice*19);
		}
		if(g_GameMTReadKey==6)
		{
			flag=0;
			if(choice+1==1)
			{
				switch(kind)
				{
					case 1:
						if(g_GameMTHeroExp>99)
						{
							g_GameMTHeroLv+=1;
							g_GameMTHeroExp-=100;
							g_GameMTHeroLife+=1000;
							g_GameMTHeroDamige+=7;
							g_GameMTHeroDefence+=7;
							flag=1;
						}
						else flag=2;
						break;
					case 2:
						if(g_GameMTHeroExp>269)
						{
							g_GameMTHeroLv+=3;
							g_GameMTHeroExp-=270;
							g_GameMTHeroLife+=3000;
							g_GameMTHeroDamige+=21;
							g_GameMTHeroDefence+=21;
							flag=1;
						}
						else flag=2;
						break;
					case 3:
						if(g_GameMTHeroMoney>9)
						{
							g_GameMTHeroMoney-=10;
							g_GameMTKey[0]+=1;
							flag=1;
						}
						else flag=3;
						break;
					case 4:
						if(g_GameMTKey[0]+1>1)
						{
							g_GameMTHeroMoney+=7;
							g_GameMTKey[0]-=1;
							flag=1;
						}
						else flag=4;
						break;
					case 5:
						if(g_GameMTHeroMoney>24)
						{
							g_GameMTHeroMoney-=25;
							g_GameMTHeroLife+=800;
							flag=1;
						}
						else flag=3;
						break;
					case 6:
						if(g_GameMTHeroMoney>99)
						{
							g_GameMTHeroMoney-=100;
							g_GameMTHeroLife+=4000;
							flag=1;
						}
						else flag=3;
				}
			}
			if(choice==1)
			{
				switch(kind)
				{
					case 1:
						if(g_GameMTHeroExp>29)
						{
							g_GameMTHeroExp-=30;
							g_GameMTHeroDamige+=5;
							flag=1;
						}
						else flag=2;
						break;
					case 2:
						if(g_GameMTHeroExp>94)
						{
							g_GameMTHeroExp-=95;
							g_GameMTHeroDamige+=17;
							flag=1;
						}
						else flag=2;
						break;
					case 3:
						if(g_GameMTHeroMoney>49)
						{
							g_GameMTHeroMoney-=50;
							g_GameMTKey[1]+=1;
							flag=1;
						}
						else flag=3;
						break;
					case 4:
						if(g_GameMTKey[1]+1>1)
						{
							g_GameMTHeroMoney+=35;
							g_GameMTKey[1]-=1;
							flag=1;
						}
						else flag=4;
						break;
					case 5:
						if(g_GameMTHeroMoney>24)
						{
							g_GameMTHeroMoney-=25;
							g_GameMTHeroDamige+=4;
							flag=1;
						}
						else flag=3;
						break;
					case 6:
						if(g_GameMTHeroMoney>99)
						{
							g_GameMTHeroMoney-=100;
							g_GameMTHeroDamige+=20;
							flag=1;
						}
						else flag=3;
						break;
				}
			}
			if(choice==2)
			{
				switch(kind)
				{
					case 1:
						if(g_GameMTHeroExp>29)
						{
							g_GameMTHeroExp-=30;
							g_GameMTHeroDefence+=5;
							flag=1;
						}
						else flag=2;
						break;
					case 2:
						if(g_GameMTHeroExp>94)
						{
							g_GameMTHeroExp-=95;
							g_GameMTHeroDefence+=17;
							flag=1;
						}
						else flag=2;
						break;
					case 3:
						if(g_GameMTHeroMoney>99)
						{
							g_GameMTHeroMoney-=100;
							g_GameMTKey[2]+=1;
							flag=1;
						}
						else flag=3;
						break;
					case 4:
						if(g_GameMTKey[2]+1>1)
						{
							g_GameMTHeroMoney+=70;
							g_GameMTKey[2]-=1;
							flag=1;
						}
						else flag=4;
						break;
					case 5:
						if(g_GameMTHeroMoney>24)
						{
							g_GameMTHeroMoney-=25;
							g_GameMTHeroDefence+=4;
							flag=1;
						}
						else flag=3;
						break;
					case 6:
						if(g_GameMTHeroMoney>99)
						{
							g_GameMTHeroMoney-=100;
							g_GameMTHeroDefence+=20;
							flag=1;
						}
						else flag=3;
				}
			}
			if(choice==3)break;
			switch(flag)
			{
				case 1:
					SysMemcpy(temp,"  状态已更改!\0",14);
					GuiMsgBox(temp,50);
					break;
				case 2:
					SysMemcpy(temp,"    经验不足!\0",14);
					GuiMsgBox(temp,50);
					break;
				case 3:
					SysMemcpy(temp,"    金币不足!\0",14);
					GuiMsgBox(temp,50);
					break;
				case 4:
					SysMemcpy(temp,"    钥匙不足!\0",14);
					GuiMsgBox(temp,50);
					break;
			}
		}
	}
	SysRestoreScreen(0,5,158,89,g_GameMTBuf);
	GameMTReNewR();
}

/***********************************************************************
 * 函数名:	GameMTReNewR()
 * 说明:		更新英雄数据显示
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void GameMTReNewR()
{
	U8 i,temp[3];
	if(g_GameMTNearEnd)
	{
		if(g_GameMTCurTime!=SysGetSecond())
		{
			g_GameMTCurTime=SysGetSecond();
			g_GameMTDeadLine--;
		}
		temp[0]=g_GameMTDeadLine/10;
		temp[1]=g_GameMTDeadLine-10*temp[0]+'0';
		temp[0]+='0';
		temp[2]=0;
		SysPrintString(136,64,temp);
		if(g_GameMTDeadLine+1==1)GameMTEnd();
	}
	else
	{
		for(i=0;i<3;i++)
		{
			SysLcdPartClear(130+i*10,90,136+i*10,94);
			GameMTPrintNum(0,(U32)g_GameMTKey[i],133+i*10,90);
		}
		for(i=0;i<5;i++)
		{
			SysLcdPartClear(138,22+12*i,158,30+12*i);
			switch(i+1)
			{		
				case 1:
					if(g_GameMTHeroLife<100000)GameMTPrintNum(1,g_GameMTHeroLife,148,22);
						else GameMTPrintNum(1,99999,148,22);
					break;
				case 2:
					GameMTPrintNum(1,(U32)g_GameMTHeroDamige,148,34);
					break;
				case 3:
					GameMTPrintNum(1,(U32)g_GameMTHeroDefence,148,46);
					break;
				case 4:
					GameMTPrintNum(1,(U32)g_GameMTHeroMoney,148,58);
					break;
				case 5:
					GameMTPrintNum(1,(U32)g_GameMTHeroExp,148,70);
			}
		}
		SysLcdPartClear(138,1,150,8);
		SysLcdPartClear(130,11,146,18);
		GameMTPrintNum(2,(U32)g_GameMTFloor,142,1);
		GameMTPrintNum(2,(U32)g_GameMTHeroLv,138,11);
	}
}
