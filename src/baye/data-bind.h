//
//  data-bind.h
//  baye-ios
//
//  Created by loong on 16/9/16.
//
//

#ifndef data_bind_h
#define data_bind_h

#include <baye/compa.h>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

typedef struct ObjectDef ObjectDef;
typedef struct ValueDef ValueDef;
typedef struct Object Object;
typedef struct Value Value;

typedef void(*Object_deinit_t)(Object*);
typedef void(*Value_deinit_t)(Value*);

typedef enum ValueType {
    ValueTypeU8 = 0,
    ValueTypeU16,
    ValueTypeU32,
    ValueTypeString,
    ValueTypeObject,
    ValueTypeArray,
    ValueTypeMethod,
} ValueType;

#define ValueFlagRead       (1 << 0)
#define ValueFlagWrite      (1 << 1)
#define ValueFlagConst      (1 << 2)
#define ValueFlagRelative   (1 << 3)

#define ValueFlagRW (ValueFlagRead | ValueFlagWrite)
#define ValueFlagRO ValueFlagRead

typedef struct ValueDef {
    ValueType type;
    U32 size;
    union {
        ObjectDef *objDef;
        ValueDef *arrDef;
    }subdef;
} ValueDef;

typedef struct Value {
    ValueDef *def;
    U32 offset;
} Value;

typedef struct Field {
    const char *name;
    Value value;
} Field;

typedef struct ObjectDef
{
    U16 count;
    U16 alloced;
    Field* fields;
} ObjectDef;

ObjectDef* ObjectDef_new(void);

void ObjectDef_free(ObjectDef* def);
void ObjectDef_addField(ObjectDef* def, Field* field);


extern ValueDef _U8_def;
extern ValueDef _U16_def;
extern ValueDef _U32_def;
extern ValueDef _str_def;


EMSCRIPTEN_KEEPALIVE
ValueType Value_get_type(Value*value);

EMSCRIPTEN_KEEPALIVE
void* Value_get_addr(Value*value);

EMSCRIPTEN_KEEPALIVE
U8 Value_get_u8_value(Value*value);

EMSCRIPTEN_KEEPALIVE
void Value_set_u8_value(Value*value, U8 cvalue);

EMSCRIPTEN_KEEPALIVE
U16 Value_get_u16_value(Value*value);

EMSCRIPTEN_KEEPALIVE
void Value_set_u16_value(Value*value, U16 cvalue);

EMSCRIPTEN_KEEPALIVE
U32 Value_get_u32_value(Value*value);

EMSCRIPTEN_KEEPALIVE
void Value_set_u32_value(Value*value, U32 cvalue);

EMSCRIPTEN_KEEPALIVE
U32 Object_get_field_count(Value*value);

EMSCRIPTEN_KEEPALIVE
Field* Object_get_field_by_index(Value*obj, U32 ind);

EMSCRIPTEN_KEEPALIVE
const char* Object_get_field_name(Field*field);

EMSCRIPTEN_KEEPALIVE
Value* Object_get_field_value(Field*field);

EMSCRIPTEN_KEEPALIVE
ValueType Object_get_field_type(Field*field);


#endif /* data_bind_h */
