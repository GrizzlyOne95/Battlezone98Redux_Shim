
/* Library Function - Single Match
    public: int __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::compare(char const *)const 
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2005 Debug */

int __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::compare
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          char *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_00416290(param_1);
  iVar2 = FUN_004227a0(0,*(undefined4 *)(this + 0x10),param_1,uVar1);
  return iVar2;
}

