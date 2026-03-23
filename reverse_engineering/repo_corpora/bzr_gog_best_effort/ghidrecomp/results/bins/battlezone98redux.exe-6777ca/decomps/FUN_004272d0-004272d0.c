
void FUN_004272d0(int *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = std::basic_ios<char,struct_std::char_traits<char>_>::widen
                    ((basic_ios<char,struct_std::char_traits<char>_> *)
                     ((int)param_1 + *(int *)(*param_1 + 4)),'\n');
  uVar2 = FUN_00417780(param_1,param_2,cVar1);
  FUN_0042aad0(uVar2);
  return;
}

