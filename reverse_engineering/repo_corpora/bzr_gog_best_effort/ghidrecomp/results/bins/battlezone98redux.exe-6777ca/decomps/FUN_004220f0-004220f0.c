
void __thiscall FUN_004220f0(int *param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = FUN_00423150(param_2,param_3 | 1,param_4);
  if (iVar1 == 0) {
    std::basic_ios<char,struct_std::char_traits<char>_>::setstate
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               ((int)param_1 + *(int *)(*param_1 + 4)),2,false);
  }
  else {
    std::basic_ios<char,struct_std::char_traits<char>_>::clear
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               ((int)param_1 + *(int *)(*param_1 + 4)),0,false);
  }
  return;
}

