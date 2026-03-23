
void __thiscall FUN_005e4620(int param_1,undefined4 param_2)

{
  int iVar1;
  float10 fVar2;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x200) == 0) {
    iVar1 = FUN_00439e60();
    local_14 = (float)((double)*(float *)(param_1 + 0x108) - *(double *)(iVar1 + 0x160));
    local_10 = (float)((double)*(float *)(param_1 + 0x10c) - *(double *)(iVar1 + 0x168));
    local_c = (float)((double)*(float *)(param_1 + 0x110) - *(double *)(iVar1 + 0x170));
    fVar2 = (float10)FUN_004428b0(&local_14,&local_14);
    if (22500.0 <= (float)fVar2) {
      FUN_005e4740();
    }
    else {
      FUN_005e47c0(param_2);
    }
  }
  FUN_0083e885();
  return;
}

