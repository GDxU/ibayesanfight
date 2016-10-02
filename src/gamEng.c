/***********************************************************************
 *Copyright (c)2005 , 东莞步步高教育电子分公司
 *All rights reserved.
 **
 文件名称：	gamEng.c
 *文件标识：	步步高电子词典的游戏引擎模块
 *摘要：		游戏引擎主程序
 **
 *移植性声明:
 *	1、符合标准：《游戏设计标准V1.0》
 *	2、兼容模式：平移兼容|缩放兼容
 *修改历史：
 *	版本    日期     作者     改动内容和原因
 *   ----------------------------------------------------
 *	1.0    2005.5.16  高国军     基本的功能完成
 ***********************************************************************/
#include "baye/stdsys.h"
#include "baye/comm.h"
#undef	GamEng
#define	GamEng
#include "baye/enghead.h"
#define		IN_FILE	1	/* 当前文件位置 */

static const U8*dataDir;

static gam_FILE* sav_fopen(U8*filename, U8 mode)
{
    U8 pathBuf[2048];
    pathBuf[0] = 0;
    gam_strcat(pathBuf, dataDir);
    gam_strcat(pathBuf, "/");
    gam_strcat(pathBuf, filename);
    return gam_fopen(pathBuf, mode);
}

/*本体函数声明*/
/*------------------------------------------*/
U8 GamVarInit(void);
void GamVarRst(void);
U8 GamMovie(U16 speID);
bool GamMainChose(void);
void GamMakerInf(void);
void GamShowErrInf(U8 idx);
U8 GamGetKing(U8 num);
void GamShowKing(U8 pTop);
void GamRevCity(U8 cycnt,U8 *tbuf,U8 *pos);
U8 GamPicMenu(U16 picID,U16 speID);
void GamRcdIFace(U8 count);
bool GamSaveRcd(U8 idx);
bool GamLoadRcd(U8 idx);
void GamLoadEngineConfig(void);

#define	DBG_MEM_AFTER	0
#define	DBG_MEM_BEFURE	1

/***********************************************************************
 * 说明:     游戏引擎主程序
 * 输入参数: 无
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR void GamBaYeEng(void)
{
    /* 初始化游戏环境 */
    if(GamConInit())
    {
        GamShowErrInf(0);
        return;
    }

    /* 从lib读取引擎参数 */
    GamLoadEngineConfig();

    /* 显示游戏开始动画 */
    GamMovie(MAIN_SPE);

    /* 初始化游戏变量 */
    if(GamVarInit())
    {
        GamShowErrInf(1);
        GamVarRst();
        GamConRst();
        return;
    }

    do
    {
        /* 获取游戏选项 */
        if(!GamMainChose())
            break;
        GameDevDrv();	 	/* 游戏引擎入口程序 */
    } while (1);


    GamVarRst();
    GamConRst();
}
/***********************************************************************
 * 说明:     初始化游戏引擎变量
 * 输入参数: 无
 * 返回值  : 0-操作成功		!0-错误代码
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
U8 GamVarInit(void)
{
    g_RunErr = NONE_ERR;

    gam_memset(FIGHTERS_IDX, 0, FIGHT_ORDER_MAX);
    gam_memset((U8 *)ORDERQUEUE, 0xff, (U16)ORDER_MAX * sizeof(OrderType));

    g_FightMap = gam_malloc(SCR_MAPWID*SCR_MAPHGT);		/* 50 */
    if (NULL == g_FightMap)
        return 1;
    g_FightPath = gam_malloc(FGT_MRG*FGT_MRG + 25);		/* 250 */
    if (NULL == g_FightPath)
        return 1;
    g_FgtAtkRng = gam_malloc(MAX_ATT_RANGE + 5);		/* 86 */
    if (NULL == g_FgtAtkRng)
        return 1;

    g_Persons = (PersonType *) gam_malloc(sizeof(PersonType) * PERSON_MAX + 4);	/* 3004 */
    if (NULL == g_Persons)
        return 1;
    g_OrderHead = (OrderQueueType *) NULL;
    g_OrderEnd = (OrderQueueType *) NULL;

    g_PlayerKing = 0;
    g_CityPos.x = 0;
    g_CityPos.y = 0;
    g_CityPos.setx = 0;
    g_CityPos.sety = 0;
    g_YearDate = 0;
    g_MonthDate = 1;
    g_LookEnemy = true;
    g_LookMovie = true;
    g_MoveSpeed = true;
    return 0;
}
/***********************************************************************
 * 说明:     恢复游戏引擎变量——释放系统资源
 * 输入参数: 无
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
void GamVarRst(void)
{
    gam_free((U8 *)g_FightMap);
    gam_free((U8 *)g_FightPath);
    gam_free((U8 *)g_FgtAtkRng);
    gam_free((U8 *)g_Persons);
}
/***********************************************************************
 * 说明:     驱动玩家在主菜单中的选择
 * 输入参数: 无
 * 返回值  : true-进入游戏	false-退出游戏
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
bool GamMainChose(void)
{
    U8	*posptr;
    U8	idx;
    U8	i,c;

    while(1)
    {
        U8 choice = GamPicMenu(MAIN_PIC,MAIN_ICON1);
        switch(choice)
        {
            case 0:		/* 新君登基 */
                idx = GamPicMenu(YEAR_PIC,YEAR_ICON1);
                if(idx == MNU_EXIT)
                    break;
                idx = GetPeriodKings(idx + 1,g_FgtAtkRng); 	/* 设置历史时期，并获取君主队列 */
                idx = GamGetKing(idx);
                if(idx == MNU_EXIT)
                    break;
                g_PlayerKing = idx;				/* 设置玩家扮演的君主ID */

                for (idx = 0;idx < CITY_MAX;idx ++)
                {
                    if (g_Cities[idx].Belong == (g_PlayerKing + 1))
                    {
                        posptr = ResLoadToCon(IFACE_CONID,dCityPos,g_CBnkPtr);
                        g_CityPos.setx = posptr[idx << 1];
                        g_CityPos.sety = posptr[(idx << 1) + 1];
                        if ((g_CityPos.setx + SHOWMAP_WS / 2) >= CITYMAP_W)
                            g_CityPos.x = CITYMAP_W - SHOWMAP_WS;
                        else if (g_CityPos.setx < SHOWMAP_WS / 2)
                            g_CityPos.x = 0;
                        else
                            g_CityPos.x = g_CityPos.setx - SHOWMAP_WS / 2;

                        if ((g_CityPos.sety + SHOWMAP_HS / 2) >= CITYMAP_H)
                            g_CityPos.y = CITYMAP_H - SHOWMAP_HS;
                        else if (g_CityPos.sety < SHOWMAP_HS / 2)
                            g_CityPos.y = 0;
                        else
                            g_CityPos.y = g_CityPos.sety - SHOWMAP_HS / 2;
                        break;
                    }
                }
                posptr = SHARE_MEM;
                for (idx = 0;idx < CITY_MAX;idx ++)
                {
                    if (g_Cities[idx].Belong != (g_PlayerKing + 1))
                    {
                        c = GetCityPersons(idx,posptr);
                        for (i = 0;i < c;i ++)
                        {
                            g_Persons[posptr[i]].Arms = 800;
                        }
                        ADD16(g_Cities[idx].Food, 1000);
                    }
                }
                g_FromSave = 0;
                return true;
            case 1:		/* 重返沙场 */
                idx = GamRecordMan(true);
                if(idx == MNU_EXIT)
                    break;
                g_FromSave = 1;
                return true;
            case 2:		/* 制作群组 */
                GamMakerInf();
                break;
            case 3:		/* 卸甲归田 */
            case MNU_EXIT:
                return false;
        }
    }
}

// TODO:示例代码, 需整理
typedef struct {
    I16 left;
    I16 top;
    I16 right;
    I16 bottom;
} Rect;

U8 isPointInRect(I16 x, I16 y, Rect r) {
    return (r.left <= x && x <= r.right) && (r.top <= y && y <= r.bottom);
}

/***********************************************************************
 * 说明:     驱动游戏主菜单，并获取相应的选择
 * 输入参数: 无
 * 返回值  : 0-操作成功		!0-错误代码
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
U8 GamPicMenu(U16 picID,U16 speID)
{
    U8	mIdx;
    GMType	pMsg;

    mIdx = 0;
    PlcRPicShow(picID,1,WK_SX,WK_SY,false);
    while(1)
    {
        U8 key = GamMovie(speID + mIdx);
        if (key == 0 || key == 0xff) {
            GamGetMsg(&pMsg);
        }
        else {
            GamGetLastMsg(&pMsg);
        }
        if(VM_CHAR_FUN == pMsg.type)
        {
            switch(pMsg.param)
            {
                case VK_UP:
                case VK_LEFT:
                    mIdx -= 1;
                    break;
                case VK_DOWN:
                case VK_RIGHT:
                    mIdx += 1;
                    break;
                case VK_ENTER:
                    return mIdx;
                case VK_EXIT:
                    return MNU_EXIT;
            }
            mIdx = mIdx % 4;
            PlcRPicShow(picID,1,WK_SX,WK_SY,false);
        }
        else if (VM_TOUCH == pMsg.type) {
            // 触控示例
            if (pMsg.param == VT_TOUCH_UP) {

                I16 x = pMsg.param2.i16.p0;
                I16 y = pMsg.param2.i16.p1;

                Rect buttonRects[] = {
                    {6, 45, 73, 63}, //新君登基
                    {83, 45, 151, 63}, //重返沙场
                    {6, 70, 73, 88}, //制作群组
                    {83, 71, 151, 88}, //解甲归田
                };

                for (U8 i = 0; i < 4; i++) {
                    if (isPointInRect(x, y, buttonRects[i])) {
                        // 已经选中则进入， 否则选中
                        if (i == mIdx) {
                            return mIdx;
                        } else {
                            mIdx = i;
                            PlcRPicShow(picID,1,WK_SX,WK_SY,false);
                            break;
                        }
                    }
                }
            }
        }
    }
}
/***********************************************************************
 * 说明:     开发群组——游戏开发人员登场了！
 * 输入参数: 无
 * 返回值  : 0-操作成功		!0-错误代码
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
void GamMakerInf(void)
{
    gam_memset(g_VisScr,0,WK_BLEN);
    GamMovie(MAKER_SPE);
    GamDelay(5000,true);
}
/***********************************************************************
 * 说明:     获取玩家要扮演的君主ID
 * 输入参数: num-君主队列人数
 * 返回值  : 玩家选中的君主ID	MNU_EXIT-跳出
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
U8 GamGetKing(U8 num)
{
    U8	*pos,tbuf[CITY_MAX];
    U8	pTop,pIdx,pSLen;
    U8	cycnt,ry;
    bool	rflag;
    GMType	pMsg;

    gam_clslcd();
    /* 获取君主的名字到g_FightPath中（只取前6个字节） */
    for(pIdx = 0;pIdx < num;pIdx += 1)
    {
        pTop = pIdx * 6;
        GetPersonName(g_FgtAtkRng[pIdx],g_FightPath + pTop);
        pSLen = gam_strlen(g_FightPath);
        if(pSLen < pTop + 6)
            gam_memset(g_FightPath + pSLen,' ',pTop + 6 - pSLen);
    }
    /* 获取城市坐标指针 */
    gam_rect(WK_SX,WK_SY,WK_EX,WK_EY);
    ResLoadToMem(IFACE_STRID,dChoseKing,tbuf);
    GamStrShowS(KING_TX,KING_TY,tbuf);
    PlcRPicShow(CITY_PIC,1,CITY_SX,CITY_SY,true);
    gam_rect(KING_SX - 3,KING_SY - 3,KING_EX + 2, (WK_EY - 6 - (KING_SY)) / HZ_HGT * HZ_HGT + KING_SY + 2);

    /* 选择要扮演的君主 */
    pos = ResLoadToCon(IFACE_CONID,dCityPos,g_CBnkPtr);
    pTop = 0;
    pIdx = 0;
    rflag = false;
    GamShowKing(pTop);
    ry = (pIdx - pTop) * HZ_HGT + KING_SY;
    gam_revlcd(KING_SX,ry,KING_EX,ry + HZ_HGT);
    cycnt = GetKingCitys(g_FgtAtkRng[pIdx],tbuf); 		/* 获取治下城市队列 */
    while(1)
    {
        GamGetMsg(&pMsg);
        if(VM_CHAR_FUN == pMsg.type)
        {
            gam_revlcd(KING_SX,ry,KING_EX,ry + HZ_HGT);
            if(rflag)
            {
                GamRevCity(cycnt,tbuf,pos);
                rflag = false;
            }
            switch(pMsg.param)
            {
                case VK_UP:
                    if(pIdx)
                    {
                        if(pIdx == pTop)
                            pTop -= 1;
                        pIdx -= 1;
                    }
                    break;
                case VK_DOWN:
                    if(pIdx < num - 1)
                    {
                        pIdx += 1;
                        if(pIdx - pTop > ((WK_EY - 6 - (KING_SY)) / HZ_HGT) - 1)
                            pTop += 1;
                    }
                    break;
                case VK_EXIT:
                    return MNU_EXIT;
                case VK_ENTER:
                    return g_FgtAtkRng[pIdx];
            }
            GamShowKing(pTop);
            ry = (pIdx - pTop) * HZ_HGT + KING_SY;
            gam_revlcd(KING_SX,ry,KING_EX,ry + HZ_HGT);
            cycnt = GetKingCitys(g_FgtAtkRng[pIdx],tbuf);	/* 获取治下城市队列 */
        }
        else
        {
            rflag = !rflag;
            GamRevCity(cycnt,tbuf,pos);
        }
    }
}
/***********************************************************************
 * 说明:     闪烁显示当前君主的城池
 * 输入参数: cycnt-城池个数	tbuf-城池队列	pos-城池坐标队列
 * 返回值  : 0-操作成功		!0-错误代码
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
void GamRevCity(U8 cycnt,U8 *tbuf,U8 *pos)
{
    U8	i,sx,sy;

    for(i = 0;i < cycnt;i += 1)
    {
        sx = tbuf[i] << 1;
        sy = pos[sx + 1] * 7 + CITY_SY + 3;
        sx = pos[sx] * 7 + CITY_SX + 3;
        gam_revlcd(sx,sy,sx + 1,sy + 1);
    }
}
/***********************************************************************
 * 说明:     显示游戏开头的动画
 * 输入参数: 无
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
void GamShowKing(U8 pTop)
{
    c_Sx = KING_SX;
    c_Ex = KING_EX;
    c_Sy = KING_SY;
    c_Ey = (WK_EY - 6 - (KING_SY)) / HZ_HGT * HZ_HGT + KING_SY;
    GamStrShowS(KING_SX,KING_SY,g_FightPath + (pTop * 6));
}
/***********************************************************************
 * 说明:     显示游戏开头的动画
 * 输入参数: 无
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
U8 GamMovie(U16 speID)
{
    SPERES	*srsptr;

    srsptr = (SPERES *)ResLoadToCon(speID,1,g_CBnkPtr);
    return PlcMovie(speID,0,srsptr->endfrm,true,WK_SX,WK_SY);
}
/***********************************************************************
 * 说明:     显示出错信息
 * 输入参数: idx-信息序号
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
void GamShowErrInf(U8 idx)
{
    U8	tbuf[50];

    ResLoadToMem(IFACE_STRID,idx + dGamConErr,tbuf);
    GamMsgBox(tbuf,2);
}
/***********************************************************************
 * 说明:     档案管理（提供存档和读取档案的函数）
 * 输入参数: flag：true-读档管理	false-存档管理
 * 返回值  : !0xFF-所操作的档案序号	0xFF-取消
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR U8 GamRecordMan(U8 flag)
{
    U8	idx,ry;
    bool	pflag;
    GMType	pMsg;
    U8 count = flag ? 4 : 3;

    GamRcdIFace(count);
    idx = 0;
    ry = WK_SY + 33;
    U8 right = WK_SX + 31 + 95;
    gam_revlcd(WK_SX + 31,ry, right, ry + HZ_HGT);
    while(1)
    {
        GamGetMsg(&pMsg);
        if(VM_CHAR_FUN == pMsg.type)
        {
            gam_revlcd(WK_SX + 31,ry,right,ry + HZ_HGT);
            switch(pMsg.param)
            {
                case VK_UP:
                    idx -= 1;
                    break;
                case VK_DOWN:
                    idx += 1;
                    break;
                case VK_ENTER:
                    if(flag)
                        pflag = GamLoadRcd(idx);
                    else
                        pflag = GamSaveRcd(idx);
                    if(pflag)
                        return idx;
                    GamRcdIFace(count);
                    break;
                case VK_EXIT:
                    return MNU_EXIT;
            }
            idx = idx % count;
            ry = idx * 14 + WK_SY + 33;
            gam_revlcd(WK_SX + 31,ry, right,ry + HZ_HGT);
        }
    }
}
/***********************************************************************
 * 说明:     初始化游戏引擎所在的机型环境
 * 输入参数: 无
 * 返回值  : 0-操作成功		!0-错误代码
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
void GamRcdIFace(U8 count)
{
    U8	idx,king,fnam[20];
    U8	pbak,tbuf[10];
    U16	year;
    gam_FILE	*fp;

    PlcRPicShow(SAVE_PIC,1,WK_SX,WK_SY,true);
    pbak = g_PIdx;
    for(idx = 0;idx < count;idx += 1)
    {
        ResLoadToMem(IFACE_STRID,dSaveFNam,fnam);
        fnam[5] = (idx << 1) + 0x30;		/* fnam = "sango?.sav" */
        fp = sav_fopen(fnam,'r');
        if(NULL == fp)
            ResLoadToMem(IFACE_STRID,dNullFNam,fnam);	/* fnam = "空" */
        else
        {
            U8 verFlag;
            gam_fread((U8 *)&verFlag,1,1,fp);
            if (verFlag & 0x80) {
                gam_fread((U8 *)&g_PIdx,1,1,fp);
            } else {
                g_PIdx = verFlag;
            }
            gam_fread((U8 *)&king,1,1,fp);
            gam_fread((U8 *)&year,1,2,fp);
            gam_fclose(fp);
            ResLoadToMem(IFACE_STRID,dRecordInf,fnam);
            GetPersonName(king,tbuf);
            king = gam_strlen(tbuf);
            gam_memcpy(fnam,tbuf,king);		/* fnam = "君主       年" */
            gam_itoa(year,tbuf,10);
            king = gam_strlen(tbuf) + 1;
            gam_memcpy(fnam + 10,tbuf,king);	/* fnam = "君主    ???年" */
        }
        GamStrShowS(WK_SX + 31,WK_SY + 33 + idx * 14,fnam);
    }
    g_PIdx = pbak;
}
/***********************************************************************
 * 说明:     载入指定序号的档案
 * 输入参数: idx-指定序号
 * 返回值  : 0-操作成功		!0-错误代码
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
bool GamLoadRcd(U8 idx)
{
    U8	tbuf[20];
    gam_FILE	*fp;
    U8 verFlag = 0;

    ResLoadToMem(IFACE_STRID,dReading,tbuf);
    GamMsgBox(tbuf,0);
    ResLoadToMem(IFACE_STRID,dSaveFNam,tbuf);

    /* 读取第一个文件 */
    tbuf[5] = (idx << 1) + 0x30;		/* tbuf = "sango?.sav" */
    fp = sav_fopen(tbuf,'r');
    if(NULL == fp)
    {
        ResLoadToMem(IFACE_STRID,dErrInf1,tbuf);
        GamMsgBox(tbuf,2);
        return false;
    }

    gam_fread((U8 *)&verFlag,1,1,fp);

    U8 version = 0;

    U16 goodsQueueLen = GOODS_MAX;
    U16 orderQueueLen = ORDER_MAX;
    U16 personQueueLen = PERSON_MAX;

    if (verFlag & 0x80) {
        version = verFlag;
    }

    if (version == 0) {
        g_PIdx = verFlag;
    } else {
        gam_fread((U8 *)&g_PIdx,1,1,fp);
    }

    if (version < 0x80) {
        goodsQueueLen = 33;
    }

    if (version < 0x81) {
        orderQueueLen = 100;
    }

    if (version < 0x82) {
        personQueueLen = 200;
    }

    gam_fread((U8 *)&g_PlayerKing,1,1,fp);
    gam_fread((U8 *)&g_YearDate,2,1,fp);
    gam_fread((U8 *)&g_LookEnemy,1,1,fp);
    gam_fread((U8 *)&g_LookMovie,1,1,fp);
    gam_fread((U8 *)&g_MoveSpeed,1,1,fp);
    gam_fread((U8 *)&g_MonthDate,1,1,fp);
    gam_fread((U8 *)&g_CityPos,sizeof(CitySetType),1,fp);
    gam_fread((U8 *)g_Persons,sizeof(PersonType),personQueueLen,fp);
    gam_fread((U8 *)g_PersonsQueue,1,personQueueLen,fp);
    gam_fread((U8 *)g_GoodsQueue,1,goodsQueueLen,fp);
    gam_fclose(fp);
    
    /* 读取第二个文件 */
    tbuf[5] = (idx << 1) + 0x31;		/* tbuf = "sango?.sav" */
    fp = sav_fopen(tbuf,'r');
    if(NULL == fp)
    {
        ResLoadToMem(IFACE_STRID,dErrInf1,tbuf);
        GamMsgBox(tbuf,2);
        return false;
    }
    
    gam_fread((U8 *)FIGHTERS_IDX,1,FIGHT_ORDER_MAX,fp);
    gam_fread((U8 *)FIGHTERS,10,FIGHT_ORDER_MAX,fp);
    gam_fread((U8 *)ORDERQUEUE,sizeof(OrderType), orderQueueLen, fp);
    gam_fread((U8 *)g_Cities,sizeof(CityType),CITY_MAX,fp);
    
    gam_fclose(fp);
    return true;	
}
/***********************************************************************
 * 说明:     存储指定序号的档案
 * 输入参数: idx-指定序号
 * 返回值  : 0-操作成功		!0-错误代码
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/

bool GamSaveRcd(U8 idx)
{
    U8	tbuf[20];
    gam_FILE	*fp;
    
    ResLoadToMem(IFACE_STRID,dWriting,tbuf);
    GamMsgBox(tbuf,0);
    ResLoadToMem(IFACE_STRID,dSaveFNam,tbuf);
    
    /* 存储第一个文件 */
    tbuf[5] = (idx << 1) + 0x30;		/* tbuf = "sango?.sav" */
    fp = sav_fopen(tbuf,'w');
    if(NULL == fp)
    {
        ResLoadToMem(IFACE_STRID,dErrInf,tbuf);
        GamMsgBox(tbuf,2);
        return false;
    }
    
    U8 verFlag = 0x82;
    gam_fwrite((U8 *)&verFlag,1,1,fp);
    gam_fwrite((U8 *)&g_PIdx,1,1,fp);
    gam_fwrite((U8 *)&g_PlayerKing,1,1,fp);
    gam_fwrite((U8 *)&g_YearDate,2,1,fp);
    gam_fwrite((U8 *)&g_LookEnemy,1,1,fp);
    gam_fwrite((U8 *)&g_LookMovie,1,1,fp);
    gam_fwrite((U8 *)&g_MoveSpeed,1,1,fp);
    gam_fwrite((U8 *)&g_MonthDate,1,1,fp);
    gam_fwrite((U8 *)&g_CityPos,sizeof(CitySetType),1,fp);
    gam_fwrite((U8 *)g_Persons,sizeof(PersonType),PERSON_MAX,fp);
    gam_fwrite((U8 *)g_PersonsQueue,1,PERSON_MAX,fp);
    gam_fwrite((U8 *)g_GoodsQueue,1,GOODS_MAX,fp);
    gam_fclose(fp);
    
    /* 存储第二个文件 */
    tbuf[5] = (idx << 1) + 0x31;		/* tbuf = "sango?.sav" */
    fp = sav_fopen(tbuf,'w');
    if(NULL == fp)
    {
        ResLoadToMem(IFACE_STRID,dErrInf,tbuf);
        GamMsgBox(tbuf,2);
        return false;
    }
    
    gam_fwrite((U8 *)FIGHTERS_IDX,1,FIGHT_ORDER_MAX,fp);
    gam_fwrite((U8 *)FIGHTERS,10,FIGHT_ORDER_MAX,fp);
    gam_fwrite((U8 *)ORDERQUEUE,sizeof(OrderType),ORDER_MAX,fp);
    gam_fwrite((U8 *)g_Cities,sizeof(CityType),CITY_MAX,fp);
    
    gam_fclose(fp);
    return true;	
}

void GamSetDataDir(const U8*dataDir_)
{
    dataDir = (U8*)strdup((const char*)dataDir_);
}


EngineConfig g_engineConfig = {
    0
};

void GamLoadEngineConfig(void) {
    ResItemGetN(IFACE_CONID, dEngineConfig, (U8*)&g_engineConfig, sizeof(g_engineConfig));
    FgtLoadConsts();   /* 初始化战斗参数 */
}

U16 add_16(U16 dst, int n)
{
    unsigned int rv = dst + n;
    U16 max = (U16)-1;
    if (rv > max) {
        return n > 0 ? max : 0;
    } else {
        return rv;
    }
}
