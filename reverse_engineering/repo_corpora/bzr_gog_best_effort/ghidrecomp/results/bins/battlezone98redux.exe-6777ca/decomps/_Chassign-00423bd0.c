
/* Library Function - Single Match
    public: void __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::_Chassign(unsigned int,unsigned int,char)
   
   Libraries: Visual Studio 2010 Debug, Visual Studio 2010 Release, Visual Studio 2012 Debug, Visual
   Studio 2012 Release */

void __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::_Chassign
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1,uint param_2,char param_3)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  
  if (param_2 == 1) {
    pcVar2 = &param_3;
    pcVar1 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                       ((_String_val<struct_std::_Simple_types<char>_> *)this);
    FUN_00416350(pcVar1 + param_1,pcVar2);
  }
  else {
    cVar3 = param_3;
    pcVar2 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                       ((_String_val<struct_std::_Simple_types<char>_> *)this);
    char_traits<char>::assign(pcVar2 + param_1,param_2,cVar3);
  }
  return;
}

