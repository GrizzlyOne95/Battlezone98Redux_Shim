
void FUN_00625c50(undefined4 *param_1)

{
  float *pfVar1;
  double *pdVar2;
  float10 fVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 local_9c [24];
  undefined1 local_84 [12];
  undefined1 local_78 [12];
  double local_6c;
  double local_64;
  double local_5c;
  double local_54;
  double local_4c;
  float local_44;
  float local_40;
  float local_3c;
  double local_38;
  double local_30;
  double local_28;
  undefined4 local_20;
  undefined4 local_1c;
  undefined2 local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pfVar1 = (float *)FUN_004560b0(local_78,&stack0x00000008);
  local_14 = *pfVar1;
  local_10 = pfVar1[1];
  local_c = pfVar1[2];
  pdVar2 = (double *)FUN_00447f60(local_9c,&stack0x00000008);
  local_38 = *pdVar2 - (double)((DAT_02cd912c + DAT_02cd9124) * 0.5);
  local_30 = pdVar2[1] - (double)DAT_02ce99cc;
  local_28 = pdVar2[2] - (double)((DAT_02cd9130 + DAT_02cd9128) * 0.5);
  uVar6 = 0x14;
  uVar5 = 0;
  puVar4 = &local_20;
  local_64 = local_38 * 64.0 + 0.5;
  floor(local_64);
  FUN_0083f040(puVar4,uVar5,uVar6);
  FUN_00625310();
  uVar6 = 0xf;
  uVar5 = 0x14;
  puVar4 = &local_20;
  local_54 = local_30 * 64.0 + 0.5;
  floor(local_54);
  FUN_0083f040(puVar4,uVar5,uVar6);
  FUN_00625370();
  uVar6 = 0x14;
  uVar5 = 0x23;
  puVar4 = &local_20;
  local_5c = local_28 * 64.0 + 0.5;
  floor(local_5c);
  FUN_0083f040(puVar4,uVar5,uVar6);
  FUN_00625310();
  pfVar1 = (float *)FUN_004621a0(local_84,&local_14);
  local_14 = *pfVar1;
  local_10 = pfVar1[1];
  local_c = pfVar1[2];
  if (1.0 < local_14) {
    local_14 = 1.0;
  }
  if (local_14 < -1.0) {
    local_14 = -1.0;
  }
  if (1.0 < local_10) {
    local_10 = 1.0;
  }
  if (local_10 < -1.0) {
    local_10 = -1.0;
  }
  fVar3 = (float10)FUN_0046e0a0(local_14,local_c);
  local_40 = (float)fVar3;
  fVar3 = (float10)FUN_00608a60(local_10);
  local_44 = (float)fVar3;
  local_3c = -local_44;
  uVar6 = 0xd;
  uVar5 = 0x37;
  puVar4 = &local_20;
  local_4c = (double)((local_40 * 4095.0) / 3.1415927) + 0.5;
  floor(local_4c);
  FUN_0083f040(puVar4,uVar5,uVar6);
  FUN_00625310();
  uVar6 = 0xc;
  uVar5 = 0x44;
  puVar4 = &local_20;
  local_6c = (double)((local_3c * 4095.0) / 3.1415927) + 0.5;
  floor(local_6c);
  FUN_0083f040(puVar4,uVar5,uVar6);
  FUN_00625310();
  *param_1 = local_20;
  param_1[1] = local_1c;
  *(undefined2 *)(param_1 + 2) = local_18;
  FUN_0083e885();
  return;
}

