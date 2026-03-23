
void FUN_00625a30(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_c4 [64];
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  undefined4 local_60 [16];
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_006251e0(&stack0x00000008,0,0x14);
  local_14 = (float)iVar1 / 64.0;
  iVar1 = FUN_00625160(&stack0x00000008,0x14,0xf);
  local_10 = (float)iVar1 / 64.0;
  iVar1 = FUN_006251e0(&stack0x00000008,0x23,0x14);
  local_14 = (DAT_02cd912c + DAT_02cd9124) * 0.5 + local_14;
  local_10 = local_10 + DAT_02ce99cc;
  local_c = (DAT_02cd9130 + DAT_02cd9128) * 0.5 + (float)iVar1 / 64.0;
  iVar1 = FUN_006251e0(&stack0x00000008,0x37,0xd);
  local_68 = ((float)iVar1 * 3.1415927) / 4095.0;
  iVar1 = FUN_006251e0(&stack0x00000008,0x44,0xc);
  local_64 = ((float)iVar1 * 3.1415927) / 4095.0;
  fVar4 = (float10)FUN_004178f0(local_68);
  local_74 = (float)fVar4;
  local_70 = local_74;
  fVar4 = (float10)FUN_004178b0(local_64);
  local_78 = (float)fVar4;
  local_20 = local_70 * local_78;
  fVar4 = (float10)FUN_004178f0(local_64);
  local_80 = (float)fVar4;
  local_1c = -local_80;
  fVar4 = (float10)FUN_004178b0(local_68);
  local_84 = (float)fVar4;
  local_6c = local_84;
  fVar4 = (float10)FUN_004178b0(local_64);
  local_7c = (float)fVar4;
  local_18 = local_84 * local_7c;
  puVar2 = (undefined4 *)FUN_0081fa10(local_c4,&local_14,&local_20);
  puVar3 = local_60;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = local_60;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

