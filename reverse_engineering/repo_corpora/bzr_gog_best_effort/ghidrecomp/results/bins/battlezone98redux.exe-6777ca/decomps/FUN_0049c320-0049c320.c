
float10 FUN_0049c320(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_8;
  
  local_8 = *(float *)(param_1 + 8);
  iVar1 = param_1;
  while (param_1 = iVar1, param_2 = param_2 + -1, param_2 != 0) {
    iVar1 = param_1 + 0xc;
    if (*(float *)(param_1 + 0x14) <= local_8 && local_8 != *(float *)(param_1 + 0x14)) {
      local_8 = *(float *)(param_1 + 0x14);
    }
  }
  return (float10)local_8;
}

