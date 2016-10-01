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

#endif /* bind_objects_h */
