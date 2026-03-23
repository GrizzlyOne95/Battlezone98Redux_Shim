
void __thiscall FUN_004ef0c0(int param_1,float param_2)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(int *)(param_1 + 0x2a8) != 0) {
    *(float *)(*(int *)(param_1 + 0x2a8) + 100) = param_2;
  }
  puVar1 = (undefined4 *)FUN_00462490();
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  fVar2 = (float10)FUN_004428b0(&local_14,param_1 + 300);
  fVar2 = (float10)FUN_00447ed0((param_2 - (float)fVar2) * 0.2,0xbf800000,0x3f800000);
  *(float *)(*(int *)(param_1 + 0x230) + 0xd0) = (float)fVar2;
  *(undefined4 *)(*(int *)(param_1 + 0x230) + 0xcc) = 0;
  FUN_0083e885();
  return;
}

