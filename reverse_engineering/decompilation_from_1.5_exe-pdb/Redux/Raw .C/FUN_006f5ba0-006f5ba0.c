
undefined4 __thiscall
FUN_006f5ba0(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,undefined4 param_2)

{
  char *pcVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
  pcVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  iVar4 = (int)pcVar1 - (int)pcVar2;
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  uVar3 = FUN_00416430(pcVar1,iVar4);
  FUN_006ae410(param_2,uVar3);
  return param_2;
}

