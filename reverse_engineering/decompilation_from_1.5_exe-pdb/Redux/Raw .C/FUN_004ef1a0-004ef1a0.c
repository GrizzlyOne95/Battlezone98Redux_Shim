
void __fastcall FUN_004ef1a0(int param_1)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_00462490();
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  fVar2 = (float10)FUN_004428b0(&local_14,param_1 + 300);
  if ((float)fVar2 < -0.1) {
    *(undefined4 *)(*(int *)(param_1 + 0x230) + 0xd0) = 0x3f800000;
    *(undefined4 *)(*(int *)(param_1 + 0x230) + 0xc4) = 0;
  }
  FUN_0083e885();
  return;
}

