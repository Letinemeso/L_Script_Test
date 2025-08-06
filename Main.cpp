#include <Type_Manager.h>
#include <Object_Constructor.h>

#include <LScript_Registration.h>

#include <Script.h>


int main()
{
    LV::Type_Manager::register_basic_types();
    LV::Object_Constructor object_constructor;

    LScript::register_types(object_constructor);


    LV::MDL_Reader reader;
    reader.parse_file("../Resources/Script_Test");

    LScript::Script_Stub* stub = (LScript::Script_Stub*)object_constructor.construct(reader.get_stub("Script_Test"));
    LScript::Script* script = LScript::Script_Stub::construct_from(stub);
    delete stub;

    script->run();

    delete script;


    return 0;
}
