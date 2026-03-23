
uint FUN_006b3430(int *param_1,int *param_2)

{
  uint uVar1;
  
  if (*param_1 == *param_2) {
    if (*param_1 == 1) {
      uVar1 = FUN_006b30d0(param_1 + 2,param_2 + 2);
    }
    else {
      uVar1 = eq_int_type(param_1 + 1,param_2 + 1);
    }
  }
  else {
    uVar1 = (uint)param_1 & 0xffffff00;
  }
  return uVar1;
}

