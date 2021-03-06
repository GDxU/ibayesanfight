//
//  exportjs.c
//  baye-ios
//
//  Created by loong on 16/10/29.
//
//

#include <stdio.h>

#include	"baye/comm.h"
#include	"baye/bind-objects.h"
#include	"baye/data-bind.h"
#include	"baye/script.h"
#include	"baye/fundef.h"
#include	"baye/enghead.h"
#include    "touch.h"

void gam_setcustomdata(U8*data);
U8* gam_getcustomdata();

EMSCRIPTEN_KEEPALIVE
void bayeSendKey(int key)
{
    MsgType msg;
    msg.type = VM_CHAR_FUN;
    msg.param = key;
    GuiPushMsg(&msg);
}

EMSCRIPTEN_KEEPALIVE
void bayeSendTouchEvent(int event, int x, int y)
{
    touchSendTouchEvent((U16)event, (I16)x, (I16)y);
}

EMSCRIPTEN_KEEPALIVE
void bayeSetLcdSize(int width, int height)
{
    g_screenWidth = width;
    g_screenHeight = height;
}

EMSCRIPTEN_KEEPALIVE
void bayeSetDebug(int debug)
{
    GamSetDebug(debug);
}

EMSCRIPTEN_KEEPALIVE
int bayeGetCurrentPeriod()
{
    return g_PIdx;
}

EMSCRIPTEN_KEEPALIVE
int bayeCityAddGoods(U8 cityIndex, U8 goodsIndex)
{
    return AddGoodsEx(cityIndex, goodsIndex, 1);
}

EMSCRIPTEN_KEEPALIVE
int bayeCityDelGoods(U8 cityIndex, U8 goodsIndex)
{
    return DelGoods(cityIndex, goodsIndex);
}

EMSCRIPTEN_KEEPALIVE
ValueType Value_get_type(Value*value) {
    return value->def->type;
}

EMSCRIPTEN_KEEPALIVE
ValueDef* Value_get_def(Value*value) {
    return value->def;
}

EMSCRIPTEN_KEEPALIVE
void* Value_get_addr(Value*value) {
    return (void*)value->offset;
}

EMSCRIPTEN_KEEPALIVE
U8 Value_get_u8_value(Value*value) {
    return *(U8*)value->offset;
}

EMSCRIPTEN_KEEPALIVE
void Value_set_u8_value(Value*value, U8 cvalue) {
    *(U8*)value->offset = cvalue;
}

EMSCRIPTEN_KEEPALIVE
U16 Value_get_u16_value(Value*value) {
    return *(U16*)value->offset;
}

EMSCRIPTEN_KEEPALIVE
void Value_set_u16_value(Value*value, U16 cvalue) {
    *(U16*)value->offset = cvalue;
}

EMSCRIPTEN_KEEPALIVE
U32 Value_get_u32_value(Value*value) {
    return *(U32*)value->offset;
}

EMSCRIPTEN_KEEPALIVE
void Value_set_u32_value(Value*value, U32 cvalue) {
    *(U32*)value->offset = cvalue;
}

EMSCRIPTEN_KEEPALIVE
U32 Object_get_field_count(Value*value) {
    return value->def->subdef.objDef->count;
}

EMSCRIPTEN_KEEPALIVE
Field* Object_get_field_by_index(Value*obj, U32 ind) {
    return &obj->def->subdef.objDef->fields[ind];
}

EMSCRIPTEN_KEEPALIVE
const char* Field_get_name(Field*field) {
    return field->name;
}

EMSCRIPTEN_KEEPALIVE
Value* Field_get_value(Field*field) {
    return &field->value;
}

EMSCRIPTEN_KEEPALIVE
ValueType Field_get_type(Field*field) {
    return field->value.def->type;
}

EMSCRIPTEN_KEEPALIVE
ValueType ValueDef_get_type(ValueDef*def) {
    return def->type;
}


EMSCRIPTEN_KEEPALIVE
U32 baye_get_u8_value(U8*value) {
    return *(U8*)value;
}

EMSCRIPTEN_KEEPALIVE
void baye_set_u8_value(U8*value, U8 cvalue) {
    *(U8*)value = cvalue;
}

EMSCRIPTEN_KEEPALIVE
U32 baye_get_u16_value(U16*value) {
    return *(U16*)value;
}

EMSCRIPTEN_KEEPALIVE
void baye_set_u16_value(U16*value, U16 cvalue) {
    *(U16*)value = cvalue;
}

EMSCRIPTEN_KEEPALIVE
U32 baye_get_u32_value(U32*value) {
    return *(U32*)value;
}

EMSCRIPTEN_KEEPALIVE
void baye_set_u32_value(U32*value, U32 cvalue) {
    *(U32*)value = cvalue;
}


EMSCRIPTEN_KEEPALIVE
U32 ValueDef_get_field_count(ValueDef*def) {
    return def->subdef.objDef->count;
}


EMSCRIPTEN_KEEPALIVE
Field *ValueDef_get_field_by_index(ValueDef*def, U32 ind) {
    return &def->subdef.objDef->fields[ind];
}

EMSCRIPTEN_KEEPALIVE
U32 ValueDef_get_array_length(ValueDef*def) {
    return def->size / def->subdef.arrDef->size;
}

EMSCRIPTEN_KEEPALIVE
U32 ValueDef_get_size(ValueDef*def) {
    return def->size;
}

EMSCRIPTEN_KEEPALIVE
ValueDef* ValueDef_get_array_subdef(ValueDef*def) {
    return def->subdef.arrDef;
}

EMSCRIPTEN_KEEPALIVE
FAR const U8* bayeGetPersonName(U8 personIndex)
{
    static U8 name[32] = {0};
    name[0] = 0;
    GetPersonName(personIndex, name);
    return name;
}

EMSCRIPTEN_KEEPALIVE
FAR const U8* bayeGetToolName(U8 toolIndex)
{
    static U8 name[32] = {0};
    name[0] = 0;
    GetGoodsName(toolIndex, name);
    return name;
}

EMSCRIPTEN_KEEPALIVE
FAR const U8* bayeGetSkillName(U8 skillIndex)
{
    static U8 name[32] = {0};
    name[0] = 0;
    ResLoadToMem(SKL_NAMID, skillIndex+1, name);
    return name;
}

EMSCRIPTEN_KEEPALIVE
FAR const U8* bayeGetCityName(U8 cityIndex)
{
    static U8 name[32] = {0};
    name[0] = 0;
    GetCityName(cityIndex, name);
    return name;
}

EMSCRIPTEN_KEEPALIVE
FAR U32 bayeStrLen(const U8* s)
{
    return (U32)strlen((const char*)s);
}

Value* bind_get_global(void);

EMSCRIPTEN_KEEPALIVE
Value* bayeGetGlobal(void) {
    return bind_get_global();
}

EMSCRIPTEN_KEEPALIVE
U8* bayeGetCustomData(void) {
    return gam_getcustomdata();
}

EMSCRIPTEN_KEEPALIVE
void bayeSetCustomData(U8*data) {
    return gam_setcustomdata(data);
}

EMSCRIPTEN_KEEPALIVE
void bayeScriptInit(void) {
    script_init();
}

EMSCRIPTEN_KEEPALIVE
U32 bayeRand(void) {
    return gam_rand();
}

EMSCRIPTEN_KEEPALIVE
void bayeSRand(U32 seed) {
    gam_srand(seed);
}

EMSCRIPTEN_KEEPALIVE
U32 bayeGetSeed(void) {
    return gam_seed();
}

EMSCRIPTEN_KEEPALIVE
void bayeLevelUp(U8 person) {
    LevelUp(&g_Persons[person]);
}

EMSCRIPTEN_KEEPALIVE
U32 bayeOrderNeedMoney(U8 order) {
    return OrderNeedMoney(order);
}

EMSCRIPTEN_KEEPALIVE
void bayeOrderComsumeMoney(U8 city, U8 order) {
    OrderConsumeMoney(city, order);
}


EMSCRIPTEN_KEEPALIVE
U32 bayeFgtGetGenTer(U8 index) {
    return FgtGetGenTer(index);
}

EMSCRIPTEN_KEEPALIVE
void bayePutPersonInCity(U8 city, U8 person) {
    AddPerson(city, person);
}

EMSCRIPTEN_KEEPALIVE
void bayePutToolInCity(U8 city, U8 tool, U8 hide) {
    AddGoodsEx(city, tool, !hide);
}


EMSCRIPTEN_KEEPALIVE
void bayeDeletePersonInCity(U8 city, U8 person) {
    DelPerson(city, person);
}

EMSCRIPTEN_KEEPALIVE
void bayeDeleteToolInCity(U8 city, U8 tool, U8 hide) {
    DelGoods(city, tool);
}

EMSCRIPTEN_KEEPALIVE
U8 bayeGetArmType(U8 pIndex) {
    return GetArmType(&g_Persons[pIndex]);
}

EMSCRIPTEN_KEEPALIVE
U8* bayeGetGBKBuffer(void) {
    return g_asyncActionStringParam;
}

EMSCRIPTEN_KEEPALIVE
void bayeLcdDrawImage(U16 resid, U16 item, U8 index, U8 x, U8 y, U8 flag) {
    return PlcRPicShowEx(resid, item, index+1, x, y, flag);
}

EMSCRIPTEN_KEEPALIVE
U32 bayeLcdDrawText(U8*text, U8 x, U8 y) {
    return GamStrShowS(x, y, text);
}

/* 清除屏幕矩形 */
EMSCRIPTEN_KEEPALIVE
void bayeLcdClearRect(U8 left, U8 top, U8 right, U8 bottom) {
    gam_clrlcd(left, top, right, bottom);
}

/* 反显屏幕 */
EMSCRIPTEN_KEEPALIVE
void bayeLcdRevertRect(U8 left, U8 top, U8 right, U8 bottom) {
    gam_revlcd(left, top, right, bottom);
}

/* 画点函数 */
EMSCRIPTEN_KEEPALIVE
void bayeLcdDot(U8 x, U8 y, U8 color) {
    gam_putpixel(x, y, color);
}

/* 显示直线 */
EMSCRIPTEN_KEEPALIVE
void bayeLcdDrawLine(U8 sx, U8 sy, U8 ex, U8 ey, U8 color) {
    if (color) {
        gam_line(sx, sy, ex, ey);
    } else {
        // TODO:
        // gam_linec(sx, sy, ex, ey);
        printf("clear line not implemented\n");
    }
}

/* 显示矩形 */
EMSCRIPTEN_KEEPALIVE
void bayeLcdDrawRect(U8 sx, U8 sy, U8 ex, U8 ey, U8 color) {
    if (color) {
        gam_rect(sx, sy, ex, ey);
    } else {
        gam_rectc(sx, sy, ex, ey);
    }
}
