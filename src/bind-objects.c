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

void object_bind_JLATT(Object*o, JLATT	*pAtk)
{
    object_bind_u8(o, "level", pAtk->level, 1);
    object_bind_u8(o, "canny", &pAtk->canny, 1);
    object_bind_u8(o, "ter", &pAtk->ter, 1);
    //object_bind_u8(o, "bile", &pAtk->bile, 1);
    object_bind_u8(o, "armsType", &pAtk->armsType, 1);
    object_bind_u8(o, "exp", pAtk->exp, 1);
    object_bind_u16(o, "arms", pAtk->arms, 1);
    object_bind_u16(o, "at", &pAtk->at, 1);
    object_bind_u16(o, "df", &pAtk->df, 1);
}

Object* create_JLATT(JLATT	*pAtk)
{
    Object* obj = object_new(16);
    object_bind_JLATT(obj, pAtk);
    return obj;
}

void object_bind_city(Object*o, CityType *city)
{
    object_bind_u8(o, "id", &city->Id, 0);
    object_bind_u8(o, "belong", &city->Belong, 1);
    object_bind_u8(o, "satrapId", &city->SatrapId, 1);
    object_bind_u16(o, "farmingLimit", &city->FarmingLimit, 1);
    object_bind_u16(o, "farming", &city->Farming, 1);
    object_bind_u16(o, "commerceLimit", &city->CommerceLimit, 1);
    object_bind_u16(o, "commerce", &city->Commerce, 1);
    object_bind_u8(o, "peopleDevotion", &city->PeopleDevotion, 1);
    object_bind_u8(o, "avoidCalamity", &city->AvoidCalamity, 1);
    object_bind_u32(o, "populationLimit", &city->PopulationLimit, 1);
    object_bind_u32(o, "population", &city->Population, 1);
    object_bind_u16(o, "money", &city->Money, 1);
    object_bind_u16(o, "food", &city->Food, 1);
    object_bind_u16(o, "mothballArms", &city->MothballArms, 1);
}

void object_bind_person(Object*o, PersonType *person)
{
    object_bind_u8(o, "id", &person->Id, 0);
    object_bind_u8(o, "belong", &person->Belong, 1);
    object_bind_u8(o, "level", &person->Level, 1);
    object_bind_u8(o, "force", &person->Force, 1);
    object_bind_u8(o, "iq", &person->IQ, 1);
    object_bind_u8(o, "devotion", &person->Devotion, 1);
    object_bind_u8(o, "character", &person->Character, 1);
    object_bind_u8(o, "experience", &person->Experience, 1);
    object_bind_u8(o, "thew", &person->Thew, 1);
    object_bind_u8(o, "armsType", &person->ArmsType, 1);
    object_bind_u16(o, "arms", &person->Arms, 1);
    object_bind_u8(o, "equip1", &person->Equip[0], 1);
    object_bind_u8(o, "equip2", &person->Equip[1], 1);
    object_bind_u8(o, "age", &person->Age, 1);
}

void object_bind_tool(Object*o, GOODS *tool)
{
    object_bind_u8(o, "useflag", &tool->useflag, 0);
    object_bind_u8(o, "changeAttackRange", &tool->changeAttackRange, 0);
    object_bind_bin(o, "atRange", tool->atRange, sizeof(tool->atRange), 0);
    object_bind_u8(o, "at", &tool->at, 0);
    object_bind_u8(o, "iq", &tool->iq, 0);
    object_bind_u8(o, "move", &tool->move, 0);
    object_bind_u8(o, "arm", &tool->arm, 0);
}

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
