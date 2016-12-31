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

void ObjectDef_addField(ObjectDef* def, Field* field) {
    if (def->count == def->alloced) {
        def->alloced *= 2;
        def->fields = (Field*)realloc(def->fields, sizeof(*def->fields)*def->alloced);
    }
    memcpy(&def->fields[def->count], field, sizeof(*def->fields));
    def->count += 1;
}
