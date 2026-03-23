
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
   & __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::assign(char const *,unsigned int)
   
   Library: Visual Studio 2012 Release */

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          char *param_1,uint param_2)

{
  bool bVar1;
  char *pcVar2;
  uint uVar3;
  
  bVar1 = _Inside(this,param_1);
  if (bVar1) {
    pcVar2 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                       ((_String_val<struct_std::_Simple_types<char>_> *)this);
    this = assign(this,this,(int)param_1 - (int)pcVar2,param_2);
  }
  else {
    bVar1 = _Grow(this,param_2,false);
    if (bVar1) {
      uVar3 = param_2;
      pcVar2 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)this);
      char_traits<char>::copy(pcVar2,param_1,uVar3);
      basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
                ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
                  *)this,param_2);
    }
  }
  return this;
}

