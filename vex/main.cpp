#include "quickjs.h"
#include <iostream>

// Example C++ function
static JSValue hello(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    std::cout << "Hello from C++!" << std::endl;
    return JS_UNDEFINED;
}

int main() {
    JSRuntime *rt = JS_NewRuntime();
    JSContext *ctx = JS_NewContext(rt);

    // Register function as global JS "hello"
    JSValue global = JS_GetGlobalObject(ctx);
    JS_SetPropertyStr(ctx, global, "hello",
        JS_NewCFunction(ctx, hello, "hello", 0));
    JS_FreeValue(ctx, global);

    // Run some JS that calls hello()
    const char *script = "hello();";
    JS_Eval(ctx, script, strlen(script), "<input>", JS_EVAL_TYPE_GLOBAL);

    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    return 0;
}
