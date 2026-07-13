
/* Library Function - Multiple Matches With Same Base Name
    public: class std::_String_iterator<char,struct std::char_traits<char>,class
   std::allocator<char> > __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::end(void)
    public: class std::_String_iterator<class std::_String_val<struct std::_Simple_types<char> > >
   __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::end(void)
   
   Libraries: Visual Studio 2010 Release, Visual Studio 2012 Release */

undefined4 __thiscall
FUN_004fee40(_String_val<struct_std::_Simple_types<char>_> *param_1,undefined4 param_2)

{
  char *pcVar1;
  _String_val<struct_std::_Simple_types<char>_> *p_Var2;
  
  p_Var2 = param_1;
  pcVar1 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_1);
  _String_const_iterator<>(pcVar1 + *(int *)(param_1 + 0x10),p_Var2);
  return param_2;
}

