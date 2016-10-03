/***********************************************************************
 *Copyright (c)2005 , 东莞步步高教育电子分公司
 *All rights reserved.
 **
 文件名称：	cityedit.c
 *文件标识：	步步高电子词典的游戏引擎模块
 *摘要：		封装引擎对系统显示程序调用的入口
 **
 *移植性声明:
 *	1、符合标准：《游戏设计标准V1.0》
 *	2、兼容模式：本程序和界面无关，无兼容模式。
 *	3、使用本封装程序的引擎要移植到其他环境中，系统的显示部分只需在此修改
 *修改历史：
 *	版本    日期     作者     改动内容和原因
 *   ----------------------------------------------------
 *	1.0    2005-6-3 14:45  陈泽伟     基本的功能完成
 ***********************************************************************/

#include "baye/stdsys.h"
#include "baye/comm.h"
#undef	CITYEDIT_C
#define	CITYEDIT_C
#include "baye/enghead.h"
#include "touch.h"

/*U8 GetCityOutPersons(U8 city,U8 *pqueue);
 U8 GetCityPersons(U8 city,U8 *pqueue);
 U8 ShowCityMap(CitySetType *pos);
 U16 NumOperate(U16 min,U16 max);

 FAR U8 MenuComm(MenuType *menu);*/

/******************************************************************************
 * 函数名:AddPerson
 * 说  明:在城市人才队列中添加人才
 *
 * 入口参数：city -- 城市编号，person -- 人才编号
 *
 * 出口参数：1 -- 成功，0 -- 失败
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-6-3 14:50	基本功能完成
 ******************************************************************************/
FAR U8 AddPerson(U8 city,U8 person)
{
    U8 i;
    U8 qnum;

    if (city >= CITY_MAX)
        return(0);

    if (person >= PERSON_MAX)
        return(0);

    qnum  = g_Cities[city].PersonQueue + g_Cities[city].Persons;

    for (i = PERSON_MAX - 1;i > qnum;i --)
    {
        g_PersonsQueue[i] = g_PersonsQueue[i - 1];
    }

    g_PersonsQueue[qnum] = person;
    g_Cities[city].Persons += 1;

    for (i = city + 1;i < CITY_MAX;i ++)
    {
        g_Cities[i].PersonQueue += 1;
    }

    return(1);
}

/******************************************************************************
 * 函数名:DelPerson
 * 说  明:在城市人才队列中删除人才
 *
 * 入口参数：city -- 城市编号，person -- 人才编号
 *
 * 出口参数：1 -- 成功，0 -- 失败
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-6-3 15:41	基本功能完成
 ******************************************************************************/
FAR U8 DelPerson(U8 city,U8 person)
{
    U8 i;
    U8 qnum;
    CityType *cptr;

    if (city >= CITY_MAX)
        return(0);

    if (person >= PERSON_MAX)
        return(0);

    cptr = &g_Cities[city];

    qnum  = cptr->PersonQueue + cptr->Persons;

    for (i = cptr->PersonQueue;i < qnum;i ++)
    {
        if (g_PersonsQueue[i] == person)
            break;
    }

    if (i >= qnum)
        return(0);

    for (;i < PERSON_MAX - 1;i ++)
    {
        g_PersonsQueue[i] = g_PersonsQueue[i + 1];
    }

    cptr->Persons -= 1;

    for (i = city + 1;i < CITY_MAX;i ++)
    {
        g_Cities[i].PersonQueue -= 1;
    }

    return(1);
}

/******************************************************************************
 * 函数名:AddGoods
 * 说  明:在城市道具队列中添加道具
 *
 * 入口参数：city -- 城市编号，goods -- 道具编号
 *
 * 出口参数：1 -- 成功，0 -- 失败
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-6-3 14:50	基本功能完成
 ******************************************************************************/
FAR U8 AddGoods(U8 city,U8 goods)
{
    U8 i;
    U8 qnum;

    if (city >= CITY_MAX)
        return(0);

    if (goods >= GOODS_MAX)
        return(0);

    qnum  = g_Cities[city].ToolQueue + g_Cities[city].Tools;

    for (i = GOODS_MAX - 1;i > qnum;i --)
    {
        g_GoodsQueue[i] = g_GoodsQueue[i - 1];
    }

    g_GoodsQueue[qnum] = goods;
    g_Cities[city].Tools += 1;

    for (i = city + 1;i < CITY_MAX;i ++)
    {
        g_Cities[i].ToolQueue += 1;
    }

    return(qnum + 1);
}

/******************************************************************************
 * 函数名:DelGoods
 * 说  明:在城市道具队列中删除道具
 *
 * 入口参数：city -- 城市编号，goods -- 道具编号
 *
 * 出口参数：1 -- 成功，0 -- 失败
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-6-3 15:41	基本功能完成
 ******************************************************************************/
FAR U8 DelGoods(U8 city,U8 goods)
{
    U8 i;
    U8 qnum;
    CityType *cptr;


    if (city >= CITY_MAX)
        return(0);

    if (goods >= GOODS_MAX)
        return(0);

    cptr = &g_Cities[city];

    qnum  = cptr->ToolQueue + cptr->Tools;

    for (i = cptr->ToolQueue;i < qnum;i ++)
    {
        if ((g_GoodsQueue[i] & 0x7f) == goods)
            break;
    }

    if (i >= qnum)
        return(0);

    for (;i < GOODS_MAX - 1;i ++)
    {
        g_GoodsQueue[i] = g_GoodsQueue[i + 1];
    }

    cptr->Tools -= 1;

    for (i = city + 1;i < CITY_MAX;i ++)
    {
        g_Cities[i].ToolQueue -= 1;
    }

    return(1);
}

/******************************************************************************
 * 函数名:ClearOrderQueue
 * 说  明:清除命令队列
 *
 * 入口参数：无
 *
 * 出口参数：1 -- 成功，0 -- 失败
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005/5/18 11:26AM	基本功能完成
 ******************************************************************************/
U8 ClearOrderQueue(void)
{
    /*OrderQueueType *orderdel;
     while (1)
     {
     if (NULL == g_OrderHead)
     break;

     orderdel = g_OrderHead;
     g_OrderHead = g_OrderHead->nOrder;
     if (!gam_free((U8 *) orderdel))
     return(0);
     }
     g_OrderEnd = (OrderQueueType *) NULL;
     return(1);*/
    return 0;
}


/******************************************************************************
 * 函数名:SearchRoad
 * 说  明:两城市之间路径搜索
 *
 * 入口参数：sc -- 出发城市编号，ob -- 目的城市编号
 *
 * 出口参数：0xff -- 有障碍无法通过 ， 其他值 -- 距离
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-6-7 9:38	基本功能完成
 ******************************************************************************/
FAR U8 SearchRoad(U8 sc,U8 xs,U8 ys,U8 ob,U8 xo,U8 yo)
{
    /*U8 nstr[10];
     U8 cbelong;
     U8 *clnk,*cdis;
     U8 citycount;
     U8 *dircount,*city,*diss;
     U8 i,c,d,scnt;
     U8 *inf;
     U16 clnkcount;

     dircount = gam_malloc(CITY_MAX * 3 + 4);
     if (NULL == dircount)
     return(0xff);
     city = dircount + CITY_MAX;
     cbelong = g_Cities[sc].Belong;
     if (xs > xo)
     {
     c = ob;
     ob = sc;
     sc = c;
     }

     citycount = 0;
     city[0] = sc;
     dircount[0] = 0;

     clnk = ResLoadToCon(CITY_LINKR,1,g_CBnkPtr);
     cdis = clnk + 8;
     scnt = 0;

     while (1)
     {
     scnt += 1;
     if (CITY_MAX < scnt)
     {
     citycount = 0;
     dircount[0] += 1;
     scnt = 0;
     }

     if (8 <= dircount[citycount])
     {
     if (!citycount)
     {
     citycount = 0xff;
     break;
     }

     citycount -= 1;
     if (!citycount)
     {
     scnt = 0;
     }
     dircount[citycount] += 1;
     continue;
     }

     clnkcount = city[citycount];
     clnkcount *= 16;
     clnkcount += dircount[citycount];
     if (clnk[clnkcount])
     {
     c = clnk[clnkcount] - 1;

     if (c == ob)
     {
     break;
     }
     if ((g_Cities[c].Belong == cbelong) || !(g_Cities[c].Belong))
     {
     for (i = 0;i <= citycount;i ++)
     {
					if (c == city[i])
     break;
     }

     if (i > citycount)
     {
					citycount += 1;
					city[citycount] = c;
					dircount[citycount] = 0;
     }
     else
     {
					dircount[citycount] += 1;
					continue;
     }
     }
     else
     {
     dircount[citycount] += 1;
     continue;
     }
     }
     else
     {
     dircount[citycount] += 1;
     }

     }


     if (0xff == citycount)
     {
     if (!gam_free(dircount))
     return(0xff);
     return(0xff);
     }*/

    U8 *cq;
    U8 ccount0,ccount1;
    U8 i,j,d;

    cq = SHARE_MEM + 2000;
    ccount0 = GetRoundSelfCity(sc,cq);
    if (!ccount0)
        return(0xff);

    ccount1 = ccount0;
    while (1)
    {
        for (i = 0;i < ccount0;i ++)
        {
            ccount1 += GetRoundSelfCity(cq[i],&cq[ccount1]);
        }
        for (i = 0;i < ccount1;i ++)
        {
            for (j = i + 1;j < ccount1;)
            {
                if (cq[i] == cq[j])
                {
                    ccount1 -= 1;
                    cq[j] = cq[ccount1];
                    continue;
                }
                j += 1;
            }
        }
        if (ccount1 == ccount0)
            break;

        ccount0 = ccount1;
    }
    for (i = 0;i < ccount0;i ++)
    {
        if (cq[i] == ob)
        {
            if (yo > ys)
                d = yo - ys;
            else
                d = ys - yo;

            if (xo > xs)
                d = d + xo - xs;
            else
                d = d + xs - xo;

            return(d);
        }
    }
    return(0xff);
    /*U8 *clnk;
     U8 i,d;
     U16 clnkcount;


     clnk = ResLoadToCon(CITY_LINKR,1,g_CBnkPtr);
     clnkcount = sc;
     clnkcount *= 16;
     clnk = &clnk[clnkcount];

     for (i = 0;i < 8;i ++)
     {
     if (clnk[i] == ob + 1)
     break;
     }

     if (i >= 8)
     return(0xff);

     if (yo > ys)
     d = yo - ys;
     else
     d = ys - yo;

     if (xo > xs)
     d = d + xo - xs;
     else
     d = d + xs - xo;*/

    /*if (!gam_free(dircount))
     return(0xff);*/

    /*return(d);*/
}


/******************************************************************************
 * 函数名:AttackCityRoad
 * 说  明:相临两城市之间路径搜索
 *
 * 入口参数：sc -- 出发城市编号，ob -- 目的城市编号
 *
 * 出口参数：0xff -- 有障碍无法通过 ， 其他值 -- 距离
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-6-7 9:38	基本功能完成
 ******************************************************************************/
FAR U8 AttackCityRoad(U8 sc,U8 xs,U8 ys,U8 ob,U8 xo,U8 yo)
{
    U8 *clnk;
    U8 i,d;
    U16 clnkcount;

    clnk = ResLoadToCon(CITY_LINKR,1,g_CBnkPtr);
    clnkcount = sc;
    clnkcount *= 16;
    clnk += clnkcount;

    for (i = 0;i < 8;i ++)
    {
        if (clnk[i] == ob + 1)
            break;
    }

    if (i >= 8)
        return(0xff);

    if (yo > ys)
        d = yo - ys;
    else
        d = ys - yo;

    if (xo > xs)
        d = d + xo - xs;
    else
        d = d + xs - xo;

    return(d);
}

/******************************************************************************
 * 函数名:GetRoundSelfCity
 * 说  明:取得城市周围相临己方城池
 *
 * 入口参数：city -- 指定城池，cqueue -- 周围城池队列指针
 *
 * 出口参数：城池个数
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-8-20 10:15	基本功能完成
 ******************************************************************************/
FAR U8 GetRoundSelfCity(U8 city,U8 *cqueue)
{
    U8 *inf;	/*inf -- 城市连接信息*/
    U8 i;
    U8 count;
    U8 cp,cb;
    U16 clnkcount;

    inf = ResLoadToCon(CITY_LINKR,1,g_CBnkPtr);
    clnkcount = city;
    clnkcount *= 16;
    inf += clnkcount;
    count = 0;
    cb = g_Cities[city].Belong;
    for (i = 0;i < 8;i ++)
    {
        if (inf[i])
        {
            cp = g_Cities[inf[i] - 1].Belong;
            if (cp == cb)
            {
                cqueue[count] = inf[i] - 1;
                count += 1;
            }
        }
    }
    return(count);
}

/******************************************************************************
 * 函数名:GetRoundEnemyCity
 * 说  明:取得城市周围相临敌人城池
 *
 * 入口参数：city -- 指定城池，cqueue -- 周围城池队列指针
 *
 * 出口参数：城池个数
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-7-27 10:57	基本功能完成
 ******************************************************************************/
FAR U8 GetRoundEnemyCity(U8 city,U8 *cqueue)
{
    U8 *inf;	/*inf -- 城市连接信息*/
    U8 i;
    U8 count;
    U8 cp,cb;
    U16 clnkcount;

    inf = ResLoadToCon(CITY_LINKR,1,g_CBnkPtr);
    clnkcount = city;
    clnkcount *= 16;
    inf += clnkcount;
    count = 0;
    cb = g_Cities[city].Belong;
    for (i = 0;i < 8;i ++)
    {
        if (inf[i])
        {
            cp = g_Cities[inf[i] - 1].Belong;
            if (cp && (cp != cb))
            {
                cqueue[count] = inf[i] - 1;
                count += 1;
            }
        }
    }
    return(count);
}

/******************************************************************************
 * 函数名:GetKingCitys
 * 说  明:获得君主拥有城池
 *
 * 入口参数：king -- 指定君主编号，cqueue -- 城池队列指针
 *
 * 出口参数：城池个数
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-7-25 9:48	基本功能完成
 ******************************************************************************/
FAR U8 GetKingCitys(U8 king,U8 *cqueue)
{
    U8 c,count;

    count = 0;
    for (c = 0;c < CITY_MAX;c ++)
    {
        if (g_Cities[c].Belong == (king + 1))
        {
            cqueue[count] = c;
            count ++;
        }
    }
    return(count);
}

/******************************************************************************
 * 函数名:GetPersonCity
 * 说  明:获得武将所在城市编号
 *
 * 入口参数：指定武将
 *
 * 出口参数：0xff -- 所有城市都无此武将，其他 -- 武将所在城市编号
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-7-23 11:06	基本功能完成
 ******************************************************************************/
FAR U8 GetPersonCity(U8 person)
{
    U8 c,i,j;

    for (c = 0;c < CITY_MAX;c ++)
    {
        j = g_Cities[c].PersonQueue;
        for (i = 0;i < g_Cities[c].Persons;i ++,j ++)
        {
            if (g_PersonsQueue[j] == person)
            {
                return(c);
            }
        }
    }
    return(0xff);
}

/******************************************************************************
 * 函数名:GetCityPersons
 * 说  明:取得城市中在任武将
 *
 * 入口参数：city -- 城市编号，pqueue -- 武将队列指针
 *
 * 出口参数：在任武将个数
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005/5/18 11:26AM	基本功能完成
 ******************************************************************************/
FAR U8 GetCityPersons(U8 city,U8 *pqueue)
{
    U8 i,count;
    U8 p;

    count = 0;
    for (i = 0;i < g_Cities[city].Persons;i ++)
    {
        p = g_PersonsQueue[g_Cities[city].PersonQueue + i];
        if (g_Persons[p].Belong == g_Cities[city].Belong)
        {
            pqueue[count] = p;
            count += 1;
        }
    }
    return(count);
}


/******************************************************************************
 * 函数名:GetCityOutPersons
 * 说  明:取得城市中在野武将
 *
 * 入口参数：city -- 城市编号，pqueue -- 武将队列指针
 *
 * 出口参数：在野武将个数
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-7-4 9:18	基本功能完成
 ******************************************************************************/
FAR U8 GetCityOutPersons(U8 city,U8 *pqueue)
{
    U8 i,count;
    U8 p;

    count = 0;
    for (i = 0;i < g_Cities[city].Persons;i ++)
    {
        p = g_PersonsQueue[g_Cities[city].PersonQueue + i];
        if (!(g_Persons[p].Belong))
        {
            pqueue[count] = p;
            count += 1;
        }
    }
    return(count);
}

/******************************************************************************
 * 函数名:GetCityCaptives
 * 说  明:取得城市中俘虏
 *
 * 入口参数：city -- 城市编号，pqueue -- 武将队列指针
 *
 * 出口参数：俘虏个数
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-7-4 9:24	基本功能完成
 ******************************************************************************/
FAR U8 GetCityCaptives(U8 city,U8 *pqueue)
{
    U8 i,count;
    U8 p;

    count = 0;
    for (i = 0;i < g_Cities[city].Persons;i ++)
    {
        p = g_PersonsQueue[g_Cities[city].PersonQueue + i];
        if (0xff == (g_Persons[p].Belong))
        {
            pqueue[count] = p;
            count += 1;
        }
    }
    return(count);
}

/******************************************************************************
 * 函数名:GetEnemyPersons
 * 说  明:取得敌方在任武将
 *
 * 入口参数：king -- 我方君主编号，pqueue -- 武将队列指针
 *
 * 出口参数：在任武将个数
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-7-4 9:24	基本功能完成
 ******************************************************************************/
FAR U8 GetEnemyPersons(U8 king,U8 *pqueue)
{
    U8 c,i,count;
    U8 b,p;

    count = 0;
    for (c = 0;c < CITY_MAX;c ++)
    {
        b = g_Cities[c].Belong;
        if ((b != (king + 1)) && b)
        {
            for (i = 0;i < g_Cities[c].Persons;i ++)
            {
                p = g_PersonsQueue[g_Cities[c].PersonQueue + i];
                if ((g_Persons[p].Belong == b) && ((p + 1) != b))
                {
                    pqueue[count] = p;
                    count += 1;
                }
            }
        }
    }
    return(count);
}

/******************************************************************************
 * 函数名:GetEnemySatraps
 * 说  明:取得敌方在任太守
 *
 * 入口参数：king -- 我方君主编号，squeue -- 太守队列指针
 *
 * 出口参数：在任太守个数
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-7-14 17:25	基本功能完成
 ******************************************************************************/
FAR U8 GetEnemySatraps(U8 king,U8 *squeue)
{
    U8 c,count;
    U8 b,s;

    count = 0;
    for (c = 0;c < CITY_MAX;c ++)
    {
        b = g_Cities[c].Belong;
        if (!(b))
            continue;

        s = g_Cities[c].SatrapId;
        if (!s) {
            continue;
        }
        if ((b != (king + 1)) && (s != b))
        {
            squeue[count] = s - 1;
            count += 1;
        }
    }
    return(count);
}

/******************************************************************************
 * 函数名:GetEnemyKing
 * 说  明:取得敌方君主
 *
 * 入口参数：king -- 我方君主编号，kqueue -- 君主队列指针
 *
 * 出口参数：敌方君主个数
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-7-13 9:57	基本功能完成
 ******************************************************************************/
FAR U8 GetEnemyKing(U8 king,U8 *kqueue)
{
    U8 c,i,count;
    U8 b;

    count = 0;
    for (c = 0;c < CITY_MAX;c ++)
    {
        b = g_Cities[c].Belong;
        if ((b) && (b != (king + 1)))
        {
            for (i = 0;i < count;i ++)
            {
                if (kqueue[i] == b - 1)
                    break;
            }
            if (i < count)
            {
                continue;
            }
            kqueue[count] = b - 1;
            count += 1;
        }
    }
    return(count);
}

/******************************************************************************
 * 函数名:GetEnemyPersons
 * 说  明:取得指定势力在任武将
 *
 * 入口参数：king -- 指定势力君主编号，pqueue -- 武将队列指针
 *
 * 出口参数：在任武将个数
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-7-4 9:24	基本功能完成
 ******************************************************************************/
FAR U8 GetKingPersons(U8 king,U8 *pqueue)
{
    U8 c,count;

    count = 0;
    for (c = 0;c < CITY_MAX;c ++)
    {
        if (g_Cities[c].Belong == (king + 1))
        {
            count += GetCityPersons(c,&pqueue[count]);
        }
    }
    return(count);
}

/******************************************************************************
 * 函数名:GetCitySet
 * 说  明:选择城市
 *
 * 入口参数：pos -- 初始显示选中城市结构
 *
 * 出口参数：0xff -- 退出，其他值 -- 选中城市编号
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-6-21 9:07	基本功能完成
 ******************************************************************************/
FAR U8 GetCitySet(CitySetType *pos)
{
    U8 showflag,scrollflag,tpicflag;
    U8 city = '\0';
    U8 *dptr;
    GMType Msg;
    Touch touch = {0};
    Rect mapRect = {
        .left = WK_SX,
        .top = WK_SY,
        .right = WK_SX + CITYMAP_TIL_W * SHOWMAP_WS,
        .bottom = WK_SY + CITYMAP_TIL_H * SHOWMAP_HS,
    };
    U8 xWhenTouchDown = 0;
    U8 yWhenTouchDown = 0;

    showflag = 1;
    scrollflag = 0;
    tpicflag = 0;
    gam_clrvscr(WK_SX,WK_SY,WK_EX,WK_EY,g_VisScr);
    while (1)
    {
        if (showflag && !tpicflag)
        {
            city = ShowCityMap(pos,scrollflag);
            showflag = 0;
            scrollflag = 0;
        }

        GamGetMsg(&Msg);
        if (VM_CHAR_FUN == Msg.type)
        {
            if (tpicflag)
            {
                tpicflag = 0;
                showflag = 1;
                continue;
            }
            switch (Msg.param)
            {
                case VK_UP:
                    if (pos->sety)
                    {
                        //scrollflag = 1;
                        pos->sety -= 1;
                        if (pos->sety < pos->y)
                        {
                            pos->y = pos->sety;
                            scrollflag = 0;
                        }
                        showflag = 1;
                    }
                    break;
                case VK_LEFT:
                    if (pos->setx)
                    {
                        //scrollflag = 2;
                        pos->setx -= 1;
                        if (pos->setx < pos->x)
                        {
                            pos->x = pos->setx;
                            scrollflag = 0;
                        }
                        showflag = 1;
                    }
                    break;
                case VK_DOWN:
                    if (pos->sety < CITYMAP_H - 1)
                    {
                        //scrollflag = 3;
                        pos->sety += 1;
                        if (pos->sety >= pos->y + SHOWMAP_HS)
                        {
                            pos->y = pos->sety - SHOWMAP_HS + 1;
                            scrollflag = 0;
                        }
                        showflag = 1;
                    }
                    break;
                case VK_RIGHT:
                    if (pos->setx < CITYMAP_W - 1)
                    {
                        //scrollflag = 4;
                        pos->setx += 1;
                        if (pos->setx >= pos->x + SHOWMAP_WS)
                        {
                            pos->x = pos->setx - SHOWMAP_WS + 1;
                            scrollflag = 0;
                        }
                        showflag = 1;
                    }
                    break;
                case VK_ENTER:
                    if (city)
                    {
                        return(city - 1);
                    }
                    break;
                case VK_EXIT:
                    return(0xff);
                    break;
                case VK_SEARCH:
                    gam_clrlcd(WK_SX,WK_SY,WK_EX,WK_EY);
                    dptr = ResLoadToCon(TACTIC_ICON,1,g_CBnkPtr);
                    GamPicShowExS(WK_SX + (WK_EX - WK_SX - 84) / 2,WK_SY + (WK_EY - WK_SY - 64) / 2,84,64,0,dptr);
                    tpicflag = 1;
                    break;
            }
        } else if (VM_TOUCH == Msg.type) {
            if (tpicflag)
            {
                if (VT_TOUCH_UP == Msg.param) {
                    // 退出地图
                    tpicflag = 0;
                    showflag = 1;
                }
                touchUpdate(&touch, Msg);
                continue;
            }
            switch (Msg.param) {
                case VT_TOUCH_DOWN:
                    xWhenTouchDown = pos->x;
                    yWhenTouchDown = pos->y;
                    break;
                case VT_TOUCH_UP:
                {
                    if (!touch.touched || touch.moved) break;

                    if (touchIsPointInRect(touch.currentX, touch.currentY, mapRect)) {
                        I16 px = touch.currentX - mapRect.left;
                        I16 py = touch.currentY - mapRect.top;
                        I16 row = py / CITYMAP_TIL_H;
                        I16 col = px / CITYMAP_TIL_W;

                        U8 setx = pos->x + col;
                        U8 sety = pos->y + row;

                        if (setx == pos->setx && sety == pos->sety) {
                            if (city) {
                                return city - 1;
                            }
                        } else {
                            pos->setx = setx;
                            pos->sety = sety;
                            showflag = 1;
                        }
                    }

                    break;
                }
                case VT_TOUCH_MOVE:
                {
                    I16 dx = Msg.param2.i16.p0 - touch.startX;
                    I16 dy = Msg.param2.i16.p1 - touch.startY;
                    I16 rows = dy / CITYMAP_TIL_H;
                    I16 cols = dx / CITYMAP_TIL_W;
                    
                    I16 x = xWhenTouchDown - cols;
                    I16 y = yWhenTouchDown - rows;

                    x = limitValueInRange(x, 0, CITYMAP_W - SHOWMAP_WS);
                    y = limitValueInRange(y, 0, CITYMAP_H - SHOWMAP_HS);

                    if (x != pos->x || y != pos->y) {
                        pos->x = x;
                        pos->y = y;
                        showflag = 1;
                    }

                    break;
                }
                default:
                    break;
            }
            touchUpdate(&touch, Msg);
        }
    }
    return(0xff);
}

/******************************************************************************
 * 函数名:ShowCityMap
 * 说  明:显示城市地图
 *
 * 入口参数：pos -- 城市地图显示选中位置结构，scrollflag -- 滚动标志
 *
 * 出口参数：选中城市
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-6-23 10:48	基本功能完成
 ******************************************************************************/

U8 ShowCityMap(CitySetType *pos,U8 scrollflag)
{
    U8 *str,*astr;
    U8 h,w,sw,sh,c;
    U8 *cdptr,*pdptr,*cicon;
    U16 count;

    /*取得citymap的值*/

    cdptr = ResLoadToCon(IFACE_CONID,C_MAP,g_CBnkPtr);
    count = CITYMAP_W;
    count *= pos->y;
    count += pos->x;
    for (h = 0;h < SHOWMAP_HS;h ++)
    {
        gam_memcpy(citymap[h],&cdptr[count],SHOWMAP_WS);
        count += CITYMAP_W;
    }

    sh = pos->sety - pos->y;
    sw = pos->setx - pos->x;

    pdptr = ResLoadToCon(CITYMAP_TILE,1,g_CBnkPtr);
    pdptr += sizeof(PictureHeadType);
    if (!scrollflag)
    {
        for (h = 0;h < SHOWMAP_HS;h ++)
        {
            count = (CITYMAP_TIL_W + 7) / 8 * CITYMAP_TIL_H * ((U16) (pos->y + h) * CITYMAP_W + pos->x);
            for (w = 0;w < SHOWMAP_WS;w ++)
            {
                /*显示地图块pdptr + count*/
                GamPicShowV(WK_SX + CITYMAP_TIL_W * w,WK_SY + CITYMAP_TIL_H * h,CITYMAP_TIL_W,CITYMAP_TIL_H,pdptr + count,g_VisScr);
                count += (CITYMAP_TIL_W + 7) / 8 * CITYMAP_TIL_H;
            }
        }

        for (h = 0;h < SHOWMAP_HS;h ++)
        {
            for (w = 0;w < SHOWMAP_WS;w ++)
            {
                if (citymap[h][w])
                {
                    /*显示城市图标*/
                    if (g_Cities[citymap[h][w] - 1].Belong == (g_PlayerKing + 1))
                    {
                        c = 8;
                    }
                    else if (g_Cities[citymap[h][w] - 1].Belong)
                    {
                        c = 7;
                    }
                    else
                    {
                        c = 0;
                    }
                    cicon = ResLoadToCon(CITY_ICON,1,g_CBnkPtr);
                    GamPicShowExV(WK_SX + CITYMAP_TIL_W * w + (CITYMAP_TIL_W - CITY_ICON_W) / 2,WK_SY + CITYMAP_TIL_H * h + (CITYMAP_TIL_H - CITY_ICON_H) / 2,CITY_ICON_W,CITY_ICON_H,c,cicon,g_VisScr);
                }
            }
        }
    }
    else
    {
        h = sh;
        w = sw;
        switch (scrollflag)
        {
            case 1:
                h = sh + 1;
                break;
            case 2:
                w = sw + 1;
                break;
            case 3:
                h = sh - 1;
                break;
            case 4:
                w = sw - 1;
                break;
        }

        count = (CITYMAP_TIL_W + 7) / 8 * CITYMAP_TIL_H * ((U16) (pos->y + h) * CITYMAP_W + pos->x + w);
        GamPicShowV(WK_SX + CITYMAP_TIL_W * w,WK_SY + CITYMAP_TIL_H * h,CITYMAP_TIL_W,CITYMAP_TIL_H,pdptr + count,g_VisScr);

        if (citymap[h][w])
        {
            if (g_Cities[citymap[h][w] - 1].Belong == (g_PlayerKing + 1))
            {
                c = 8;
            }
            else if (g_Cities[citymap[h][w] - 1].Belong)
            {
                c = 7;
            }
            else
            {
                c = 0;
            }
            cicon = ResLoadToCon(CITY_ICON,1,g_CBnkPtr);
            GamPicShowExV(WK_SX + CITYMAP_TIL_W * w + (CITYMAP_TIL_W - CITY_ICON_W) / 2,WK_SY + CITYMAP_TIL_H * h + (CITYMAP_TIL_H - CITY_ICON_H) / 2,CITY_ICON_W,CITY_ICON_H,c,cicon,g_VisScr);
        }
    }

    if (pos->setx >= pos->x && pos->sety >= pos->y && pos->setx < pos->x + SHOWMAP_WS && pos->sety < pos->y + SHOWMAP_HS) {
        /*显示指针图标*/
        cicon = ResLoadToCon(CITY_POS_ICON,1,g_CBnkPtr);
        cicon += sizeof(PictureHeadType);
        GamMPicShowV(WK_SX + CITYMAP_TIL_W * sw + (CITYMAP_TIL_W - CITY_ICON_W) / 2,WK_SY + CITYMAP_TIL_H * sh + CITY_ICON_H,CITY_ICON_W,CITY_ICON_H,cicon,g_VisScr);
    }

    str = SHARE_MEM + 3000;
    astr = SHARE_MEM + 3400;
    gam_clrvscr(WK_SX + CITYMAP_TIL_W * SHOWMAP_WS,WK_SY,WK_EX,WK_EY,g_VisScr);
    cicon = ResLoadToCon(GEN_HEADPIC1 + g_PIdx,1,g_CBnkPtr);
    GamPicShowExV(WK_SX + CITYMAP_TIL_W * SHOWMAP_WS + ((WK_EX - (WK_SX + CITYMAP_TIL_W * SHOWMAP_WS) - 24) / 2),WK_SY + 4,24,24,g_PlayerKing,cicon,g_VisScr);
    cicon = ResLoadToCon(MAPFACE_ICON,1,g_CBnkPtr);
    GamPicShowExV(WK_SX + CITYMAP_TIL_W * SHOWMAP_WS + 2,WK_SY + 4 + 24 + (12 - 9) / 2 + 4,7,9,1,cicon,g_VisScr);
    c = GetKingCitys(g_PlayerKing,str);
    gam_itoa(c,str,10);
    GamStrShowV(WK_SX + CITYMAP_TIL_W * SHOWMAP_WS + 2 + 10,WK_SY + 4 + 24 + (12 - 9) / 2 + 4,str,g_VisScr);
    GamPicShowExV(WK_SX + CITYMAP_TIL_W * SHOWMAP_WS + 2,WK_SY + 4 + 24 + 12 + (12 - 9) + 4,7,9,0,cicon,g_VisScr);
    c = GetPersonsCount(g_PlayerKing);
    gam_itoa(c,str,10);
    GamStrShowV(WK_SX + CITYMAP_TIL_W * SHOWMAP_WS + 2 + 10,WK_SY + 4 + 24 + 12 + (12 - 9) / 2 + 4,str,g_VisScr);
    
    gam_itoa(g_YearDate,str,10);
    ResLoadToMem(STRING_CONST,DATE_TIME_STR2,astr);
    gam_strcat(str,astr);
    GamStrShowV(WK_SX + CITYMAP_TIL_W * SHOWMAP_WS + 1,WK_EY - HZ_HGT - ASC_HGT - ASC_HGT - 1,str,g_VisScr);
    gam_itoa(g_MonthDate,str,10);
    ResLoadToMem(STRING_CONST,DATE_TIME_STR3,astr);
    gam_strcat(str,astr);
    GamStrShowV(WK_SX + CITYMAP_TIL_W * SHOWMAP_WS + 1,WK_EY - HZ_HGT - ASC_HGT - 1,str,g_VisScr);
    if (citymap[sh][sw])
    {
        GetCityName(citymap[sh][sw] - 1,astr);
        GamStrShowV(WK_SX + CITYMAP_TIL_W * SHOWMAP_WS + 2,WK_EY - HZ_HGT - 1,astr,g_VisScr);
    }
    
    /*GamShowFrame(g_VisScr);
     gam_rect(WK_SX + CITYMAP_TIL_W * SHOWMAP_WS,WK_SY,WK_EX,WK_EY);*/
    ShowMapClear();
    
    return(citymap[sh][sw]);
}

/******************************************************************************
 * 函数名:使用地图界面作为背景
 * 说  明:
 *
 * 入口参数：无
 *
 * 出口参数：无
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005/5/18 11:26AM	基本功能完成
 ******************************************************************************/
FAR void ShowMapClear(void)
{
    GamShowFrame(g_VisScr);
    gam_rect(WK_SX + CITYMAP_TIL_W * SHOWMAP_WS,WK_SY,WK_EX,WK_EY);
}

/******************************************************************************
 * 函数名:GetFood
 * 说  明:食物操作
 *
 * 入口参数：min -- 最小值限制，max -- 最大值限制
 *
 * 出口参数：0xffff -- 退出，其他值 -- 操作值
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-6-23 11:43	基本功能完成
 ******************************************************************************/
FAR U16 GetFood(U16 min,U16 max)
{
    U8 str[20];
    
    gam_clrlcd((WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2,(WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2 + ASC_WID * 12,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2 + ASC_HGT * 3);
    gam_rect((WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2 - 1,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2 - 1,(WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2 + ASC_WID * 12 + 1,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2 + ASC_HGT * 3 + 1);
    ResLoadToMem(STRING_CONST,ATRR_STR60,str);
    GamStrShowS((WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2,str);
    return(NumOperate(min,max));
}

/******************************************************************************
 * 函数名:GetMoney
 * 说  明:金钱操作
 *
 * 入口参数：min -- 最小值限制，max -- 最大值限制
 *
 * 出口参数：0xffff -- 退出，其他值 -- 操作值
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005-6-23 11:44	基本功能完成
 ******************************************************************************/
FAR U16 GetMoney(U16 min,U16 max)
{
    U8 str[20];
    
    gam_clrlcd((WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2,(WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2 + ASC_WID * 12,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2 + ASC_HGT * 3);
    gam_rect((WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2 - 1,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2 - 1,(WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2 + ASC_WID * 12 + 1,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2 + ASC_HGT * 3 + 1);
    ResLoadToMem(STRING_CONST,ATRR_STR61,str);
    GamStrShowS((WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2,str);
    return(NumOperate(min,max));
}

/******************************************************************************
 * 函数名:GetArmy
 * 说  明:军队操作
 *
 * 入口参数：min -- 最小值限制，max -- 最大值限制
 *
 * 出口参数：0xffff -- 退出，其他值 -- 操作值
 *
 * 修改历史:
 *		姓名		日期			说明
 *		----		----			-----------
 *		陈泽伟		2005/5/18 11:26AM	基本功能完成
 ******************************************************************************/
FAR U16 GetArmy(U16 min,U16 max)
{
    U8 str[20];
    
    gam_clrlcd((WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2,(WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2 + ASC_WID * 12,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2 + ASC_HGT * 3);
    gam_rect((WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2 - 1,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2 - 1,(WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2 + ASC_WID * 12 + 1,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2 + ASC_HGT * 3 + 1);
    ResLoadToMem(STRING_CONST,ATRR_STR62,str);
    GamStrShowS((WK_SX + WK_EX - WK_SX  - ASC_WID * 12) / 2,(WK_SY + WK_EY - WK_SY - ASC_HGT * 3) / 2,str);
    return(NumOperate(min,max));
}
