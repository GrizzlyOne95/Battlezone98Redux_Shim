
/* Library Function - Single Match
    public: wchar_t & __thiscall std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class
   std::allocator<wchar_t> >::back(void)
   
   Libraries: Visual Studio 2012 Release, Visual Studio 2015 Release */

wchar_t * __thiscall
std::basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::back
          (basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
           *this)

{
  _String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_> *this_00;
  wchar_t *pwVar1;
  undefined1 *puVar2;
  undefined1 local_c [4];
  basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_> *local_8;
  
  puVar2 = local_c;
  local_8 = this;
  this_00 = (_String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_> *)
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
                      ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        *)this);
  _String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_>::operator-
            (this_00,(int)puVar2);
  pwVar1 = (wchar_t *)FUN_00421ec0();
  return pwVar1;
}

