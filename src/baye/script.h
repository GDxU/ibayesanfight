//
//  script.h
//  baye-ios
//
//  Created by loong on 16/9/17.
//
//

#ifndef script_h
#define script_h

#include <stdio.h>
#include <inc/dictsys.h>
#include <baye/data-bind.h>

void script_init(void);
int has_hook(const char* name);
int call_hook(const char* name, Value* context);

#endif /* script_h */
