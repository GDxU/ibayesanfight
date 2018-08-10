/***********************************************************************
*Copyright (c)2001 , 广东步步高教育电子分公司
*All rights reserved.
**
文件名称：	magictower.c
*文件标识：	属于朗文BA818(A600)的游戏模块
*摘要：		游戏——魔塔
**
*移植性说明:
*	本程序对存储位置无要求
*修改历史：
*	版本    日期     作者     改动内容和原因
*   ----------------------------------------------------
*	1.0    2005.1.26  罗博明     DEBUGING...
***********************************************************************/
#include	"inc/dictsys.h"
#include	"inc/keytable.h"
#include	"mtower.h"
#include <stdlib.h>

/*游戏进入逃离模式,逃离模式时间,游戏完成标志,游戏结束标志,游戏初始化标志,退出游戏标志*/
U8	g_GameMTNearEnd,g_GameMTDeadLine,g_GameMTEnd,g_GameMTGameOver,g_GameMTInit,g_GameMTQuit;
/*获取用户输入,各个动画公用时间控制,英雄到达的最高层,英雄等级,现在逃离时间*/
U8	g_GameMTReadKey,g_GameMTTimeOut,g_GameMTTopFloor,g_GameMTHeroLv,g_GameMTCurTime;
U16	g_GameMTKBState;
/*单前所见地图x,y坐标,英雄当前x,y坐标,当前判断x,y坐标*/
U8	g_GameMTMapX,g_GameMTMapY,g_GameMTHeroX,g_GameMTHeroY,g_GameMTJuidgeX,g_GameMTJuidgeY;
/*图形缓存,英雄拥有的钥匙数,当前层怪信息*/
U8	g_GameMTBuf[19200],g_GameMTKey[3],g_GameMTCheck[8];
/*英雄攻击、防御、金币、经验*/
U16	g_GameMTHeroDamige,g_GameMTHeroDefence,g_GameMTHeroMoney,g_GameMTHeroExp;
/*英雄方向、所在层、地图数据缓存*/
U8	g_GameMTHeroDir,g_GameMTFloor,*g_GameMTCurMap;
/*英雄生命值*/
U32 g_GameMTHeroLife;
/*当前判断单元指针*/
U8	*g_GameMTJuidgeNow;

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
extern	U8	GameMTBattlePad[];
extern	U8	GameMTChar[][20];
extern	U8	GameMTNotice[];
extern	U16	GameMTMonData[][5];
extern	U8	GameMTVictory[];
extern	U8	GameMTStartPoint[][4];
extern	U8	GameMTLiKai[];
extern	U8	GameMTUnknown[];
extern	U8	GameMTMonName[];
extern	U8	GameMTMainFace[];
extern	U8	GameMTHappyEnd[];
extern	U8	GameMTEagle[];
extern	U8	GameMTHelpData[];

/***********************************************************************
 * 函数名:	GameMagicTower()
 * 说明:		游戏主程序
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR	U8	GameMagicTower()
{
	GuiInit();					/*Gui OS 初始化 */
	SysMemInit(MEM_HEAP_START,MEM_HEAP_SIZE);	/*初始化堆*/
	SysIconAllClear();
	
	g_GameMTKBState=GuiGetKbdState();			/* 取键盘状态 */
	GuiSetInputFilter(INPUT_ENG_ENABLE);
	GuiSetKbdType(INPUT_ENG_ENABLE);
	g_GameMTCurMap = malloc(2662);
	SysTimer1Open(8);
	
	g_GameMTInit=TRUE;
	g_GameMTQuit=FALSE;
	while(1)
	{
		if(g_GameMTQuit)
		{
			SysTimer1Close();
			break;
		}
		if(g_GameMTInit)GameMTInit();
		GameMTEvent();
	}
    return 0;
}

/***********************************************************************
 * 函数名:	GameMTGetInput()
 * 说明:		获取输入消息
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void	GameMTGetInput()
{
	MsgType		gMsg;
	g_GameMTReadKey=0;
	
	while(1){
		if(!GuiGetMsg(&gMsg)){
			g_GameMTReadKey=0;
			break;
		}
		if(!GuiTranslateMsg(&gMsg)){
				g_GameMTReadKey=0;
				break;
			}
		if((gMsg.type == WM_COMMAND) && (gMsg.param == CMD_RETURN_HOME))
			{
				g_GameMTQuit=TRUE;
				GuiSetKbdState(g_GameMTKBState);	/* 恢复键盘状态 */
				break;
			}
	switch(gMsg.type)
		{
			case	WM_CHAR_FUN:
				switch(gMsg.param)
					{
						case CHAR_LEFT:
							g_GameMTReadKey=1;
							break;
						case CHAR_RIGHT:
							g_GameMTReadKey=2;
							break;
						case CHAR_UP:					
							g_GameMTReadKey=3;
							break;
						case CHAR_DOWN:
							g_GameMTReadKey=4;
							break;
                            /*
						case CHAR_HELP:	
							GuiDownAppHelp(GameMTHelpData);				
							break;
                             */
						case CHAR_ENTER:					
							g_GameMTReadKey=6;
							break;
						case CHAR_EXIT:
							g_GameMTReadKey=7;
							break;
						case CHAR_SEARCH:
							g_GameMTReadKey=8;
				}
				break;
		case	WM_TIMER:
			g_GameMTReadKey=16;
		}
	break;
	}							
}

/***********************************************************************
 * 函数名:	GameMTRefresh()
 * 说明:		更新游戏界面
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void	GameMTRefresh()
{
	U8 	i,j,x,y;
	x=g_GameMTHeroX-g_GameMTMapX;
	y=g_GameMTHeroY-g_GameMTMapY;
	for(i=0;i<8;i++)
		for(j=0;j<6;j++)
			if(i==x&&j==y)SysPicture(x*16,y*16,x*16+15,y*16+15,GameMTHeroPic[g_GameMTHeroDir],0);
				else
					SysPicture(i*16,j*16,i*16+15,j*16+15,GameMTUnitPic[g_GameMTCurMap[(U16)g_GameMTFloor*121+(g_GameMTMapY+j)*11+g_GameMTMapX+i]],0);
	
}

/***********************************************************************
 * 函数名:	GameMTTalk(U8 line,U16 number,U8	flag)
 * 说明:		显示对话信息
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void	GameMTTalk(U8 line,U16 number,U8	flag)
{
	U8	i,temp[20];
	if(g_GameMTQuit)return;
	g_GameMTTimeOut=0;
	SysSaveScreenRect(4,5,154,90,g_GameMTBuf);
	/*SysRect(7,7,152,88);
	SysRect(6,6,153,89);
	SysRect(5,5,154,90);*/
	SysPicture(5,45-8*line,154,47-8*line,GameMTTalkUp,0);
	SysPicture(5,48+8*line,154,50+8*line,GameMTTalkDown,0);
	for(i=0;i<line;i++)
	{
		SysPicture(4,48-8*line+i*16,6,63-8*line+i*16,GameMTTalkSide,0);
		SysPicture(152,48-8*line+i*16,154,63-8*line+i*16,GameMTTalkSide,0);
	}
	for(i=0;i<line;i++)
		{
			SysLcdPartClear(7,48-8*line+i*16,7,48-8*line+i*16+14);
			if(number<343)
				SysPrintString(8,48-8*line+i*16,GameMTTalkData[number+i]);
				else
				{
					GameMTGetTalk(number+i,temp);
					SysPrintString(8,48-8*line+i*16,temp);
				}
		}
		while(1)
		{
			GameMTGetInput();
			if(g_GameMTQuit)break;
			if(g_GameMTReadKey==16)
			{
				g_GameMTTimeOut++;
				if(g_GameMTTimeOut==5&&flag)SysPicture(136,33+8*line,151,45+8*line,GameMTTalkSigh[0],0);
				if(g_GameMTTimeOut==10)
				{
					if(flag)SysPicture(136,33+8*line,151,45+8*line,GameMTTalkSigh[1],0);
					g_GameMTTimeOut=0;
				}
			}
			else break;
		}
	SysRestoreScreenRect(4,5,154,90,g_GameMTBuf);
}

/***********************************************************************
 * 函数名:	GameMTInit()
 * 说明:		游戏初始化函数
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
void	GameMTInit()
{
	U16 	i,j,k;
	GameMTMainMenu();
	if(g_GameMTQuit)return;
	SysLcdPartClear(0,0,158,95);
	g_GameMTInit=FALSE;
	g_GameMTMapX=2;
	g_GameMTMapY=5;
	g_GameMTTopFloor=0;
	g_GameMTHeroX=5;
	g_GameMTHeroY=10;
	g_GameMTHeroDir=2;
	g_GameMTHeroLv=1;
	g_GameMTHeroLife=1000;    /*英雄初始数据*/
	g_GameMTHeroDamige=10;
	g_GameMTHeroDefence=10;
	g_GameMTHeroMoney=0;
	g_GameMTHeroExp=0;
	g_GameMTFloor=0;
	g_GameMTGameOver=FALSE;
	g_GameMTDeadLine=90;
	g_GameMTNearEnd=FALSE;
	g_GameMTEnd=FALSE;
	g_GameMTQuit=FALSE;
	GameMTTalk(5,0,1);
	GameMTTalk(5,5,1);
	GameMTTalk(5,10,1);
	GameMTTalk(5,15,1);
	GameMTTalk(5,20,5);
	GameMTTalk(5,25,5);
	GameMTTalk(4,30,0);
	if(g_GameMTQuit)return;
	GameMTGetMapData();
	i=0;
	while(i<2662)
	{
		g_GameMTCurMap[i]-=40;
		i++;
	}
	g_GameMTKey[0]=0;
	g_GameMTKey[1]=0;
	g_GameMTKey[2]=0;
	SysPicture(128,0,158,95,GameMTWorkPad,0);
	GameMTReNewR();
	for(i=0;i<8;i++)
		for(j=0;j<6;j++)
			SysPicture(i*16,j*16,i*16+15,j*16+15,GameMTUnitPic[g_GameMTCurMap[g_GameMTFloor*121+(g_GameMTMapY+j)*11+g_GameMTMapX+i]],0);
	SysPicture((g_GameMTHeroX-g_GameMTMapX)*16,(g_GameMTHeroY-g_GameMTMapY)*16,(g_GameMTHeroX-g_GameMTMapX)*16+15,(g_GameMTHeroY-g_GameMTMapY)*16+15,GameMTHeroPic[g_GameMTHeroDir],0);
	g_GameMTCurMap[154]=33;
}

/***********************************************************************
 * 函数名:	GameMTMove()
 * 说明:		英雄移动控制
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void	GameMTMove()
{
	
		switch(g_GameMTReadKey){
			case	1:
				if(g_GameMTHeroX+1>1)g_GameMTHeroX--;
				if(g_GameMTMapX+1>1&&g_GameMTHeroX-g_GameMTMapX<3)g_GameMTMapX--;
				break;
			case	2:
				if(g_GameMTHeroX<10)g_GameMTHeroX++;
				if(g_GameMTMapX<3&&g_GameMTHeroX-g_GameMTMapX>4)g_GameMTMapX++;
				break;
			case	3:
				if(g_GameMTHeroY+1>1)g_GameMTHeroY--;
				if(g_GameMTMapY+1>1&&g_GameMTHeroY-g_GameMTMapY<2)g_GameMTMapY--;
				break;
			case	4:
				if(g_GameMTHeroY<10)g_GameMTHeroY++;
				if(g_GameMTMapY<5&&g_GameMTHeroY-g_GameMTMapY>3)g_GameMTMapY++;
				break;
				}	
}

/***********************************************************************
 * 函数名:	GameMTPrintNum(U8 flag,U32 number,U8 x,U8 y)
 * 说明:		显示游戏中的各类数字
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void GameMTPrintNum(U8 flag,U32 number,U8 x,U8 y)
{
	U16 i[6];
	U8	j,lengh;
	i[0]=number-number/10*10;
	lengh=1;
	if(number>=10)
	{
		i[1]=number/10-number/100*10;
		lengh=2;
	}
	if(number>=100)
	{
		i[2]=number/100-number/1000*10;
		lengh=3;
	}
	if(number>=1000)
	{
		i[3]=number/1000-number/10000*10;
		lengh=4;
	}
	if(number>=10000)
	{
		i[4]=number/10000-number/100000*10;
		lengh=5;
	}
	if(number>=100000)
	{
		i[5]=number/100000-number/1000000*10;
		lengh=6;
	}
	if(flag==1){for(j=0;j<lengh;j++)SysPicture(x+lengh*2-j*4-3,y,x+lengh*2-j*4,y+8,GameMTNum39+9*i[j],0);}
		else 	if(flag==2){for(j=0;j<lengh;j++)SysPicture(x+lengh*4-j*7-6,y,x+lengh*4-j*7,y+7,GameMTNum78+8*i[j],0);}
			else	for(j=0;j<lengh;j++)SysPicture(x+lengh*2-j*4-3,y,x+lengh*2-j*4,y+4,GameMTNum35+5*i[j],0);
}

/***********************************************************************
 * 函数名:	GameMTBattle(U8	number)
 * 说明:		战斗功能函数
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR U8	GameMTBattle(U8	number)
{
	U8	i,p,info[33],temp;
	U16	TempL;
	for(i=0;i<13;i++)info[i]=GameMTVictory[i];
	p=1;
	temp=g_GameMTMapY;
	if(GameMTMonData[number][3]>=10)
	{
		if(GameMTMonData[number][3]>=100)
		{
			info[14]='0'+GameMTMonData[number][3]/10-GameMTMonData[number][3]/100*10;
			info[13]='0'+GameMTMonData[number][3]/100;
			p=3;
		}
			else 
			{
				info[13]='0'+GameMTMonData[number][3]/10-GameMTMonData[number][3]/100*10;
				p=2;
			}
	}
	info[12+p]='0'+GameMTMonData[number][3]-GameMTMonData[number][3]/10*10;
	for(i=0;i<8;i++)info[13+p+i]=GameMTVictory[i+13];
	if(GameMTMonData[number][4]>=10)
	{
		if(GameMTMonData[number][4]>=100)
		{
			info[22+p]='0'+GameMTMonData[number][4]/10-GameMTMonData[number][4]/100*10;
			info[21+p]='0'+GameMTMonData[number][4]/100;
			p+=2;
		}
			else 
			{
				info[21+p]='0'+GameMTMonData[number][4]/10-GameMTMonData[number][4]/100*10;
				p+=1;
			}
	}
	info[21+p]='0'+GameMTMonData[number][4]-GameMTMonData[number][4]/10*10;
	for(i=0;i<8;i++)info[22+p+i]=GameMTVictory[i+21];
	if(GameMTMonData[number][2]>=g_GameMTHeroDamige)
	{
		GameMTTalk(2,441,0);
		g_GameMTMapY=temp;
		return 0;
	}
	if(GameMTMonData[number][1]>g_GameMTHeroDefence&&GameMTCountLose(number)>g_GameMTHeroLife)
	{
		GameMTTalk(2,443,0);
		return 0;
	}
	SysSaveScreenRect(8,14,119,81,g_GameMTBuf);
	SysPicture(8,14,119,81,GameMTBattlePad,0);
	TempL=GameMTMonData[number][0];
	GameMTPrintNum(1,g_GameMTHeroLife,92,41);
	GameMTPrintNum(1,(U32)g_GameMTHeroDamige,92,53);
	GameMTPrintNum(1,(U32)g_GameMTHeroDefence,92,65);
	GameMTPrintNum(1,(U32)GameMTMonData[number][0],33,41);
	GameMTPrintNum(1,(U32)GameMTMonData[number][1],33,52);
	GameMTPrintNum(1,(U32)GameMTMonData[number][2],33,65);
	SysPicture(15,21,30,36,GameMTUnitPic[g_GameMTCurMap[(U16)g_GameMTFloor*121+g_GameMTJuidgeY*11+g_GameMTJuidgeX]],0);
	g_GameMTTimeOut=0;
	while(1)
		{
			GameMTGetInput();if(g_GameMTQuit)break;
			if(TempL+1==1)break;
			g_GameMTTimeOut++;
			if(g_GameMTTimeOut==5)
			{
				g_GameMTTimeOut=0;
				if(TempL>g_GameMTHeroDamige-GameMTMonData[number][2])
					TempL-=g_GameMTHeroDamige-GameMTMonData[number][2];
					else TempL=0;
				SysLcdPartClear(23,41,43,49);
				GameMTPrintNum(1,(U32)TempL,33,41);
				if(GameMTMonData[number][1]>g_GameMTHeroDefence)
				{
					g_GameMTHeroLife-=GameMTMonData[number][1]-g_GameMTHeroDefence;
					SysLcdPartClear(82,41,102,49);
					GameMTPrintNum(1,g_GameMTHeroLife,92,41);
				}
			}
		}
	GuiMsgBox(info,100);
	g_GameMTCurMap[(U16)g_GameMTFloor*121+g_GameMTJuidgeY*11+g_GameMTJuidgeX]=0;
	g_GameMTHeroMoney+=GameMTMonData[number][3];
	g_GameMTHeroExp+=GameMTMonData[number][4];
	SysRestoreScreenRect(8,14,119,81,g_GameMTBuf);
	GameMTReNewR();
	return 1;
}

/***********************************************************************
 * 函数名:	GameMTOpenDoor()
 * 说明:		打开游戏中各种门动画
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void GameMTOpenDoor()
{
	 U8	i,Buf[32],flag;
	 for(i=0;i<32;i++)Buf[i]=GameMTUnitPic[g_GameMTCurMap[(U16)g_GameMTFloor*121+g_GameMTJuidgeY*11+g_GameMTJuidgeX]][i];
	 flag=g_GameMTCurMap[(U16)g_GameMTFloor*121+g_GameMTJuidgeY*11+g_GameMTJuidgeX];
	 if(flag==8)
	 {
	 		for(i=0;i<16;i++)
	 		{
	 			GameMTGetInput();
	 			if(g_GameMTQuit)return;
	 			SysPicture((g_GameMTJuidgeX-g_GameMTMapX)*16,(g_GameMTJuidgeY-g_GameMTMapY)*16,(g_GameMTJuidgeX-g_GameMTMapX)*16+15,(g_GameMTJuidgeY-g_GameMTMapY)*16+15-i,Buf+i*2,0);
	 			if(i+1>1)SysLcdPartClear((g_GameMTJuidgeX-g_GameMTMapX)*16,(g_GameMTJuidgeY-g_GameMTMapY)*16+16-i,(g_GameMTJuidgeX-g_GameMTMapX)*16+15,(g_GameMTJuidgeY-g_GameMTMapY)*16+16-i);
	 		}
	 }
	 else 
	 {
	 		for(i=0;i<8;i++)
	 		{
	 			GameMTGetInput();if(g_GameMTQuit)return;
	 			for(flag=0;flag<16;flag++)
	 			{
	 				Buf[flag*2]=Buf[flag*2]<<1;
	 				Buf[flag*2+1]=Buf[flag*2+1]>>1;
	 			}
	 			SysPicture((g_GameMTJuidgeX-g_GameMTMapX)*16,(g_GameMTJuidgeY-g_GameMTMapY)*16,(g_GameMTJuidgeX-g_GameMTMapX)*16+15,(g_GameMTJuidgeY-g_GameMTMapY)*16+15,Buf,0);
	 		}
	 }
}

/***********************************************************************
 * 函数名:	GameMTNewFloor()
 * 说明:		换层更新信息
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void GameMTNewFloor()
{
	U8	text[14],f;
	f=g_GameMTFloor/10;
	if(g_GameMTHeroX>6)g_GameMTMapX=3;
		else if(g_GameMTHeroX>4)g_GameMTMapX=g_GameMTHeroX-4;
			else g_GameMTMapX=0;
	if(g_GameMTHeroY>7)g_GameMTMapY=5;
		else if(g_GameMTHeroY>3)g_GameMTMapY=g_GameMTHeroY-3;
			else g_GameMTMapY=0;
	g_GameMTJuidgeY=g_GameMTHeroX;
	g_GameMTJuidgeX=g_GameMTHeroY;
	SysMemcpy(text,"   魔塔第",9);
	if(f+1>1)
	{
		text[9]='0'+f;
		text[10]='0'+g_GameMTFloor-10*f;
		SysMemcpy(text+11,"层\0",3);
	}
		else
		{
			text[9]='0'+g_GameMTFloor;
			SysMemcpy(text+10,"层\0",3);
		}
	GameMTRefresh();
	GuiMsgBox(text,100);
}

/***********************************************************************
 * 函数名:	GameMTEndFace()
 * 说明:		游戏将要结束界面
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void GameMTEndFace()
{
	U8 temp[3];
	g_GameMTNearEnd=TRUE;
	SysLcdPartClear(129,0,158,95);
	SysMemcpy(temp,"倒\0",3);
	SysPrintString(136,0,temp);
	SysMemcpy(temp,"计\0",3);
	SysPrintString(136,16,temp);
	SysMemcpy(temp,"时\0",3);
	SysPrintString(136,32,temp);
	SysMemcpy(temp,"：\0",3);
	SysPrintString(140,48,temp);
	SysMemcpy(temp,"秒\0",3);
	SysPrintString(136,80,temp);
}
