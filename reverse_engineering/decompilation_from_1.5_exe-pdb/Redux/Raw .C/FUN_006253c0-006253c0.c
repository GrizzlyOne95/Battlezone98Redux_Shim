
void FUN_006253c0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_98 [64];
  undefined4 local_58 [10];
  double local_30;
  double local_28;
  double local_20;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_006251e0(&stack0x00000008,0,0xf);
  local_18 = (float)iVar1 / 16383.0;
  iVar1 = FUN_006251e0(&stack0x00000008,0xf,0xf);
  local_14 = (float)iVar1 / 16383.0;
  iVar1 = FUN_006251e0(&stack0x00000008,0x1e,0xf);
  local_10 = (float)iVar1 / 16383.0;
  local_c = ((1.0 - local_18 * local_18) - local_14 * local_14) - local_10 * local_10;
  if (local_c <= 0.0) {
    local_c = 0.0;
  }
  else {
    fVar4 = (float10)FUN_00417910(local_c);
    local_c = (float)fVar4;
  }
  FUN_004dead0(&local_18);
  puVar2 = (undefined4 *)FUN_0081efe0(local_98,&local_18);
  puVar3 = local_58;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  iVar1 = FUN_006251e0(&stack0x00000008,0x2d,0x18);
  local_30 = (double)iVar1 / 1024.0;
  iVar1 = FUN_00625160(&stack0x00000008,0x45,0x13);
  local_28 = (double)iVar1 / 1024.0;
  iVar1 = FUN_006251e0(&stack0x00000008,0x58,0x18);
  local_30 = (double)(DAT_02cd912c + DAT_02cd9124) * 0.5 + local_30;
  local_28 = (double)DAT_02ce99cc + local_28;
  local_20 = (double)(DAT_02cd9130 + DAT_02cd9128) * 0.5 + (double)iVar1 / 1024.0;
  puVar2 = local_58;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

