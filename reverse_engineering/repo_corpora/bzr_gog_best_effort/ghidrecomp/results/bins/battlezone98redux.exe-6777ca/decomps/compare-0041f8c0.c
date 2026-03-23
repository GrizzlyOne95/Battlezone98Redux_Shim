
/* Library Function - Single Match
    public: int __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::compare(class std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> > const &)const 
   
   Library: Visual Studio 2003 Debug */

int __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::compare
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  int iVar3;
  
  uVar1 = FUN_004170c0();
  pcVar2 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                     ((_String_val<struct_std::_Simple_types<char>_> *)param_1);
  iVar3 = FUN_004227a0(0,*(undefined4 *)(this + 0x10),pcVar2,uVar1);
  return iVar3;
}

