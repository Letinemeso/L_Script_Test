#include <iostream>

#include <Stuff/Arguments_Container.h>

#include <Type_Manager.h>
#include <Object_Constructor.h>

#include <LScript_Registration.h>

#include <Script.h>
#include <Script_Details/Operations/Custom_Operation.h>
#include <Integrated_Functions.h>

#define INIT_SCRIPTABLE_FUNCTION(OWNER_CLASS) \
    { \
    using Scriptable_Function_Owner = OWNER_CLASS; \
    std::string scriptable_function_owner_name = #OWNER_CLASS

#define SCRIPTABLE_FUNCTION_NAME(FUNCTION_NAME) \
    auto member_function = &Scriptable_Function_Owner::FUNCTION_NAME; \
    std::string member_function_name = #FUNCTION_NAME; \
    using Arguments_Container = decltype(construct_args_container(member_function)); \
    LScript::Function::Arguments_Data arguments_data; \
    arguments_data.push({"Test", "this", true})

#define SCRIPTABLE_FUNCTION_ARG(TYPE) \
    arguments_data.push({#TYPE, "_" + std::to_string(arguments_data.size() - 1), false})

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

    // DECLARE_FUNCTION(void scriptable_func(int, bool))

    Test()
    {
        static bool __scriptable_functions_initialized = false;
        if(!__scriptable_functions_initialized)
        {
            INIT_SCRIPTABLE_FUNCTION(Test);
            SCRIPTABLE_FUNCTION_NAME(print_shit);
            SCRIPTABLE_FUNCTION_ARG(int);
            SCRIPTABLE_FUNCTION_ARG(bool);

                LScript::Function* function = new LScript::Function;

                LScript::Custom_Operation* call_scriptable_function_operation = new LScript::Custom_Operation;
                call_scriptable_function_operation->set_operation_logic([scriptable_function_owner_name, function, member_function]()
                {
                    Arguments_Container args_container;

                    for(unsigned int i = 0; i < args_container.arguments_amount(); ++i)
                    {
                        char* arg_raw = nullptr;
                        args_container.init_pointer(i, arg_raw);

                        LScript::Variable* variable = function->compound_statement().context().get_variable("_" + std::to_string(i));
                        L_ASSERT(variable);

                        char* variable_raw = (char*)variable->data();
                        for(unsigned int byte = 0; byte < variable->raw_size(); ++byte)
                            arg_raw[byte] = variable_raw[byte];
                    }

                    LScript::Variable* context_object_variable = function->compound_statement().context().get_variable("this");
                    L_ASSERT(context_object_variable);
                    L_ASSERT(scriptable_function_owner_name == context_object_variable->type());
                    Scriptable_Function_Owner* context_object = (Scriptable_Function_Owner*)context_object_variable->data();

                    args_container.call_with_args(*context_object, member_function);

                    return nullptr;
                });

                L_ASSERT(arguments_data.size() == Arguments_Container::arguments_amount() + 1);

                function->compound_statement().add_operation(call_scriptable_function_operation);
                function->set_expected_arguments_data(arguments_data);

                LScript::Integrated_Functions::instance().register_member_function(scriptable_function_owner_name, member_function_name, function);
            }
        }
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

    Test test;
    script->set_context_object("Test", &test);

    script->run();

    delete script;


    return 0;
}
