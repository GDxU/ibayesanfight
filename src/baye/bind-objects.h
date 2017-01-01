//
//  bind-objects.h
//  baye-ios
//
//  Created by loong on 16/9/17.
//
//

#ifndef bind_objects_h
#define bind_objects_h

#include <stdio.h>
#include "data-bind.h"
#include "baye/fight.h"
#include "baye/attribute.h"

void object_bind_JLATT(Object*o, JLATT	*pAtk);
void object_bind_person(Object*o, PersonType *person);
void object_bind_city(Object*o, CityType *city);
void object_bind_tool(Object*o, GOODS *tool);

Object* get_person_by_index(Object*context, U8 index);
Object* get_tool_by_index(Object*context, U8 index);

void object_bind_game_env(Object* o);
Object* get_game_env(void);
void global_var_init(void);

#ifndef offsetof
#define offsetof __builtin_offsetof
#endif

#define AL(a) sizeof(a)/sizeof(*a)

#define _FIELD(name, ST, field, t) {name, {.def=&_##t##_def, .offset=offsetof(ST, field)}}

#define FIELD_RW(ST, field, t) _FIELD(#field, ST, field, t)
#define _FIELD_RW(field, t) FIELD_RW(_ST, field, t)
#define _FIELD_RO _FIELD_RW

#define _U8ARR_FIELD(field, l) {#field, {&U8_a##l##_def, offsetof(_ST, field)}}

#define DEC_U8ARR_DEF(n) \
        static ValueDef U8_a##n##_def = {\
            ValueTypeArray, n, .subdef.arrDef = &_U8_def\
        }

#define DEFADD_U8ARR(name, n) ObjectDef_addFieldArray(def, #name, ValueTypeU8, name, n);
#define DEFADDF(name, t) ObjectDef_addFieldF(def, #name, ValueType##t, &name, 0, 0)

#endif /* bind_objects_h */
