
float10 FUN_0058d590(int param_1,int param_2,float param_3)

{
  float10 fVar1;
  undefined4 local_8;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    fVar1 = (float10)1e+30;
  }
  else {
    fVar1 = (float10)FUN_0058d4c0(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x28),
                                  *(undefined4 *)(param_2 + 0x24),*(undefined4 *)(param_2 + 0x28));
    local_8 = (float)fVar1;
    if (DAT_02a13c79 != '\0') {
      fVar1 = (float10)FUN_004464c0();
      local_8 = local_8 + local_8 * 0.2 * (float)fVar1;
    }
    fVar1 = (float10)(local_8 * param_3);
  }
  return fVar1;
}

