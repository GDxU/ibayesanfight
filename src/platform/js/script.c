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
            window.baye = {
                methods: {}
            };
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

int call_script(const char* name, Value* context)
{
    return EM_ASM_INT({
        var name = UTF8ToString($0);
        var rv = 0;

        if (window.baye == undefined || window.baye.methods == undefined || window.baye.methods[name] == undefined) {
            rv = -1;
        } else {
            var cContext = $1;
            if (cContext != 0) {
                var jsContext = baye_bridge_value(cContext);
                rv = window.baye.methods[name](jsContext);
            } else {
                rv = window.baye.methods[name]();
            }
        }
        return rv;
    }, name, context);
}

