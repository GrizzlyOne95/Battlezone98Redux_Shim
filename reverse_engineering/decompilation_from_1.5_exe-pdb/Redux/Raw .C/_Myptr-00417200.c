
/* Library Function - Single Match
    public: char const * __thiscall std::_String_val<struct std::_Simple_types<char>
   >::_Myptr(void)const 
   
   Library: Visual Studio 2012 Release */

char * __thiscall
std::_String_val<struct_std::_Simple_types<char>_>::_Myptr
          (_String_val<struct_std::_Simple_types<char>_> *this)

{
  _String_val<struct_std::_Simple_types<char>_> *local_c;
  
  local_c = this;
  if (0xf < *(uint *)(this + 0x14)) {
    local_c = (_String_val<struct_std::_Simple_types<char>_> *)FUN_00417780(*(undefined4 *)this);
  }
  return (char *)local_c;
}

