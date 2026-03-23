
/* Library Function - Single Match
    public: class std::_String_iterator<class std::_String_val<struct std::_Simple_types<char> > >
   __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::end(void)
   
   Library: Visual Studio 2012 Release */

undefined4 __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this)

{
  char *pcVar1;
  undefined4 in_stack_00000004;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  
  pbVar2 = this;
  pcVar1 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                     ((_String_val<struct_std::_Simple_types<char>_> *)this);
  _String_iterator<>(pcVar1 + *(int *)(this + 0x10),pbVar2);
  return in_stack_00000004;
}

