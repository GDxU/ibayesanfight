//
//  script.c
//  baye-ios
//
//  Created by loong on 16/9/17.
//
//

#include "baye/script.h"
#include "baye/consdef.h"
#include "baye/datman.h"
#include <emscripten.h>

void script_init(void)
{
    U8* script = ResLoadStringWithId(ENGINE_SCRIPT);
    EM_ASM_INT({
        if (window.baye == undefined) {
            window.baye = {};
        }
        var script = UTF8ToString($0);
        eval(script);
    }, script);
}

int call_script(I8* name, Object* context)
{
    return EM_ASM_INT({
        var name = UTF8ToString($0);
        var cContext = $1;

        var jsContext = baye_bridge_obj(cContext);
        var rv = 0;

        if (window.baye == undefined || window.baye.methods == undefined || window.baye.methods[name] == undefined) {
            rv = -1;
        } else {
            rv = window.baye.methods[name](jsContext);
            baye_sync_obj(cContext, jsContext);
        }
        return rv;
    }, name, context);
}

