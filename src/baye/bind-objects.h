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

void bind_init(void);

#ifndef offsetof
#define offsetof __builtin_offsetof
#endif

#define AL(a) sizeof(a)/sizeof(*a)


// static
#define _FIELD(name, ST, field, t) {name, {.def=&_##t##_def, .offset=offsetof(ST, field)}}

#define FIELD_RW(ST, field, t) _FIELD(#field, ST, field, t)
#define _FIELD_RW(field, t) FIELD_RW(_ST, field, t)
#define _FIELD_RO _FIELD_RW

#define _U8ARR_FIELD(field, l) {#field, {&U8_a##l##_def, offsetof(_ST, field)}}

#define DEC_U8ARR_DEF(n) \
        static ValueDef U8_a##n##_def = {\
            ValueTypeArray, n, .subdef.arrDef = &_U8_def\
        }

#define _BEGIN_SDEF(name) static Field name##_fields[] = {
#define _END_SDEF(name) }; \
\
            static ObjectDef name##_obj_def = { \
                AL(name##_fields), 0, sizeof(_ST), name##_fields \
            }; \
\
            static ValueDef name##_value_def = { \
                .type = ValueTypeObject, \
                .size = sizeof(_ST), \
                .subdef.objDef = &name##_obj_def, \
            }; \
            static Value name = {.def = &name##_value_def}

// #### dynamic add
#define DEFADD_U8ARR(name, n) ObjectDef_addFieldArray(def, #name, ValueTypeU8, name, n);
#define DEFADDF(name, t) ObjectDef_addFieldF(def, #name, ValueType##t, &name, 0, 0)

#endif /* bind_objects_h */

