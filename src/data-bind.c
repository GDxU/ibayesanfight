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

#define SIZEOF_FIELD_NAME 32

typedef enum ValueType {
    ValueTypeU8 = 0,
    ValueTypeU16 = 1,
    ValueTypeU32 = 2,
    ValueTypeString = 3,
    ValueTypeBinary = 4,
    ValueTypeObject = 5,
} ValueType;

typedef struct Field {
    char name[SIZEOF_FIELD_NAME];
    ValueType type;
    void *valuePtr;
    U32 valueSize;
    U32 writeable;
} Field;

typedef struct Object {
    struct Object* next;

    U16 fieldCount;
    U16 maxFields;
    Field fields[0];
} Object;

Object* object_new(U16 maxFields) {
    Object* obj = (Object*)malloc(sizeof(Object) + sizeof(Field) * maxFields);
    obj->maxFields = maxFields;
    obj->fieldCount = 0;
    obj->next = 0;
    return obj;
}

Object* object_new_slave(Object* master, U16 maxFields)
{
    Object* slave = object_new(maxFields);
    slave->next = master->next;
    master->next = slave;
    return slave;
}

void object_release(Object* obj) {
    for (int i = 0; i < obj->fieldCount; i++) {
        switch (obj->fields[i].type) {
            case ValueTypeObject:
                object_release((Object *)obj->fields[i].valuePtr);
                break;
            case ValueTypeU8:
            case ValueTypeU16:
            case ValueTypeU32:
            case ValueTypeString:
            case ValueTypeBinary:
                break;
        }
    }
    if (obj->next) {
        object_release(obj->next);
    }
    free(obj);
}

// ---------- BIND -----------
void object_bind_field2(Object*context, const char*name, void*ptr, U32 valueSize, U8 writeable, ValueType type)
{
    if (context->fieldCount == context->maxFields) {
        printf("Bind field failed, max reached.\n");
        return;
    }

    Field* field = &context->fields[context->fieldCount];
    context->fieldCount += 1;

    field->valuePtr = ptr;
    field->type = type;

    strncpy((char*)field->name, (const char*)name, SIZEOF_FIELD_NAME-1);
    field->name[SIZEOF_FIELD_NAME-1] = 0;

    field->valueSize = valueSize;
    field->writeable = writeable;
}

void object_bind_field(Object*context, const char*name, void*ptr, U8 writeable, ValueType type)
{
    object_bind_field2(context, name, ptr, 0, writeable, type);
}

void object_bind_u8(Object*context, const char*name, U8*ptr, U8 writeable)
{
    object_bind_field(context, name, ptr, writeable, ValueTypeU8);
}

void object_bind_u16(Object*context, const char*name, U16*ptr, U8 writeable)
{
    object_bind_field(context, name, ptr, writeable, ValueTypeU16);
}

void object_bind_u32(Object*context, const char*name, U32*ptr, U8 writeable)
{
    object_bind_field(context, name, ptr, writeable, ValueTypeU32);
}

void object_bind_str(Object*context, const char*name, U8*ptr, U8 writeable)
{
    object_bind_field(context, name, ptr, writeable, ValueTypeString);
}

void object_bind_bin(Object*context, const char*name, U8*ptr, U32 len, U8 writeable)
{
    object_bind_field2(context, name, ptr, len, writeable, ValueTypeBinary);
}

void object_bind_object(Object*context, const char*name, Object*ptr, U8 writeable)
{
    object_bind_field(context, name, ptr, writeable, ValueTypeObject);
}

// ---------- GET -------------
U16 object_get_field_count(Object*context)
{
    return context->fieldCount;
}

Field* object_get_field(Object*context, const char*name)
{
    for (int i = 0; i < context->fieldCount; i++) {
        if (strcmp(name, context->fields[i].name) == 0) {
            return &context->fields[i];
        }
    }
    return NULL;
}

Field* object_get_field_by_index(Object*context, U16 index)
{
    return &context->fields[index];
}

unsigned long object_get_field_value(Field*field)
{
    switch (field->type) {
        case ValueTypeU8:
            return *(U8*)field->valuePtr;
        case ValueTypeU16:
            return *(U16*)field->valuePtr;
        case ValueTypeU32:
            return *(U32*)field->valuePtr;
        case ValueTypeString:
        case ValueTypeBinary:
        case ValueTypeObject:
            return (unsigned long)field->valuePtr;
    }
}

unsigned long object_get_field_type(Field*field)
{
    return field->type;
}

unsigned long object_get_field_name(Field*field)
{
    return (unsigned long)field->name;
}

unsigned long object_get_field_size(Field*field)
{
    return field->valueSize;
}

// ---------- SET -------------
void object_set_field_value(Field*field, unsigned long value, U32 size)
{
    if (!field->writeable) {
        return;
    }

    switch (field->type) {
        case ValueTypeU8:
            *(U8*)field->valuePtr = value;
            break;
        case ValueTypeU16:
            *(U16*)field->valuePtr = value;
            break;
        case ValueTypeU32:
            *(U32*)field->valuePtr = (U32)value;
            break;
        case ValueTypeString:
            // TODO:
            break;
        case ValueTypeBinary:
            memcpy(field->valuePtr, (void*)value, min(field->valueSize, size));
            break;
        case ValueTypeObject:
            break;
    }
}
