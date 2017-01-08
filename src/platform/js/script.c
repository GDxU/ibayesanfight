//
//  script.c
//  baye-ios
//
//  Created by loong on 16/9/17.
//
//

#include "baye/script.h"
#include "baye/bind-objects.h"
#include "baye/consdef.h"
#include "baye/datman.h"
#include "baye/extern.h"
#include "baye/sharefun.h"
#include "baye/comm.h"
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
            if (baye.data.g_asyncActionID > 0) {
                baye.data.g_asyncActionID = 0;
                alert("Invalid operation in hook " + name);
            }
        }
        return rv;
    }, name, context);
}

static int js_callback(void) {
    return EM_ASM_INT({
        if (baye.callback)
            return baye.callback();
        return 0;
    }, 0);
}

int call_hook_a(const char* name, Value* context)
{
    int rv = call_hook(name, context);

    if (rv) {
        if (g_asyncActionID) {
            printf("Error: %s return %d with async action %d\n", name, rv, g_asyncActionID);
        }
        return rv;
    }

    while (g_asyncActionID) {
        U16 action = g_asyncActionID;
        g_asyncActionID = 0;

        switch (action) {
            case 1: // alert
                GamMsgBox(g_asyncActionStringParam, g_asyncActionParams[0]);
                rv = js_callback();
                break;
            case 2: // say
                ShowGReport(g_asyncActionParams[0], g_asyncActionStringParam);
                rv = js_callback();
                break;
            case 3: // menu
                // TODO: 显示菜单
                break;
            default:
                break;
        }
    }
    return rv;
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

