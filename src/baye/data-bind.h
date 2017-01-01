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
    U32 size;
    Field* fields;
} ObjectDef;

ObjectDef* ObjectDef_new(void);

void ObjectDef_free(ObjectDef* def);
void ObjectDef_addField(ObjectDef* def, Field* field);


extern ValueDef _U8_def;
extern ValueDef _U16_def;
extern ValueDef _U32_def;
extern ValueDef _str_def;


void ObjectDef_addField(ObjectDef* def, Field* field);
void ObjectDef_addFieldF(ObjectDef* def, const char*name, ValueType t, void* ptr, void* subdef, U32 arrLen);
void ObjectDef_addFieldArray(ObjectDef* def, const char*name, ValueType t, void* ptr, U32 arrLen);

Value* Value_ObjectValue_new(void);
void Value_ObjectValue_free(Value*value);

#endif /* data_bind_h */
