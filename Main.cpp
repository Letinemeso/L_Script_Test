#include <Type_Manager.h>
#include <Object_Constructor.h>

#include <LScript_Registration.h>


int main()
{
    LV::Type_Manager::register_basic_types();
    LV::Object_Constructor object_constructor;

    LScript::register_types(object_constructor);

    return 0;
}
