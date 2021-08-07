
export module ModuleBasic;

#define ANSWER 42

//export void MyFunc();

namespace Bar
{
    int f_internal() {
        return ANSWER;
    }

    export int f() {
        return f_internal();
    }
}