#include <iostream>

#include <Test.h>

#include <pybind11/embed.h>


#include <Python_Script/Python_Script_Engine.h>



int main()
{
    srand(time(nullptr));

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
