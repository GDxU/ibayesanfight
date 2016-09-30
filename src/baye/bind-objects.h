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

void bind_JLATT(Object*o, JLATT	*pAtk);
void bind_person(Object*o, PersonType *person);
void bind_city(Object*o, CityType *city);
void bind_tool(Object*o, GOODS *tool);
Object* get_person_by_index(Object*context, U8 index);
Object* get_tool_by_index(Object*context, U8 index);

void bind_game_env(Object* o);
Object* create_game_env(void);

#endif /* bind_objects_h */
