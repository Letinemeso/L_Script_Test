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
    std::string m_string;
    unsigned int m_number = 0;

    LScript::Script_Stub* m_script_stub = nullptr;
    LScript::Script* m_script = nullptr;

public:
    void set_string(std::string _string)
    {
        m_string = _string;
    }

    void set_number(unsigned int _number)
    {
        m_number = _number;
    }

    void print_data()
    {
        std::cout << "m_string: " << m_string << std::endl;
        std::cout << "m_number: " << m_number << std::endl;
    }

    unsigned int number() const
    {
        return m_number;
    }

    LDS::Vector<unsigned int> numbers() const
    {
        LDS::Vector<unsigned int> vec;
        vec.push(m_number);
        vec.push(m_number);
        vec.push(m_number);
        vec.push(m_number);
        vec.push(m_number);
        return vec;
    }

public:
    Test()
    {
        SCRIPTABLE_FUNCTIONS_INITIALIZATION_BEGIN;

        SCRIPTABLE_FUNCTION_INITIALIZATION_BEGIN(Test);
        SCRIPTABLE_FUNCTION_RETURN_TYPE(void);
        SCRIPTABLE_FUNCTION_NAME(set_string);
        SCRIPTABLE_FUNCTION_ARG(std::string);
        SCRIPTABLE_FUNCTION_INITIALIZATION_END;

        SCRIPTABLE_FUNCTION_INITIALIZATION_BEGIN(Test);
        SCRIPTABLE_FUNCTION_RETURN_TYPE(void);
        SCRIPTABLE_FUNCTION_NAME(set_number);
        SCRIPTABLE_FUNCTION_ARG(unsigned int);
        SCRIPTABLE_FUNCTION_INITIALIZATION_END;

        SCRIPTABLE_FUNCTION_INITIALIZATION_BEGIN(Test);
        SCRIPTABLE_FUNCTION_RETURN_TYPE(void);
        SCRIPTABLE_FUNCTION_NAME(print_data);
        SCRIPTABLE_FUNCTION_INITIALIZATION_END;

        SCRIPTABLE_FUNCTION_INITIALIZATION_BEGIN(Test);
        SCRIPTABLE_FUNCTION_RETURN_TYPE(unsigned int);
        SCRIPTABLE_FUNCTION_NAME(number);
        SCRIPTABLE_FUNCTION_INITIALIZATION_END;

        SCRIPTABLE_FUNCTION_INITIALIZATION_BEGIN(Test);
        SCRIPTABLE_FUNCTION_RETURN_TYPE(LDS::Vector<unsigned int>);
        SCRIPTABLE_FUNCTION_NAME(numbers);
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
