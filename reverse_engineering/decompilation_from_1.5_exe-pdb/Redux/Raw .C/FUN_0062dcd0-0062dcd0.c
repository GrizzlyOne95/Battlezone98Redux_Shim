
float10 FUN_0062dcd0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int local_8;
  
  uVar1 = FUN_0062dc80(&param_1,&param_2);
  local_8 = FUN_0062d8d0(param_1,param_2,uVar1);
  if (local_8 == 0) {
    local_8 = FUN_0062d940(param_1,param_2);
  }
  return (float10)*(float *)(local_8 + 8);
}

