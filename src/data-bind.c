//
//  data-bind.c
//  baye-ios
//
//  Created by loong on 16/9/16.
//
//
#include <stdlib.h>
#include <stdio.h>
#include "baye/data-bind.h"
#include "baye/comm.h"

ValueDef _U8_def = {
    .type = ValueTypeU8,
    .size = sizeof(U8),
    .subdef = {0},
};

ValueDef _U16_def = {
    .type = ValueTypeU16,
    .size = sizeof(U16),
    .subdef = {0},
};

ValueDef _U32_def = {
    .type = ValueTypeU32,
    .size = sizeof(U32),
    .subdef = {0},
};

ValueDef _str_def = {
    .type = ValueTypeString,
    .size = sizeof(char*),
    .subdef = {0},
};

ObjectDef* ObjectDef_new(void) {
    ObjectDef* def = (ObjectDef*)malloc(sizeof(ObjectDef));
    def->count = 0;
    def->alloced = 8;
    def->fields = (Field*)malloc(sizeof(*def->fields) * def->alloced);
    return def;
}

void ObjectDef_free(ObjectDef* def) {
    if (def == NULL) return;
    free(def->fields);
    free(def);
}

void ObjectDef_addField(ObjectDef* def, Field* field)
{
    if (def->count == def->alloced) {
        def->alloced *= 2;
        def->fields = (Field*)realloc(def->fields, sizeof(*def->fields)*def->alloced);
    }
    memcpy(&def->fields[def->count], field, sizeof(*def->fields));
    def->count += 1;
}

void ObjectDef_addFieldF(ObjectDef* def, const char*name, ValueType t, void* ptr, void* subdef, U32 arrLen)
{
    Field field;
    field.name = name;
    field.value.offset = (U32)ptr;
    switch (t) {
        case ValueTypeU8:
            field.value.def = &_U8_def;
            break;
        case ValueTypeU16:
            field.value.def = &_U16_def;
            break;
        case ValueTypeU32:
            field.value.def = &_U32_def;
            break;
        case ValueTypeString:
            field.value.def = &_str_def;
            break;
        case ValueTypeArray:
        {
            //TODO: Free it
            ValueDef* arrDef = malloc(sizeof(ValueDef));
            arrDef->subdef.arrDef = subdef;
            arrDef->size = arrDef->subdef.arrDef->size * arrLen;
            field.value.def = arrDef;
            field.value.def->type = t;
            break;
        }
        case ValueTypeObject:
        {
            //TODO: Free it
            ValueDef* arrDef = malloc(sizeof(ValueDef));
            arrDef->subdef.objDef = subdef;
            arrDef->size = arrDef->subdef.objDef->size;
            field.value.def = arrDef;
            field.value.def->type = t;
            break;
        }
    }
    ObjectDef_addField(def, &field);
}

void ObjectDef_addFieldArray(ObjectDef* def, const char*name, ValueType t, void* ptr, U32 arrLen)
{
    ValueDef *subdef;
    if (*name == '&') {
        name += 1;
    }
    switch (t) {
        case ValueTypeU8:
            subdef = &_U8_def;
            break;
        case ValueTypeU16:
            subdef = &_U16_def;
            break;
        case ValueTypeU32:
            subdef = &_U32_def;
            break;
        case ValueTypeString:
            subdef = &_str_def;
            break;
        default:
            printf("Not implementd\n");
            abort();
            break;
    }
    return ObjectDef_addFieldF(def, name, ValueTypeArray, ptr, subdef, arrLen);
}
