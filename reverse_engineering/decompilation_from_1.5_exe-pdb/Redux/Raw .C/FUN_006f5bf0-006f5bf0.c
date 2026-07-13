
undefined4 __thiscall
FUN_006f5bf0(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,undefined4 param_2,
            undefined4 param_3)

{
  char *pcVar1;
  undefined4 uVar2;
  
  FUN_006cef30(param_3);
  pcVar1 = std::basic_streambuf<char,struct_std::char_traits<char>_>::pptr(param_1);
  uVar2 = FUN_00416430(pcVar1,param_3);
  FUN_006ae410(param_2,uVar2);
  return param_2;
}

