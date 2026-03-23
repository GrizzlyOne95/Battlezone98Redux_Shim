
float10 FUN_0062dd20(undefined4 param_1,undefined4 param_2)

{
  float fVar1;
  int iVar2;
  int local_8;
  
  iVar2 = FUN_0062dc80(&param_1,&param_2);
  local_8 = FUN_0062d8d0(param_1,param_2);
  if (local_8 == 0) {
    local_8 = FUN_0062d940(param_1,param_2);
  }
  if (iVar2 == 0) {
    fVar1 = *(float *)(local_8 + 0x10);
  }
  else {
    fVar1 = *(float *)(local_8 + 0x14);
  }
  return (float10)fVar1;
}

