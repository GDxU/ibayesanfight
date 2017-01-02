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
#include "baye/comm.h"

DEC_U8ARR_DEF(5);
DEC_U8ARR_DEF(6);
DEC_U8ARR_DEF(8);
DEC_U8ARR_DEF(FGTA_MAX);

static Value g_var = {0};

void global_var_init(void) {
    static ObjectDef* def = NULL;
    static ValueDef vref;

    if (def == NULL) {
        def = ObjectDef_new();
    }

    vref.size = 0;
    vref.subdef.objDef = def;
    vref.type = ValueTypeObject;

    g_var.def = &vref;
    g_var.offset = 0;

    DEFADD_U8ARR(g_FightMap, SCR_MAPWID*SCR_MAPHGT);
    DEFADD_U8ARR(g_FightPath, FGT_MRG*FGT_MRG + 25);
    DEFADD_U8ARR(g_FgtAtkRng, MAX_ATT_RANGE + 5);

    DEFADDF(g_TileId, U16);
    DEFADDF(g_EneTmpProv, U16);

    DEFADDF(g_MapWid, U8);
    DEFADDF(g_MapHgt, U8);

    DEFADDF(g_FoucsX, U8);
    DEFADDF(g_FoucsY, U8);

    DEFADDF(g_MapSX, U8);
    DEFADDF(g_MapSY, U8);

    DEFADDF(g_PathSX, U8);
    DEFADDF(g_PathSY, U8);

    DEFADDF(g_PUseSX, U8);
    DEFADDF(g_PUseSY, U8);

    DEFADDF(g_BakUpX, U8);
    DEFADDF(g_BakUpY, U8);

    DEFADDF(g_CityX, U8);
    DEFADDF(g_CityY, U8);

    DEFADDF(g_FgtOver, U8);

    DEFADDF(g_FgtWeather, U8);
    DEFADDF(g_FgtBoutCnt, U8);
    DEFADDF(g_MainGenIdx, U8);
    DEFADDF(g_LookEnemy, U8);
    DEFADDF(g_LookMovie, U8);
    DEFADDF(g_MoveSpeed, U8);

    DEFADDF(g_PlayerKing, U8);
    DEFADDF(g_YearDate, U16);

    DEFADDF(g_MonthDate, U8);
    DEFADDF(g_PIdx, U8);

    DEFADD_U8ARR(&g_PersonsQueue, PERSON_MAX);
    DEFADD_U8ARR(&g_GoodsQueue, GOODS_MAX);


    {
#define _ST PersonType
        static Field _fields[] = {
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
        };

        static ObjectDef _obj_def = {
            AL(_fields), 0, sizeof(_ST), _fields
        };

        static ValueDef _value_def = {
            .type = ValueTypeObject,
            .size = sizeof(_ST),
            .subdef.objDef = &_obj_def,
        };
#undef _ST
        static ValueDef arrdef = { .type=ValueTypeArray, .size=0, .subdef.arrDef=&_value_def };
        static Field arrfield = {"g_Persons", {.def=&arrdef, .offset=0}};
        arrdef.size = _value_def.size * PERSON_MAX;
        arrfield.value.offset = (U32)g_Persons;

        ObjectDef_addField(def, &arrfield);
    }
    {
#define _ST CityType
        static Field _fields[] = {
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
            _FIELD_RW(PersonQueue, U8),
            _FIELD_RW(Persons, U8),
            _FIELD_RW(ToolQueue, U8),
            _FIELD_RW(Tools, U8),
        };

        static ObjectDef _obj_def = {
            AL(_fields), 0, sizeof(_ST), _fields
        };

        static ValueDef _value_def = {
            .type = ValueTypeObject,
            .size = sizeof(_ST),
            .subdef.objDef = &_obj_def,
        };
#undef _ST
        static ValueDef arrdef = { .type=ValueTypeArray, .size=0, .subdef.arrDef=&_value_def };
        static Field arrfield = {"g_Cities", {.def=&arrdef, .offset=0}};
        arrdef.size = _value_def.size * CITY_MAX;
        arrfield.value.offset = (U32)g_Cities;

        ObjectDef_addField(def, &arrfield);
    }
    {
#define _ST GOODS
        static Field _fields[] = {
            _FIELD_RO(useflag, U8),
            _FIELD_RO(changeAttackRange, U8),
            //_FIELD_RO(atRange, Binary),// TODO
            _FIELD_RO(at, U8),
            _FIELD_RO(iq, U8),
            _FIELD_RO(move, U8),
            _FIELD_RO(arm, U8),
        };

        static ObjectDef _obj_def = {
            AL(_fields), 0, sizeof(_ST), _fields
        };

        static ValueDef _value_def = {
            .type = ValueTypeObject,
            .size = sizeof(_ST),
            .subdef.objDef = &_obj_def,
        };
#undef _ST
        static ValueDef arrdef = { .type=ValueTypeArray, .size=0, .subdef.arrDef=&_value_def };
        static Field arrfield = {"g_Tools", {.def=&arrdef, .offset=0}};
        arrdef.size = _value_def.size * GOODS_MAX;
        arrfield.value.offset = (U32)ResLoadToCon(GOODS_RESID, 1, g_CBnkPtr);

        ObjectDef_addField(def, &arrfield);
    }
    {
#define _ST SKILLEF

        static Field _fields[] = {
            _FIELD_RO(aim, U8),
            _FIELD_RO(state, U8),
            _FIELD_RO(power, U16),
            _FIELD_RO(destroy, U16),
            _FIELD_RO(useMp, U8),
            _U8ARR_FIELD(weather, 5),
            _U8ARR_FIELD(eland, 8),
            _U8ARR_FIELD(oland, 8),
            _U8ARR_FIELD(earm, 6),
        };

        static ObjectDef _obj_def = {
            AL(_fields), 0, sizeof(_ST), _fields
        };

        static ValueDef _value_def = {
            .type = ValueTypeObject,
            .size = sizeof(_ST),
            .subdef.objDef = &_obj_def,
        };
#undef _ST
        static ValueDef arrdef = { .type=ValueTypeArray, .size=0, .subdef.arrDef=&_value_def };
        static Field arrfield = {"g_Skills", {.def=&arrdef, .offset=0}};
        arrdef.size = _value_def.size * 255; // TODO
        arrfield.value.offset = (U32)ResLoadToCon(SKL_RESID, 1, g_CBnkPtr);
        ObjectDef_addField(def, &arrfield);
    }
    {
#define _ST JLATT
        static Field _fields[] = {
            _FIELD_RW(level, U8),
            _FIELD_RW(canny, U8),
            _FIELD_RW(ter, U8),
            _FIELD_RW(bile, U8),
            _FIELD_RW(armsType, U8),
            _FIELD_RW(exp, U8),
            _FIELD_RW(arms, U16),
            _FIELD_RW(at, U16),
            _FIELD_RW(df, U16),
        };

        static ObjectDef _obj_def = {
            AL(_fields), 0, sizeof(_ST), _fields
        };

        static ValueDef _value_def = {
            .type = ValueTypeObject,
            .size = sizeof(_ST),
            .subdef.objDef = &_obj_def,
        };
#undef _ST
        static ValueDef arrdef = { .type=ValueTypeArray, .size=0, .subdef.arrDef=&_value_def };
        static Field arrfield = {"g_GenAtt", {.def=&arrdef, .offset=0}};
        arrdef.size = _value_def.size * 2;
        arrfield.value.offset = (U32)g_GenAtt;
        ObjectDef_addField(def, &arrfield);
    }
    {
#define _ST JLPOS
        static Field _fields[] = {
            _FIELD_RW(x, U8),
            _FIELD_RW(y, U8),
            _FIELD_RW(hp, U8),
            _FIELD_RW(mp, U8),
            _FIELD_RW(move, U8),
            _FIELD_RW(active, U8),
            _FIELD_RW(state, U8),
        };

        static ObjectDef _obj_def = {
            AL(_fields), 0, sizeof(_ST), _fields
        };

        static ValueDef _value_def = {
            .type = ValueTypeObject,
            .size = sizeof(_ST),
            .subdef.objDef = &_obj_def,
        };
#undef _ST
        static ValueDef arrdef = { .type=ValueTypeArray, .size=0, .subdef.arrDef=&_value_def };
        static Field arrfield = {"g_GenPos", {.def=&arrdef, .offset=0}};
        arrdef.size = _value_def.size * FGTA_MAX;
        arrfield.value.offset = (U32)g_GenPos;
        ObjectDef_addField(def, &arrfield);
    }
    {
#define _ST FGTJK
        static Field _fields[] = {
            _FIELD_RW(Mode, U8),
            _FIELD_RW(Way, U8),
            _FIELD_RW(MapId, U16),
            _FIELD_RW(MProvender, U16),
            _FIELD_RW(EProvender, U16),
            _U8ARR_FIELD(GenArray, FGTA_MAX),
        };

        static ObjectDef _obj_def = {
            AL(_fields), 0, sizeof(_ST), _fields
        };

        static ValueDef _value_def = {
            .type = ValueTypeObject,
            .size = sizeof(_ST),
            .subdef.objDef = &_obj_def,
        };
#undef _ST
        static Field field = {"g_FgtParam", {.def=&_value_def, .offset=0}};
        field.value.offset = (U32)&g_FgtParam;
        ObjectDef_addField(def, &field);
    }
    {
#define _ST EngineConfig
        static Field _fields[] = {
            _FIELD_RW(enableToolAttackRange, U8),
            _FIELD_RW(fixCityOffset, U8),
            _FIELD_RW(fixThewOverFlow, U8),
            _FIELD_RW(fixFoodOverFlow, U8),
            _FIELD_RW(fixOverFlow16, U8),
            _FIELD_RW(fixConsumeMoney, U8),
            _FIELD_RW(fixFightMoveOutRange, U8),
            _FIELD_RW(enable16bitConsumeMoney, U8),
            _FIELD_RW(enableScript, U8),
            _FIELD_RW(fixAlienateComsumeThew, U8),
            _FIELD_RW(disableSL, U8),
            _FIELD_RW(aiLevelUpSpeed, U8),
            _FIELD_RW(disableAgeGrow, U8),
            _FIELD_RW(enableCustomRatio, U8),
            _FIELD_RW(ratioOfArmsToLevel, U16),
            _FIELD_RW(ratioOfArmsToAge, U8),
            _FIELD_RW(ratioOfArmsToIQ, U8),
            _FIELD_RW(ratioOfArmsToForce, U8),
            _FIELD_RW(ratioOfAttToForce, U8),
            _FIELD_RW(ratioOfAttToIQ, U8),
            _FIELD_RW(ratioOfAttToAge, U8),
            _FIELD_RW(ratioOfDefenceToForce, U8),
            _FIELD_RW(ratioOfDefenceToIQ, U8),
            _FIELD_RW(ratioOfDefenceToAge, U8),
            _FIELD_RW(ratioOfFoodToArmsPerMouth, U16),
            _FIELD_RW(ratioOfFoodToArmsPerDay, U16),
            _FIELD_RW(armsPerDevotion, U8),
            _FIELD_RW(armsPerMoney, U8),
            _FIELD_RW(maxLevel, U8),
            _FIELD_RW(responseNoteOfBettle, U8),
            _FIELD_RW(aiDefenceMode, U8),
            _FIELD_RW(aiAttackMethod, U8),
        };

        static ObjectDef _obj_def = {
            AL(_fields), 0, sizeof(_ST), _fields
        };

        static ValueDef _value_def = {
            .type = ValueTypeObject,
            .size = sizeof(_ST),
            .subdef.objDef = &_obj_def,
        };
#undef _ST
        static Field field = {"g_engineConfig", {.def=&_value_def, .offset=0}};
        field.value.offset = (U32)&g_engineConfig;
        ObjectDef_addField(def, &field);
    }
    {
#define _ST OrderType
        static Field _fields[] = {
            _FIELD_RW(OrderId, U8),
            _FIELD_RW(Person, U8),
            _FIELD_RW(City, U8),
            _FIELD_RW(Object, U8),
            _FIELD_RW(Arms, U16),
            _FIELD_RW(Food, U16),
            _FIELD_RW(Money, U16),
            _FIELD_RW(Consume, U8),
            _FIELD_RW(TimeCount, U8),
        };

        static ObjectDef _obj_def = {
            AL(_fields), 0, sizeof(_ST), _fields
        };

        static ValueDef _value_def = {
            .type = ValueTypeObject,
            .size = sizeof(_ST),
            .subdef.objDef = &_obj_def,
        };
#undef _ST
        static ValueDef arrdef = { .type=ValueTypeArray, .size=0, .subdef.arrDef=&_value_def };
        static Field arrfield = {"g_OrderQueue", {.def=&arrdef, .offset=0}};
        arrdef.size = _value_def.size * ORDER_MAX;
        arrfield.value.offset = (U32)ORDERQUEUE;
        ObjectDef_addField(def, &arrfield);
    }

    DEFADD_U8ARR(FIGHTERS_IDX, 30);
    DEFADD_U8ARR(FIGHTERS, 300);
}

Value* bind_get_global(void) {
    if (g_var.def == NULL) {
        global_var_init();
    }
    return &g_var;
}
