
undefined4 FUN_0075a090(int *param_1,int *param_2)

{
  undefined4 uVar1;
  
  if (*param_1 < *param_2) {
    uVar1 = 1;
  }
  else if (*param_2 < *param_1) {
    uVar1 = 0;
  }
  else if (*param_1 == 1) {
    uVar1 = FUN_00759eb0(param_1 + 2,param_2 + 2);
  }
  else {
    uVar1 = FUN_00759c00(param_1 + 1,param_2 + 1);
  }
  return uVar1;
}

