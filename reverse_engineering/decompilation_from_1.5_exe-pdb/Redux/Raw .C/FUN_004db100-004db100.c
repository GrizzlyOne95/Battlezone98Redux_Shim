
void __fastcall FUN_004db100(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  float *pfVar3;
  undefined4 *puVar4;
  float *pfVar5;
  undefined1 local_164 [64];
  float *local_124;
  float *local_120;
  float *local_11c;
  float *local_118;
  float *local_114;
  float *local_110;
  int local_10c;
  float local_108 [16];
  undefined4 local_c8 [16];
  float local_88 [16];
  float local_48 [4];
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(int *)(param_1 + 0xf0) == 0) {
    local_11c = (float *)(*(int *)(param_1 + 0xf4) + 0xa0);
  }
  else {
    local_11c = (float *)(*(int *)(param_1 + 0xf0) + 8);
  }
  local_120 = local_11c;
  local_114 = local_11c;
  local_10c = param_1;
  if (*(int *)(param_1 + 0xf0) == 0) {
    puVar1 = (undefined4 *)FUN_0062e070(local_164,*(undefined4 *)(param_1 + 0xf4),0);
    puVar4 = local_c8;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar4 = puVar4 + 1;
    }
    pfVar3 = (float *)local_c8;
    pfVar5 = local_88;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar5 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar5 = pfVar5 + 1;
    }
    local_118 = local_88;
  }
  else {
    pfVar3 = (float *)(*(int *)(param_1 + 0xf4) + 0x20);
    pfVar5 = local_108;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar5 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar5 = pfVar5 + 1;
    }
    local_118 = local_108;
  }
  local_124 = local_118;
  pfVar3 = local_118;
  pfVar5 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar5 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar5 = pfVar5 + 1;
  }
  local_110 = local_48;
  *(float *)(local_10c + 0x108) =
       (float)((double)(*local_114 * local_48[0] + local_114[1] * local_48[3] +
                       local_114[2] * local_30) + local_20);
  *(float *)(local_10c + 0x10c) =
       (float)((double)(*local_114 * local_48[1] + local_114[1] * local_38 + local_114[2] * local_2c
                       ) + local_18);
  *(float *)(local_10c + 0x110) =
       (float)((double)(*local_114 * local_48[2] + local_114[1] * local_34 + local_114[2] * local_28
                       ) + local_10);
  if (*(int *)(local_10c + 0xf0) != 0) {
    *(float *)(*(int *)(local_10c + 0xf0) + 0x44) =
         *(float *)(local_10c + 0x108) - *(float *)(*(int *)(local_10c + 0xf0) + 0x14);
    *(float *)(*(int *)(local_10c + 0xf0) + 0x50) =
         *(float *)(local_10c + 0x108) + *(float *)(*(int *)(local_10c + 0xf0) + 0x14);
    *(float *)(*(int *)(local_10c + 0xf0) + 0x48) =
         *(float *)(local_10c + 0x10c) - *(float *)(*(int *)(local_10c + 0xf0) + 0x14);
    *(float *)(*(int *)(local_10c + 0xf0) + 0x54) =
         *(float *)(local_10c + 0x10c) + *(float *)(*(int *)(local_10c + 0xf0) + 0x14);
    *(float *)(*(int *)(local_10c + 0xf0) + 0x4c) =
         *(float *)(local_10c + 0x110) - *(float *)(*(int *)(local_10c + 0xf0) + 0x14);
    *(float *)(*(int *)(local_10c + 0xf0) + 0x58) =
         *(float *)(local_10c + 0x110) + *(float *)(*(int *)(local_10c + 0xf0) + 0x14);
    FUN_00680bd0(*(undefined4 *)(local_10c + 0xf0));
  }
  FUN_0083e885();
  return;
}

