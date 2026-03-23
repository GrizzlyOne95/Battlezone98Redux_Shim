
void __fastcall FUN_0048a570(int *param_1)

{
  int iVar1;
  
  iVar1 = FUN_00423210();
  if (iVar1 == 0) {
    std::basic_ios<char,struct_std::char_traits<char>_>::setstate
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               ((int)param_1 + *(int *)(*param_1 + 4)),2,false);
  }
  return;
}

