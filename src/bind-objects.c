//
//  bind-objects.c
//  baye-ios
//
//  Created by loong on 16/9/17.
//
//

#include "baye/bind-objects.h"
#include "baye/extern.h"
#include "baye/datman.h"

#ifndef offsetof
#define offsetof __builtin_offsetof
#endif

#define AL(a) sizeof(a)/sizeof(*a)

#define _FIELD(name, ST, field, t) {name, {.def=&_##t##_def, .offset=offsetof(ST, field)}}

#define FIELD_RW(ST, field, t) _FIELD(#field, ST, field, t)
#define _FIELD_RW(field, t) FIELD_RW(_ST, field, t)
#define _FIELD_RO _FIELD_RW

static Field JLATT_fields[] = {
    {"level", {.def=&_U8_def, .offset=offsetof(JLATT, level)}},
#define _ST JLATT
    _FIELD_RW(level, U8),
    _FIELD_RW(canny, U8),
    _FIELD_RW(ter, U8),
    _FIELD_RW(bile, U8),
    _FIELD_RW(armsType, U8),
    _FIELD_RW(exp, U8),
    _FIELD_RW(arms, U16),
    _FIELD_RW(at, U16),
    _FIELD_RW(df, U16),
#undef _ST
};

static ObjectDef JLATT_def = {
    AL(JLATT_fields), 0, JLATT_fields
};

static Field City_fields[] = {
#define _ST CityType
    _FIELD_RW(State, U8),
    _FIELD_RW(Belong, U8),
    _FIELD_RW(SatrapId, U8),
    _FIELD_RW(FarmingLimit, U16),
    _FIELD_RW(Farming, U16),
    _FIELD_RW(CommerceLimit, U16),
    _FIELD_RW(Commerce, U16),
    _FIELD_RW(PeopleDevotion, U8),
    _FIELD_RW(AvoidCalamity, U8),
    _FIELD_RW(PopulationLimit, U32),
    _FIELD_RW(Population, U32),
    _FIELD_RW(Money, U16),
    _FIELD_RW(Food, U16),
    _FIELD_RW(MothballArms, U16),
#undef _ST
};

static ObjectDef City_def = {
    AL(City_fields), 0, City_fields
};

static Field Person_fields[] = {
#define _ST PersonType
    _FIELD_RW(OldBelong, U8),
    _FIELD_RW(Belong, U8),
    _FIELD_RW(Level, U8),
    _FIELD_RW(Force, U8),
    _FIELD_RW(IQ, U8),
    _FIELD_RW(Devotion, U8),
    _FIELD_RW(Character, U8),
    _FIELD_RW(Experience, U8),
    _FIELD_RW(Thew, U8),
    _FIELD_RW(ArmsType, U8),
    _FIELD_RW(Arms, U16),
    _FIELD("Tool1", _ST, Equip[0], U8),
    _FIELD("Tool2", _ST, Equip[1], U8),
    _FIELD_RW(Age, U8),
#undef _ST
};

static ObjectDef Person_object_def = {
    AL(Person_fields), 0, Person_fields
};

static ValueDef Person_value_def = {
    .type = ValueTypeObject,
    .size = sizeof(PersonType),
    .subdef.objDef = &Person_object_def,
};

static Field Tool_fields[] = {
#define _ST GOODS
    _FIELD_RO(useflag, U8),
    _FIELD_RO(changeAttackRange, U8),
    //_FIELD_RO(atRange, Binary),// TODO
    _FIELD_RO(at, U8),
    _FIELD_RO(iq, U8),
    _FIELD_RO(move, U8),
    _FIELD_RO(arm, U8),
#undef _ST
};

static ObjectDef Tool_def = {
    AL(Tool_fields), 0, Tool_fields
};

static struct g_var {
    Value* people;
    Value* tools;
    Value* cities;
} g_var = {0};

void g_var_init(void) {
    static ValueDef personArray_def = { .type=ValueTypeArray, .size=0, .subdef.arrDef=&Person_value_def };
    static Value personArray = {.def=&personArray_def, .offset=0};
    personArray_def.size =Person_value_def.size * PERSON_MAX;
    personArray.offset = (U32)g_Persons;
    g_var.people = &personArray;
}

#if 0

void object_bind_FGTJK(Object*o, FGTJK*param)
{
    object_bind_u8(o, "mode", &param->Mode, 0);
    object_bind_u8(o, "way", &param->Way, 0);
    object_bind_u16(o, "mapId", &param->MapId, 0);
    object_bind_u16(o, "ourFoods", &param->MProvender, 1);
    object_bind_u16(o, "enemyFoods", &param->EProvender, 1);
    object_bind_bin(o, "genArray", param->GenArray, FGTA_MAX, 1);
}

void object_bind_JLPOS(Object*o, JLPOS *pos)
{
    object_bind_u8(o, "x", &pos->x, 1);
    object_bind_u8(o, "y", &pos->y, 1);
    object_bind_u8(o, "hp", &pos->hp, 1);
    object_bind_u8(o, "mp", &pos->mp, 1);
    object_bind_u8(o, "move", &pos->move, 1);
    object_bind_u8(o, "active", &pos->active, 1);
    object_bind_u8(o, "state", &pos->state, 1);

}

void object_bind_fight_env(Object*o) {

    object_bind_bin(o, "fightPath", g_FightPath, FGT_MRG*FGT_MRG + 25, 1);
    object_bind_bin(o, "attackRange", g_FgtAtkRng, MAX_ATT_RANGE + 5, 1);
    object_bind_u16(o, "enemyFoods", &g_EneTmpProv, 1);
    object_bind_u8(o, "mapHeight", &g_MapHgt, 0);
    object_bind_u8(o, "mapWidth", &g_MapWid, 0);
    object_bind_u8(o, "weather", &g_FgtWeather, 1);
    object_bind_u8(o, "day", &g_FgtBoutCnt, 1);
    object_bind_FGTJK(o, &g_FgtParam);

    Object* ourAttackAttr = create_JLATT(&g_GenAtt[0]);
    object_bind_object(o, "ourAttackAttr", ourAttackAttr, 1);
    Object* enemyAttackAttr = create_JLATT(&g_GenAtt[1]);
    object_bind_object(o, "enemyAttackAttr", enemyAttackAttr, 1);
}

Object* create_fight_env(void)
{
    Object* env = object_new(32);
    object_bind_fight_env(env);
    return env;
}

void object_bind_game_env(Object* o)
{
    object_bind_u8(o, "playerKing", &g_PlayerKing, 1);
    object_bind_u16(o, "year", &g_YearDate, 1);
    object_bind_u8(o, "month", &g_MonthDate, 1);
    object_bind_u8(o, "period", &g_PIdx, 0);
}

Object* get_game_env(void) {
    Object* env = object_new(8);
    object_bind_game_env(env);
    return env;
}


Object* get_tool_by_index(Object*context, U8 index)
{
    GOODS *ptr = (GOODS *)(ResLoadToCon(GOODS_RESID, 1, g_CBnkPtr) + (U16)(index) * sizeof(GOODS));
    Object*toolObj = object_new_slave(context, 16);
    object_bind_tool(toolObj, ptr);
    return toolObj;
}

Object* get_person_by_index(Object*context, U8 index)
{
    PersonType* person = &g_Persons[index];
    Object* personObj = object_new_slave(context, 32);
    object_bind_person(personObj, person);
    return personObj;
}

Object* get_geninfo_by_index(Object*context, U8 index)
{
    JLPOS* info = &g_GenPos[index];
    Object* infoObj = object_new_slave(context, 32);
    object_bind_JLPOS(infoObj, info);
    return infoObj;
}
#endif

Value* test_value(void) {
    g_var_init();
    return g_var.people;
}
