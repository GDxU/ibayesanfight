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

typedef struct Object Object;
typedef struct Field Field;

Object* object_new(U16 maxFields);
Object* object_new_slave(Object* master, U16 maxFields);
void object_release(Object* obj);

void object_bind_u8(Object*context, const I8*name, U8*ptr, U8 writeable);
void object_bind_u16(Object*context, const I8*name, U16*ptr, U8 writeable);
void object_bind_u32(Object*context, const I8*name, U32*ptr, U8 writeable);
void object_bind_str(Object*context, const I8*name, U8*ptr, U8 writeable);
void object_bind_bin(Object*context, const I8*name, U8*ptr, U32 len, U8 writeable);
void object_bind_object(Object*context, const I8*name, Object*ptr, U8 writeable);

EMSCRIPTEN_KEEPALIVE
U16 object_get_field_count(Object*context);
EMSCRIPTEN_KEEPALIVE
Field* object_get_field_by_index(Object*context, U16 index);
EMSCRIPTEN_KEEPALIVE
Field* object_get_field(Object*context, const I8*name);
EMSCRIPTEN_KEEPALIVE
unsigned long object_get_field_type(Field*field);
EMSCRIPTEN_KEEPALIVE
unsigned long object_get_field_name(Field*field);
EMSCRIPTEN_KEEPALIVE
unsigned long object_get_field_size(Field*field);
EMSCRIPTEN_KEEPALIVE
unsigned long object_get_field_value(Field*field);
EMSCRIPTEN_KEEPALIVE
void object_set_field_value(Field*field, unsigned long value, U32 size);

#endif /* data_bind_h */
