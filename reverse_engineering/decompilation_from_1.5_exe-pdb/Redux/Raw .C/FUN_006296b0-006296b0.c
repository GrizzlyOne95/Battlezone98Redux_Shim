
void FUN_006296b0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  char cVar1;
  
  cVar1 = FUN_006268d0(*param_2,*param_1);
  if (cVar1 != '\0') {
    _Swap_adl<>(param_2,param_1);
  }
  cVar1 = FUN_006268d0(*param_3,*param_2);
  if (cVar1 != '\0') {
    _Swap_adl<>(param_3,param_2);
    cVar1 = FUN_006268d0(*param_2,*param_1);
    if (cVar1 != '\0') {
      _Swap_adl<>(param_2,param_1);
    }
  }
  return;
}

