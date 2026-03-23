
undefined4 FUN_00783840(undefined4 param_1,int param_2)

{
  float *pfVar1;
  float10 fVar2;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (4 < local_8) {
      return 1;
    }
    fVar2 = (float10)FUN_004428b0(local_8 * 0x10 + param_2,param_1);
    pfVar1 = (float *)(param_2 + 0xc + local_8 * 0x10);
    if (*pfVar1 <= (float)fVar2 && (float)fVar2 != *pfVar1) break;
    local_8 = local_8 + 1;
  }
  return 0;
}

