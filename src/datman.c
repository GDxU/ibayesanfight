/***********************************************************************
 *Copyright (c)2005 , 东莞步步高教育电子分公司
 *All rights reserved.
 **
 文件名称：	comOut.c
 *文件标识：	步步高电子词典的游戏引擎模块
 *摘要：		游戏数据管理模块
 **
 *移植性声明:
 *	1、符合标准：《游戏设计标准V1.0》
 *	2、兼容模式：本程序和界面无关，无兼容模式。
 *修改历史：
 *	版本    日期     作者     改动内容和原因
 *   ----------------------------------------------------
 *	1.0    2005.5.16  高国军     基本的功能完成
 ***********************************************************************/
#include "baye/stdsys.h"
#include "baye/comm.h"
#include "baye/enghead.h"

/*本体函数声明*/
/*------------------------------------------*/
U32	GetResStartAddr(U16 id);
U16	GetResItem(U32 addr,U8 idx,RCHEAD *reshead,RIDX *rIdx);
void	ExpDataWithKey(U8 *ptr,U8 key,U16 len);

/***********************************************************************
 * 说明:     获取指定资源项的数据长度
 * 输入参数: ResId-资源id	idx-目标在资源队列中的序号
 * 返回值  : 资源项的数据长度
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.18       完成基本功能
 ***********************************************************************/
FAR U16 ResGetItemLen(U16 ResId,U8 idx)
{
    U32	addr;
    RIDX	rIdx;
    RCHEAD	reshead;

    addr=GetResStartAddr(ResId);
    if(addr==0)
        return 0;
    return GetResItem(addr,idx,&reshead,&rIdx);
}

FAR U8 ResItemGet(U16 ResId,U8 idx,U8 *ptr)
{
    U16	plen;
    U32	addr;
    RIDX	rIdx;
    RCHEAD	reshead;

    addr=GetResStartAddr(ResId);
    if(addr==0)
        return 1;
    GetResItem(addr,idx,&reshead,&rIdx);
    addr+=rIdx.offset;
    plen = rIdx.rlen;
    if (plen == 0) {
        return 2;
    }
    gam_fseek(g_LibFp,addr,SEEK_SET);
    gam_fread(ptr,1,plen,g_LibFp);
    if(reshead.ResKey)
        ExpDataWithKey(ptr,reshead.ResKey,plen);
    return 0;
}

/***********************************************************************
 * 说明:     将指定的资源载入到内存中
 * 输入参数: ResId-资源id	idx-目标在资源队列中的序号
 *	   : ptr-内存指针
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.18       完成基本功能
 ***********************************************************************/
FAR U8 ResLoadToMem(U16 ResId,U8 idx,U8 *ptr)
{
    U16	plen;
    U32	addr;
    RIDX	rIdx;
    RCHEAD	reshead;

    addr=GetResStartAddr(ResId);
    if(addr==0)
        return 1;
    GetResItem(addr,idx,&reshead,&rIdx);
    addr+=rIdx.offset;
    plen = rIdx.rlen;
    if (plen == 0) {
        return 2;
    }
    gam_fseek(g_LibFp,addr,SEEK_SET);
    gam_fread(ptr,1,plen,g_LibFp);
    ptr[plen] = 0;
    if(reshead.ResKey)
        ExpDataWithKey(ptr,reshead.ResKey,plen);
    return 0;
}

/***********************************************************************
 * 说明:     将指定的资源载入到常量页面（没有常量页的系统用堆来模拟）
 * 输入参数: ResId-资源id		idx-目标在资源队列中的序号
 * 返回值  : 资源被载入后的指针(NULL为载入失败)
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.18       完成基本功能
 ***********************************************************************/
FAR U8 *ResLoadToCon(U16 ResId,U8 idx,U8 *cbnk)
{
    U8	*ptr;
    U16	tmp;
    U32	addr;
    RCHEAD	*reshead;
    if(!idx)
        return (U8 *) NULL;
    idx-=1;
    addr=GetResStartAddr(ResId);
    if(addr==0)
        return (U8 *) NULL;
    ptr=gam_fload(cbnk,addr,g_LibFp);
    reshead=(RCHEAD	*)ptr;
    if(reshead->ItmCnt <= idx || reshead->ResKey!=0) {
        return (U8 *) NULL;
    }
    if(reshead->ItmLen!=0)
    {
        ptr+=sizeof(RCHEAD);
        ptr+=idx*reshead->ItmLen;
    }
    else
    {
        if(reshead->ItmCnt==1)
            ptr+=sizeof(RCHEAD);
        else
        {
            tmp=idx;
            tmp<<=2;
            tmp+=sizeof(RCHEAD);
            ptr+=(U16) *((U16*)(ptr+tmp));
        }
    }
    return ptr;
}

/***********************************************************************
 * 说明:     将被加密的数据解密
 * 输入参数: id-资源id
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.18       完成基本功能
 ***********************************************************************/
void ExpDataWithKey(U8 *ptr,U8 key,U16 len)
{
    U16	i;
    for(i=0;i<len;i++)
        ptr[i]-=key;
}
/***********************************************************************
 * 说明:     获取指定的资源项
 * 输入参数: addr-资源起始地址	idx-目标在资源队列中的序号
 *	   : reshead-资源头	rIdx-资源项索引
 * 返回值  : 资源项数据长度
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.18       完成基本功能
 ***********************************************************************/
U16 GetResItem(U32 addr,U8 idx,RCHEAD *reshead,RIDX *rIdx)
{
    gam_fseek(g_LibFp,addr,SEEK_SET);
    gam_fread((U8*)reshead,sizeof(RCHEAD),1,g_LibFp);
    if ((idx - 1) >= reshead->ItmCnt) {
        rIdx->offset = 0;
        rIdx->rlen = 0;
        return 0;
    } else if(reshead->ItmLen!=0)
    {
        rIdx->offset = idx - 1;
        rIdx->offset *= reshead->ItmLen;
        rIdx->offset += sizeof(RCHEAD);
        rIdx->rlen=(U16)(reshead->ItmLen);
    }
    else
    {
        addr=idx-1;
        addr<<=2;
        gam_fseek(g_LibFp,addr,SEEK_CUR);
        gam_fread((U8 *)rIdx,sizeof(RIDX),1,g_LibFp);
    }
    return rIdx->rlen;
}
/***********************************************************************
 * 说明:     获取指定资源的数据起始地址
 * 输入参数: id-资源id
 * 返回值  : 资源地址
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.18       完成基本功能
 ***********************************************************************/
U32 GetResStartAddr(U16 id)
{
    U32	addr;
    
    if(id==0) return (U32)0;
    
    /* 获取资源的索引地址 addr=(id-1)*4 */
    addr=id-1;
    addr<<=2;
    
    /* 获取资源索引（实际就是资源存储的数据地址）*/
    gam_fseek(g_LibFp,addr,SEEK_SET);
    gam_fread((U8*)&addr,4,1,g_LibFp);
    
    if (addr == (U32)-1) {
        addr = 0;
    }
    return addr;
}
