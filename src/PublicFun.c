/***********************************************************************
 *Copyright (c)2005 , 东莞步步高教育电子分公司
 *All rights reserved.
 **
 文件名称：	PublicFun.c
 *文件标识：	步步高电子词典的游戏引擎模块
 *摘要：		游戏引擎公共模块
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
#undef	PublicFun
#define	PublicFun
#include "baye/enghead.h"
#include "touch.h"
#include "baye/script.h"
#define		IN_FILE	1	/* 当前文件位置 */

/*本体函数声明*/
/*------------------------------------------*/
U8 *PlcItemShowS(U8 sx,U8 sy,U8 ex,U8 ey,U8 *buf);
U8 *strlchr(U8 *buf,U8 len,U8 ch);

/***********************************************************************
 * 说明:     播放指定的动画
 * 输入参数: speid 指定播放的对象,keyflag (00000010|00000001|00000100)背景处理|响应键盘|反转播放
 *           startfrm 起始帧,endfrm 结束帧, x,y 播放坐标
 * 返回值  : 0xff -- 非按键退出 ；其他值 -- 按键退出，按键的扫描码
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             陈泽伟          2005-7-8 18:59       完成基本功能
 ***********************************************************************/
FAR U8 PlcMovie(U16 speid, U16 index, U8 startfrm,U8 endfrm,U8 keyflag,U8 x,U8 y)
{
    U8 **dat,*srsptr;
    U8	 count;			/*桢数*/
    U8	 picmax;		/*最大图片序号*/
    U16 wid,high,picdatlen,maxdatlen,mode,lenspe;
    U8 i,clsflag,showflag;
    U8 mcount;
    U8 keynum;
    U8 x1,y1;
    U8 ymount,*spem,*spec;
    SPEUNIT  *spe;

    lenspe = 0;
    clsflag = 1;
    showflag = 1;
    maxdatlen = 0;


    srsptr = ResLoadToCon(speid,index+1,g_CBnkPtr);
    if (NULL == srsptr)
    {
        printf("spe %d %d not found\n", speid, index);
        gamTraceP(speid);
        return(0xff);
    }
    endfrm = min(((SPERES*)srsptr)->endfrm, endfrm);

    count  = *(srsptr+2);
    picmax = *(srsptr+3);
    srsptr+=6;
    dat = (U8 **) SHARE_MEM;
    spem = (U8 *) (SHARE_MEM + 2000);
    spec = (U8 *) (SHARE_MEM + 2000 + 1000);
    spe = (SPEUNIT *) srsptr;

    lenspe = count;
    srsptr += sizeof(SPEUNIT) * lenspe;
    for (i = 0;i <= endfrm - startfrm;i ++)
    {
        spem[i] = spe[i + startfrm].ndelay;
        spec[i] = spe[i + startfrm].cdelay;
    }
    for(i=0;i<picmax;i++)
    {
        wid = *(srsptr);
        high = *(srsptr + 2);
        mode = *(srsptr + 5);

        picdatlen=wid/8;
        if(wid%8)
            picdatlen++;
        picdatlen*=high;
        picdatlen*=(mode+1);
        picdatlen+=sizeof(PictureHeadType);
        dat[i] = srsptr;
        srsptr += picdatlen;
    }
    mcount = 0;
    ymount = mcount;
    while (1)
    {
        for (i = 0;i <= mcount;i ++)
        {
            if (spec[i] == 1)
            {
                if ((keyflag & 0x02) != 0x02)
                {
                    wid = *(dat[spe[i + startfrm].picIdx]);
                    high = *(dat[spe[i + startfrm].picIdx] + 2);
                    x1 = x + spe[i + startfrm].x;
                    y1 = y + spe[i + startfrm].y;
                    if (y1 >= 0x80)
                    {
                        high = high - ((0xff ^ y1) + 1);
                        y1 = 0;
                    }
                    high = y1 + high <= 96 ? high : (96 - y1);

                    if (high < 0x80 && high + 1 > 1)
                        gam_clrvscr(x1,y1,x1+wid-1,y1+high-1,g_VisScr);
                }
                clsflag = 1;
            }
            if (spec[i] + 1 != 1)
                spec[i] --;
        }
        if (clsflag == 1)
        {
            for (i = 0;i <= ymount;i ++)
            {
                if (spec[i] + 1 != 1)
                {
                    wid = *(dat[spe[i + startfrm].picIdx]);
                    high = *(dat[spe[i + startfrm].picIdx] + 2);
                    mode = *(dat[spe[i + startfrm].picIdx] + 5);
                    x1 = x + spe[i + startfrm].x;
                    y1 = y + spe[i + startfrm].y;
                    if(mode==1)
                        GamMPicShowV(x1,y1,wid,high,dat[spe[i + startfrm].picIdx] + sizeof(PictureHeadType),g_VisScr);
                    else
                        GamPicShowV(x1,y1,wid,high,dat[spe[i + startfrm].picIdx] + sizeof(PictureHeadType),g_VisScr);
                }
            }
        }
        if (showflag == 1)
        {
            for (i = ymount + 1;i <= mcount;i ++)
                if (spec[i] + 1 != 1)
                {
                    wid = *(dat[spe[i + startfrm].picIdx]);
                    high = *(dat[spe[i + startfrm].picIdx] + 2);
                    mode = *(dat[spe[i + startfrm].picIdx] + 5);
                    x1 = x + spe[i + startfrm].x;
                    y1 = y + spe[i + startfrm].y;
                    if(mode==1)
                        GamMPicShowV(x1,y1,wid,high,dat[spe[i + startfrm].picIdx] + sizeof(PictureHeadType),g_VisScr);
                    else
                        GamPicShowV(x1,y1,wid,high,(dat[spe[i + startfrm].picIdx] + sizeof(PictureHeadType)),g_VisScr);
                }
            ymount = mcount;
        }
        if (showflag == 1 || clsflag == 1)
        {
            GamShowFrame(g_VisScr);
            showflag = 0;
            clsflag = 0;
        }
        else
        {
            U8 key = GamDelay(1, keyflag);				/* 延时1%秒 */
            if (key && (keyflag & 0x01)) {
                return key;
            }
        }
        if (spem[mcount] >= 1)
            spem[mcount] --;
        while ((spem[mcount] <= 1) && (mcount + startfrm < endfrm))
        {
            mcount ++;
            showflag = 1;
        }
        if (mcount + startfrm >= endfrm)
        {
            for (i = 0;i <= mcount;i ++)
            {
                if(spec[i] > 1)
                    break;
            }
            if (i > mcount)
                break;
        }
    }
    return(0xff);
}
/***********************************************************************
 * 说明:     简单的菜单控件
 * 输入参数: pRect-菜单显示范围	pIdx-初始选中项	buf-菜单内容缓冲
 * 返回值  : 0xFF-跳出		其他-菜单选项
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR U8 PlcSplMenu(RECT *pRect,U8 pIdx,U8 *buf)
{
    U8	sy,ty,tflag,cflag;
    U8	pLen;	/* 每个菜单项字符长度 */
    U8	pItm;	/* 菜单项总数 */
    U8	pSIdx;	/* 显示起始菜单项 */
    U8	pICnt;	/* 菜单显示区能显示的项数 */
    U16	poff;	/* 数据偏移 */
    float	tcot;
    GMType	pMsg;	/* 消息 */
    Touch touch = {0};
    U8 touchStartIndex = 0;
    U8 itemHeight = ASC_HGT;

    /* 初始化显示范围 */
    c_ReFlag = false;
    c_Sx = pRect->sx;
    c_Ex = pRect->ex;
    c_Sy = pRect->sy;
    c_Ey = pRect->ey;
    /* 计算参数 */
    pLen = (c_Ex - c_Sx) / ASC_WID;
    pICnt = (c_Ey - c_Sy) / itemHeight;
    pItm = gam_strlen(buf) / pLen;
    pSIdx = 0;
    if(pICnt < pItm)
        pSIdx = pIdx;

    Rect menuRect = {c_Sx - 3,c_Sy - 3,c_Ex + 2,c_Ey + 2};
    /* 初始化界面 */
    gam_clrlcd(c_Sx - 3,c_Sy - 3,c_Ex + 2,c_Ey + 2);
    gam_rect(menuRect.left, menuRect.top, menuRect.right, menuRect.bottom);
    if(pItm > pICnt)
    {
        gam_clrlcd(c_Ex + 2,c_Sy - 3,c_Ex + 6,c_Ey + 2);
        gam_rect(c_Ex + 2,c_Sy - 3,c_Ex + 6,c_Ey + 2);
        gam_rect(c_Ex + 2,c_Sy - 1,c_Ex + 6,c_Ey);
        if(pSIdx + pICnt > pItm)
            pSIdx = pItm - pICnt;
    }
    poff = pSIdx;
    poff *= pLen;
    GamStrShowS(c_Sx,c_Sy,buf + poff);
    /* 初始化光标 */
    sy = c_Sy + (pIdx - pSIdx) * itemHeight;
    gam_revlcd(c_Sx,sy,c_Ex,sy + itemHeight);
    ty = c_Sy;
    cflag = true;
    while(1)
    {
        if(pItm > pICnt)
        {
            if(cflag)
            {	/* 驱动滚动条 */
                gam_rectc(c_Ex + 3,ty,c_Ex + 5,ty + 2);
                gam_putpixel(c_Ex + 4,ty + 1,COLOR_WHITE);
                tcot = pIdx;
                tcot /= pItm - 1;
                ty = tcot * (c_Ey - c_Sy - 3) + c_Sy;
                gam_rect(c_Ex + 3,ty,c_Ex + 5,ty + 2);
                cflag = false;
            }
            gam_revlcd(c_Ex + 3,ty,c_Ex + 5,ty + 2);
        }

        tflag = false;
        GamGetMsg(&pMsg);

        if (VM_TOUCH == pMsg.type)
        {
            touchUpdate(&touch, pMsg);
            switch (pMsg.param) {
                case VT_TOUCH_DOWN:
                {
                    touchStartIndex = pSIdx;
                    I16 index = touchListViewItemIndexAtPoint(touch.currentX, touch.currentY, menuRect, 3, 3, pSIdx, pItm, itemHeight);
                    if (index >= 0 && index != pIdx) {
                        pIdx = index;
                        tflag = 1;
                        cflag = 1;
                        break;
                    }
                    break;
                }
                case VT_TOUCH_UP:
                {
                    if (touch.completed && !touch.moved) {
                        I16 index = touchListViewItemIndexAtPoint(touch.currentX, touch.currentY, menuRect, 3, 3, pSIdx, pItm, itemHeight);
                        if (index < 0)
                        {
                            pIdx = MNU_EXIT;
                        }
                        c_ReFlag = true;
                        c_Sx = WK_SX;
                        c_Sy = WK_SY;
                        c_Ex = WK_EX;
                        c_Ey = WK_EY;
                        return pIdx;
                    }
                    break;
                }
                case VT_TOUCH_MOVE:
                {
                    I16 dy = touch.currentY - touch.startY;
                    I16 dItems = dy / itemHeight;
                    I16 startIndex = touchStartIndex - dItems;
                    startIndex = limitValueInRange(startIndex, 0, pItm-pICnt);
                    if (startIndex != pSIdx) {
                        pSIdx = startIndex;
                        poff = pSIdx*pLen;
                        tflag = true;
                    }
                    break;
                }
                default:
                    break;
            }
            goto UPDATE_UI;
        }

        if(VM_CHAR_FUN != pMsg.type)
            continue;

        switch(pMsg.param)
        {
            case VK_UP:
                if(!pIdx)
                {
                    pIdx = pItm - 1;
                    pSIdx = pItm - pICnt;
                    poff = pSIdx * pLen;
                    tflag = true;
                    cflag = true;
                    break;
                }
                if(pIdx)
                {
                    pIdx -= 1;
                    cflag = true;
                }
                if(pIdx < pSIdx)
                {
                    pSIdx -= 1;
                    poff -= pLen;
                    tflag = true;
                }
                break;
            case VK_DOWN:
                if(pIdx == pItm - 1)
                {
                    pIdx = 0;
                    pSIdx = 0;
                    poff = 0;
                    tflag = true;
                    cflag = true;
                    break;
                }
                if(pIdx < pItm - 1)
                {
                    pIdx += 1;
                    cflag = true;
                }
                if(pIdx - pSIdx >= pICnt)
                {
                    pSIdx += 1;
                    poff += pLen;
                    tflag = true;
                }
                break;
            case VK_EXIT:
                pIdx = MNU_EXIT;
            case VK_ENTER:
                c_ReFlag = true;
                c_Sx = WK_SX;
                c_Sy = WK_SY;
                c_Ex = WK_EX;
                c_Ey = WK_EY;
                return pIdx;
        }
UPDATE_UI:
        if(tflag || cflag) {
            gam_clrlcd(c_Sx, c_Sy, c_Ex, c_Ey);
            GamStrShowS(c_Sx,c_Sy,buf + poff);
            if (pIdx >= pSIdx && pIdx < pSIdx + pICnt) {
                sy = c_Sy + (pIdx - pSIdx) * ASC_HGT;
                gam_revlcd(c_Sx,sy,c_Ex,sy + ASC_HGT);
            }
        }
    }
}
/***********************************************************************
 * 说明:     居中显示指定字符串
 * 输入参数: x,y-指定位置		buf-字符串
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR void PlcMidShowStr(U8 x,U8 y,U8 *buf)
{
    U8	pLen;

    pLen = gam_strlen(buf) * ASC_WID;
    pLen >>= 1;
    x -= pLen;
    GamStrShowS(x,y,buf);
}
/***********************************************************************
 * 说明:     显示图形边框的消息框(只能显示一行)
 * 输入参数: buf-显示的消息	delay-显示延时(秒)
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR void PlcGraMsgBox(U8 *buf,U8 delay,U8 line)
{
    U8	x,y,w,h;
    U8	*ptr;

    ptr = ResLoadToCon(MSGBOX_PIC,1,g_CBnkPtr);
    w = ptr[0];
    h = ptr[2];
    x = (WK_EX - WK_SX - w) >> 1;
    x += WK_SX;
    if(line != 0xFF)
        y = WK_SY + line * HZ_HGT;
    else
    {
        y = (WK_EY - WK_SY - h) >> 1;
        y += WK_SY;
    }
    GamPicShowS(x,y,w,h,ptr + sizeof(PictureHeadType));
    GamStrShowS(x + 10,y + 6,buf);
    GamDelay(delay * 100, 2);
}

U16 sqrt32(U32 a)
{
    U32 rem = 0;
    U32 root = 0;
    U32 divisor = 0;
    for(U8 i=0; i<16; i++){
        root <<= 1;
        rem = ((rem << 2) + (a >> 30));
        a <<= 2;
        divisor = (root<<1) + 1;
        if(divisor <= rem){
            rem -= divisor;
            root++;
        }
    }
    return (U16)(root);
}

/***********************************************************************
 * 说明:     获取一个255以内的平方根(整数)
 * 输入参数: num-返回值的平方
 * 返回值  : 平方根
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR U8 PlcExtract(U16 num)
{
    return sqrt32(num);
}
/***********************************************************************
 * 说明:     显示数字到虚拟屏幕
 * 输入参数: x,y-显示坐标	num-显示数字	dig-显示位数
 * 返回值  : 0-操作成功		!0-错误代码
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
const U32 FgtDigMask[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
FAR void PlcNumShow(U8 x,U8 y,U32 num,U8 dig,U8 *vs)
{
    U8	slen,*ptr,buf[12],numb[12];
    U32	tnum;

    ptr = buf;
    gam_memset(buf,0x30,12);
    tnum = num % FgtDigMask[dig];
    gam_ltoa(tnum,numb,10);
    slen = gam_strlen(numb);
    if(slen <= dig && num >= FgtDigMask[dig])
        ptr += dig - slen;

    gam_memcpy(ptr,numb,slen + 1);
    if(vs == NULL)
        GamStrShowS(x,y,buf);
    else
        GamStrShowV(x,y,buf,vs);
}
/***********************************************************************
 * 说明:     显示指定的资源图片到虚拟屏幕
 * 输入参数: id,idx-指定要显示的对象	x,y-显示的坐标	flag-true屏幕 false内存
 * 返回值  : 0-操作成功		!0-错误代码
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR void PlcRPicShow(U16 id,U8 idx,U8 x,U8 y,U8 flag) {
    PlcRPicShowEx(id, 0, idx, x, y, flag);
}

FAR void PlcRPicShowEx(U16 id, U8 item, U8 idx,U8 x,U8 y,U8 flag)
{
    U8	*pic;
    U8	wid,high,mode;
    U16	off;

    pic = ResLoadToCon(id,item+1,g_CBnkPtr);
    if(NULL == pic)
        return;
    if(idx > pic[4])
        return;
    wid = pic[0];
    high = pic[2];
    mode = pic[5] & 0x01;
    off = wid >> 3;
    if(wid & 0x07)
        off += 1;
    off *= high;
    off <<= mode;
    off *= idx - 1;
    pic += off;
    pic += PICHEAD_LEN;
    if(!flag)
    {
        if(mode)
            GamMPicShowV(x,y,wid,high,pic,g_VisScr);
        else
            GamPicShowV(x,y,wid,high,pic,g_VisScr);
    }
    else
    {
        if(mode)
            GamMPicShowS(x,y,wid,high,pic);
        else
            GamPicShowS(x,y,wid,high,pic);
    }
}
/***********************************************************************
 * 说明:     获取指定将领的兵力上限
 * 输入参数: 无
 * 返回值  : 0-操作成功		!0-错误代码
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR U16 PlcArmsMax(U8 id) {
    IF_HAS_HOOK("getMaxArms") {
        U32 maxArms = 0;
        BIND_U8EX("personIndex", &id);
        BIND_U32(&maxArms);
        if (CALL_HOOK() == 0) {
            HOOK_RETURN(maxArms);
        }
    }
    return PlcArmsMaxP(&g_Persons[id]);
}

FAR U16 PlcArmsMaxP(PersonType* p)
{
    U32	armys = 0;
    if (g_engineConfig.enableCustomRatio) {
        armys += p->Level * g_engineConfig.ratioOfArmsToLevel;
        armys += p->Age * g_engineConfig.ratioOfArmsToAge;
        armys += p->Force * g_engineConfig.ratioOfArmsToForce;
        armys += p->IQ * g_engineConfig.ratioOfArmsToIQ;
        if (armys > 0xfffe)
            armys = 0xfffe;
    } else {
        armys += p->Level * 100;
        armys += p->Force * 10;
        armys += p->IQ * 10;
    }
    return (U16)armys;
}
/***********************************************************************
 * 说明:     显示指定字符串到big内small外的区域中
 * 输入参数: big,small-指定区域	buf-字符串
 * 返回值  : 无
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
FAR void PlcStrShowS(RECT *big,RECT *small,U8 *buf)
{
    U8	*ptr,i,tmp;
    U8	sx[4],sy[4],ex[4],ey[4];
    U16	sLen;
    
    tmp = big->sx;
    sx[0] = tmp;
    sx[1] = tmp;
    sx[3] = tmp;
    sx[2] = small->ex;
    sy[0] = big->sy;
    tmp = small->sy;
    sy[1] = tmp;
    sy[2] = tmp;
    sy[3] = small->ey;
    tmp = big->ex;
    ex[0] = tmp;
    ex[2] = tmp;
    ex[3] = tmp;
    ex[1] = small->sx;
    ey[0] = small->sy;
    tmp = small->ey;
    ey[1] = tmp;
    ey[2] = tmp;
    ey[3] = big->ey;
    
    ptr = buf;
    sLen = gam_strlen(buf);
    for(i = 0;i < 4;i += 1)
    {
        ptr = PlcItemShowS(sx[i],sy[i],ex[i],ey[i],ptr);
        if(ptr >= buf + sLen)
            return;
    }
}
/***********************************************************************
 * 说明:     根据当前范围按照项截取显示指定的字符串
 * 输入参数: sx,sy,ex,ey-指定范围		buf-要显示的项字符串(项的分割符是'|')
 * 返回值  : 下次要显示时的数据指针
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
U8 *PlcItemShowS(U8 sx,U8 sy,U8 ex,U8 ey,U8 *buf)
{
    c_Sx = sx;
    c_Sy = sy;
    c_Ex = ex;
    c_Ey = ey;
    return buf + GamStrShowS(sx,sy,buf);
}
/***********************************************************************
 * 说明:     从len处向左查找字符串buf中给定的字符ch，并返回指针。
 * 输入参数: sx,sy,ex,ey-指定范围		buf-要显示的项字符串(项的分割符是'|')
 * 返回值  : !NULL-查找成功	NULL-查找失败
 * 修改历史:
 *               姓名            日期             说明
 *             ------          ----------      -------------
 *             高国军          2005.5.16       完成基本功能
 ***********************************************************************/
U8 *strlchr(U8 *buf,U8 len,U8 ch)
{
    U8	i;
    
    for(i = len;i-0 > 0;i -= 1)
    {
        if(buf[i] == ch)
            return (buf + i);
    }
    return ((U8 *)NULL);
}

U8 GamChoosePerson(U8* pqptr, U8 pcount, U8 selected)
{
    return ShowPersonControl(pqptr, pcount, selected, WK_SX + 4, WK_SY + 2, WK_EX - 4, WK_EY - 2);
}

U16 GamChoose(U16 x, U16 y, U16 w, U16 h, U16 pIdx, U8* buf)
{
    RECT r = {
        .sx = x,
        .sy = y,
        .ex = x + w,
        .ey = y + h,
    };
    return PlcSplMenu(&r, pIdx, buf);
}
