#include "quickjs.h"
#include <iostream>

#define AMOUNT_OF_PORTS 21

// Example C++ function
static JSValue hello(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    std::cout << "Hello from C++!" << std::endl;
    return JS_UNDEFINED;
}


/**
* takes at most  2 args
* the first one being whch motor
*/
/*
JS_IsUndefined(v): Returns true if v is undefined.
JS_IsNull(v): Returns true if v is null.
JS_IsNumber(v): Returns true if v is a number (integer or float).
JS_IsString(v): Returns true if v is a string.
JS_IsBool(v): Returns true if v is a boolean.
JS_IsObject(v): Returns true if v is an object.
JS_IsFunction(ctx, v): Returns true if v is a function.
JS_IsArray(ctx, v): Returns true if v is an array.
JS_IsException(v): Returns true if v is an exception, which is crucial for error handling. 
*/ 
static JsValue moveMotor (JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc > 2) {
        std::cout << "Error - to many arguments in the `moveMotor` function call" << std::endl;
        return -1;
    } 
    else {
        if (!(JS_IsUndefined(argv[0]) || JS_IsNull(argv[0]) || JS_IsException(argv[0]))) {
            std::cout << "Error - argument in the `moveMotor` function call - not true value"
        } else {
            if (JS_IsNumber(argv[0])) goto _number;
            else if (JS_IsString(argv[0])) goto _string;
            else if (JS_IsBool(argv[0])) goto _boolean;
            
            else {
                std::cout << "Error - tyoe of argument in the `moveMotor` function call is invalid"
                return -1;
            }
        }
    }
_number:
    if (argv[0] > 0 && argv[0] < AMOUNT_OF_PORTS) {
        
    }
_string:
    
_boolean:
    
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
