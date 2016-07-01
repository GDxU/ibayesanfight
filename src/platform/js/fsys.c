//
//  fsys.c
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//

#include "baye/stdsys.h"
#include "baye/comm.h"
#include "baye/enghead.h"
#include <stdio.h>

#define ROM_PATH "/rom/"

struct gam_FILE {
    U8 (*fclose)(gam_FILE*fp);
    U8 (*fseek)(gam_FILE*fp, U32 offset, U8 fromwhere);
    U32 (*fread)(U8*buf, U8 size, U16 count, gam_FILE*fp);
    U32 (*fwrite)(U8 *buf, U8 size, U16 count, gam_FILE *fhandle);
    U32 (*ftell)(gam_FILE*fp);
};

static gam_FILE *rom_fopen(const U8 *fname,U8 pmode);

FAR gam_FILE *gam_fopen(const U8 *fname,U8 pmode)
{
    char rom_prefix[] = ROM_PATH;
    char prefix[] = ROM_PATH;
    gam_memcpy(prefix, fname, sizeof(prefix) - 1);

    if (gam_strcmp(rom_prefix, prefix) == 0) {
        return rom_fopen(fname, pmode);
    }
    return NULL;
}

FAR U8 gam_fclose(gam_FILE *fp)
{
    return fp->fclose(fp);
}

FAR U8 gam_fseek (gam_FILE *fp, U32 offset, U8 fromwhere)
{
    return fp->fseek(fp, offset, fromwhere);
}

FAR U32 gam_fread(U8 *buf, U8 size, U16 count, gam_FILE *fp)
{
    return fp->fread(buf, size, count, fp);
}

FAR U32 gam_fwrite(U8 *buf, U8 size, U16 count, gam_FILE *fp)
{
    return fp->fwrite(buf, size, count, fp);
}

FAR U32 gam_ftell(gam_FILE *fp)
{
    return fp->ftell(fp);
}

FAR U8 *gam_fload(U8 *bptr, U32 addr, gam_FILE *fhandle)
{
    return bptr + addr;
}
/***********************************************************************
 * 说明:     增强功能函数—修改文件名
 * 输入参数: fhandle-文件句柄	newname-新的文件名
 * 返回值  : 0-操作成功		!0-出错代码
***********************************************************************/
//FAR U8 gam_frename(gam_FILE *fhandle,U8 *newname)
//{
//	return 0;
//}
/***********************************************************************
 * 说明:     增强功能函数—文件删除
 * 输入参数: fhandle-文件句柄
 * 返回值  : 0-操作成功		!0-出错代码
***********************************************************************/
//FAR U8 gam_fdelete(gam_FILE *fhandle)
//{
//    return 0;
//}


FAR U8 *gam_freadall(gam_FILE *fhandle)
{
    U32 alloced = 1024*400;
    U8 buf[1024];
    U8 *rv = malloc(alloced);
    U32 offset = 0;
    U32 cnt = 0;
    
    do {
        cnt = gam_fread(buf, 1, 1024, fhandle);
        if (offset + cnt > alloced) {
            alloced *= 2;
            rv = realloc(rv, alloced);
        }
        memcpy(rv + offset, buf, cnt);
        offset += cnt;
    } while (cnt > 0);
        
    return rv;
}


///*******************************************

static U8 font[] =
#include "font.bin.c"
;
static U8 dat[] =
#include "dat.lib.c"
;


typedef struct {
    gam_FILE base;
    U32 cur;
    U32 length;
    U8* data;
} rom_FILE;


static U8 rom_fclose(gam_FILE*fp) {
    gam_free(fp);
    return 0;
}

static U8 rom_fseek(gam_FILE*fp, U32 offset, U8 fromwhere) {
    rom_FILE* _fp = (rom_FILE*)fp;

    if (fromwhere == SEEK_SET) {
        if (offset < _fp->length) {
            _fp->cur = offset;
            return 0;
        } else {
            return -1;
        }
    } else if(fromwhere == SEEK_CUR) {
        U32 loc = _fp->cur + offset;
        if (loc < _fp->length) {
            _fp->cur = loc;
            return 0;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)

static U32 rom_fread(U8*buf, U8 size, U16 count, gam_FILE*fp) {
    rom_FILE* _fp = (rom_FILE*)fp;

    U32 remain = _fp->length - _fp->cur;
    U32 l = MIN(size*count, remain);
    if (l > 0) {
        gam_memcpy(buf, _fp->data + _fp->cur, l);
        _fp->cur += l;
    }
    return l/size;
}

static U32 rom_fwrite(U8 *buf, U8 size, U16 count, gam_FILE *fhandle) {
    return 0;
}

static U32 rom_ftell(gam_FILE*fp) {
    rom_FILE* _fp = (rom_FILE*)fp;
    return _fp->length;
}

rom_FILE *rom_fnew() {
    rom_FILE* fp = gam_malloc(sizeof(rom_FILE));
    fp->base.fclose = rom_fclose;
    fp->base.fseek = rom_fseek;
    fp->base.fread = rom_fread;
    fp->base.fwrite = rom_fwrite;
    fp->base.ftell = rom_ftell;
    fp->cur = 0;
    fp->length = 0;
    fp->data = NULL;
    return fp;
}

static gam_FILE *rom_fopen(const U8 *fname,U8 pmode) {
    if (pmode != 'r') {
        return NULL;
    }

    if (0 == gam_strcmp(fname, "/rom/font.bin")) {
        rom_FILE* fp = rom_fnew();
        fp->data = font;
        fp->length = sizeof(font);
        return (gam_FILE*)fp;
    }
    else if (0 == gam_strcmp(fname, "/rom/dat.lib")) {
        rom_FILE* fp = rom_fnew();
        fp->data = dat;
        fp->length = sizeof(dat);
        return (gam_FILE*)fp;
    } else {
        return NULL;
    }
}
