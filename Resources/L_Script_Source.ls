void main()
{
    string& str_ref;

    ref_bind(str_ref, test.get_string());

    str_ref.set('textaaa');

    test.print_data();
}
