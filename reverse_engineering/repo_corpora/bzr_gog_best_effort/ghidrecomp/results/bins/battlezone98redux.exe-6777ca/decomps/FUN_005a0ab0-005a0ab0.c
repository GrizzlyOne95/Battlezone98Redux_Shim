
void __fastcall FUN_005a0ab0(int param_1)

{
  int iVar1;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((*(uint *)(*(int *)(param_1 + 0x230) + 0x114) & 4) != 0) {
    iVar1 = FUN_00439e60();
    local_14 = (float)((double)*(float *)(param_1 + 0x108) - *(double *)(iVar1 + 0x160));
    local_10 = (float)((double)*(float *)(param_1 + 0x10c) - *(double *)(iVar1 + 0x168));
    local_c = (float)((double)*(float *)(param_1 + 0x110) - *(double *)(iVar1 + 0x170));
    FUN_004428b0(&local_14,&local_14);
  }
  FUN_0083e885();
  return;
}

