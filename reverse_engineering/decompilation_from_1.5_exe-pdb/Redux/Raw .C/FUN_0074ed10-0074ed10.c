
void FUN_0074ed10(char param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  undefined4 extraout_var;
  undefined4 local_8;
  
  FUN_007427f0(param_1,param_2,param_3);
  if (param_1 == '\0') {
    local_8 = 2;
  }
  else {
    local_8 = 1;
  }
  piVar1 = (int *)FUN_0074db30(local_8,extraout_var);
  (**(code **)(*piVar1 + 4))(local_8,8,1,4);
  return;
}

