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
int call_script(const char* name, Object* context);

#endif /* script_h */
