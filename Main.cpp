#include <iostream>

#include <Stuff/Arguments_Container.h>

#include <Type_Manager.h>
#include <Object_Constructor.h>

#include <LScript_Registration.h>

#include <Script.h>
#include <Script_Details/Operations/Custom_Operation.h>
#include <Integrated_Functions.h>
#include <Scriptable_Functions_Registration.h>




// #define SCRIPTABLE_FUNCTION_ARGS_LIST_END \
//     > args_container;


template <typename _Owner_Type, typename _Return_Type, typename... _Arg_Types>
LST::Arguments_Container<_Arg_Types...> construct_args_container(_Return_Type(_Owner_Type::*_func)(_Arg_Types...))
{
    return LST::Arguments_Container<_Arg_Types...>();
}

class Test
{
public:
    void print_shit(int, bool)
    {
        std::cout << "shit" << std::endl;
    }

    void print_number(int _number)
    {
        std::cout << "printing number: " << _number << std::endl;
    }

    // DECLARE_FUNCTION(void scriptable_func(int, bool))

    Test()
    {
        SCRIPTABLE_FUNCTIONS_INITIALIZATION_BEGIN;

        SCRIPTABLE_FUNCTION_INITIALIZATION_BEGIN(Test);
        SCRIPTABLE_FUNCTION_NAME(print_shit);
        SCRIPTABLE_FUNCTION_ARG(int);
        SCRIPTABLE_FUNCTION_ARG(bool);
        SCRIPTABLE_FUNCTION_INITIALIZATION_END;

        SCRIPTABLE_FUNCTION_INITIALIZATION_BEGIN(Test);
        SCRIPTABLE_FUNCTION_NAME(print_number);
        SCRIPTABLE_FUNCTION_ARG(int);
        SCRIPTABLE_FUNCTION_INITIALIZATION_END;

        SCRIPTABLE_FUNCTIONS_INITIALIZATION_END;
    }
};




void test_func(int, bool)
{
    // std::cout << _int << ' ' << _bool << ' ' << _float << std::endl;
    std::cout << "aaa" << std::endl;
}


int main()
{
    // LST::Arguments_Container<int, bool> args_container;

    // void* ptr = nullptr;
    // args_container.init_pointer(0, ptr);

    // int* iptr = (int*)ptr;
    // *iptr = 213;

    // args_container.call_with_args(&test_func);


    // return 0;

    LV::Type_Manager::register_basic_types();
    LV::Object_Constructor object_constructor;

    LScript::register_types(object_constructor);

    LV::MDL_Reader reader;
    reader.parse_file("../Resources/Script_Test");

    LScript::Script_Stub* stub = (LScript::Script_Stub*)object_constructor.construct(reader.get_stub("Script_Test"));
    LScript::Script* script = LScript::Script_Stub::construct_from(stub);
    delete stub;

    // Test test;
    // script->set_context_object("Test", &test);

    int variable = 0;
    script->set_context_object("int", &variable);

    script->run();

    std::cout << "variable: " << variable << std::endl;

    delete script;


    return 0;
}
