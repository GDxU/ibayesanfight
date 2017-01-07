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
    EM_ASM({
        if (window.baye == undefined) {
            window.baye = {};
        }
        if (window.baye.hooks == undefined) {
            window.baye.hooks = {};
        }
        window.baye.data = baye_bridge_value(_bayeGetGlobal());
    });

    U8* script = ResLoadStringWithId(ENGINE_SCRIPT);
    if (script) {
        EM_ASM_INT({
            var script = UTF8ToString($0);
            eval(script);
        }, script);
    }
}

int call_hook(const char* name, Value* context)
{
    return EM_ASM_INT({
        var name = UTF8ToString($0);
        var rv = 0;

        if (window.baye == undefined || window.baye.hooks == undefined || window.baye.hooks[name] == undefined) {
            rv = -1;
        } else {
            var cContext = $1;
            if (cContext != 0) {
                var jsContext = baye_bridge_value(cContext);
                rv = window.baye.hooks[name](jsContext);
            } else {
                rv = window.baye.hooks[name]();
            }
        }
        return rv;
    }, name, context);
}

int has_hook(const char* name) {
    return EM_ASM_INT({
        var name = UTF8ToString($0);
        if (window.baye && window.baye.hooks && window.baye.hooks[name]) {
            return 1;
        } else {
            return 0;
        }
    }, name);
}

