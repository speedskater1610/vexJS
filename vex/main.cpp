#include "quickjs.h"
#include "vex.h"
#include <iostream>
#include <string>

#define AMOUNT_OF_PORTS 21

using namespace vex;

// Declare a motor array so JS can access by port number
motor *motors[AMOUNT_OF_PORTS];

// Example C++ function
static JSValue hello(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    std::cout << "Hello from C++!" << std::endl;
    return JS_UNDEFINED;
}

/**
 * moveMotor(port, velocity?)
 * port: number | string (0–20 or "1"–"20")
 * velocity: optional number (percentage)
 */
static JSValue moveMotor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    if (argc < 1 || argc > 2) {
        std::cout << "Error - invalid number of arguments in moveMotor" << std::endl;
        return JS_EXCEPTION;
    }

    int port = -1;

    // Port argument
    if (JS_IsNumber(argv[0])) {
        int32_t val;
        JS_ToInt32(ctx, &val, argv[0]);
        port = val;
    } else if (JS_IsString(argv[0])) {
        const char *str = JS_ToCString(ctx, argv[0]);
        if (str) {
            port = std::stoi(str);
            JS_FreeCString(ctx, str);
        }
    } else {
        std::cout << "Error - invalid port argument type" << std::endl;
        return JS_EXCEPTION;
    }

    if (port < 1 || port >= AMOUNT_OF_PORTS) {
        std::cout << "Error - port out of range (1-" << AMOUNT_OF_PORTS - 1 << ")" << std::endl;
        return JS_EXCEPTION;
    }

    // Velocity (optional)
    int velocity = 50; // default percent
    if (argc == 2) {
        if (!JS_IsNumber(argv[1])) {
            std::cout << "Error - velocity must be a number" << std::endl;
            return JS_EXCEPTION;
        }
        JS_ToInt32(ctx, &velocity, argv[1]);
    }

    if (!motors[port]) {
        motors[port] = new motor(static_cast<port>(port));
    }

    motors[port]->spin(fwd, velocity, pct);
    std::cout << "Motor " << port << " spinning at " << velocity << "%" << std::endl;

    return JS_UNDEFINED;
}

int main() {
    // Initialize VEX system (brain/screen optional)
    vexcodeInit();

    // Setup QuickJS
    JSRuntime *rt = JS_NewRuntime();
    JSContext *ctx = JS_NewContext(rt);

    JSValue global = JS_GetGlobalObject(ctx);

    // Expose functions
    JS_SetPropertyStr(ctx, global, "hello",
        JS_NewCFunction(ctx, hello, "hello", 0));
    JS_SetPropertyStr(ctx, global, "moveMotor",
        JS_NewCFunction(ctx, moveMotor, "moveMotor", 2));

    JS_FreeValue(ctx, global);

    // Example script
    const char *script = R"(
        hello();
        moveMotor(1, 75); // spin motor on port 1 at 75%
    )";

    JSValue result = JS_Eval(ctx, script, strlen(script), "<input>", JS_EVAL_TYPE_GLOBAL);

    if (JS_IsException(result)) {
        JSValue exc = JS_GetException(ctx);
        const char *err = JS_ToCString(ctx, exc);
        std::cerr << "JS Exception: " << err << std::endl;
        JS_FreeCString(ctx, err);
        JS_FreeValue(ctx, exc);
    }
    JS_FreeValue(ctx, result);

    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

    return 0;
}
