#include <iostream>

#include <Stuff/Arguments_Container.h>

#include <Type_Manager.h>
#include <Object_Constructor.h>

#include <LScript_Registration.h>

#include <Script.h>
#include <Script_Details/Operations/Custom_Operation.h>
#include <Integrated_Functions.h>
#include <Scriptable_Functions_Registration.h>


class Test : public LV::Variable_Base
{
public:
    INIT_VARIABLE(Test, LV::Variable_Base)

    INIT_CHILDS
    ADD_CHILD("script_stub", m_script_stub);
    CHILDS_END

    OVERRIDE_ON_VALUES_ASSIGNED

private:
    using string = std::string;
    string m_string;

    LScript::Script_Stub* m_script_stub = nullptr;
    LScript::Script* m_script = nullptr;

public:
    void set_string(std::string _string)
    {
        m_string = _string;
    }

public:
    Test()
    {
        SCRIPTABLE_FUNCTIONS_INITIALIZATION_BEGIN;

        SCRIPTABLE_FUNCTION_INITIALIZATION_BEGIN(Test);
        SCRIPTABLE_FUNCTION_NAME(set_string);
        SCRIPTABLE_FUNCTION_ARG(string);
        SCRIPTABLE_FUNCTION_INITIALIZATION_END;

        SCRIPTABLE_FUNCTIONS_INITIALIZATION_END;
    }

    ~Test()
    {
        delete m_script;
        delete m_script_stub;
    }

    void test()
    {
        m_script->run();
        std::cout << "m_string: " << m_string << std::endl;
    }

};

ON_VALUES_ASSIGNED_IMPLEMENTATION(Test)
{
    m_script = LScript::Script_Stub::construct_from(m_script_stub);
    delete m_script_stub;
    m_script_stub = nullptr;

    m_script->set_context_object("Test", this);
}





int main()
{
    LV::Type_Manager::register_basic_types();
    LV::Object_Constructor object_constructor;

    LScript::register_types(object_constructor);

    object_constructor.register_type<Test>();

    LV::MDL_Reader reader;
    reader.parse_file("../Resources/Test_Test");

    Test* test = (Test*)object_constructor.construct(reader.get_stub("Test_Test"));

    test->test();

    delete test;

    return 0;
}
