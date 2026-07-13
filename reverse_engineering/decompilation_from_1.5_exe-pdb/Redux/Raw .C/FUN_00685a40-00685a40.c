
void FUN_00685a40(int param_1,int param_2,int param_3)

{
  short sVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  float fVar6;
  undefined4 *local_30;
  int local_2c;
  short *local_28;
  int local_24;
  
  iVar3 = (param_3 + -2) * 3;
  FUN_0067a110(param_3,iVar3);
  sVar1 = FUN_00684c10();
  fVar6 = *(float *)(param_1 + 0x10) / 1200.0;
  local_30 = (undefined4 *)FUN_0067a150(param_3);
  for (local_24 = 0; local_24 < param_3; local_24 = local_24 + 1) {
    uVar4 = (uint)*(byte *)(param_2 + 0x14 + local_24 * 0x18);
    uVar5 = (uint)*(byte *)(param_2 + 0x15 + local_24 * 0x18);
    puVar2 = (undefined4 *)
             FUN_00446360(*(float *)(param_2 + local_24 * 0x18) * fVar6,
                          *(float *)(param_2 + 4 + local_24 * 0x18) * fVar6,
                          -*(float *)(param_2 + 8 + local_24 * 0x18) * fVar6,
                          ((int)((uVar4 - DAT_02cd9120) * uVar5) / 0xff + (uint)DAT_02cd9120 & 0xff)
                          << 0x10 | 0xff000000 |
                          ((int)((uVar4 - DAT_02cd9121) * uVar5) / 0xff + (uint)DAT_02cd9121 & 0xff)
                          << 8 | (int)((uVar4 - DAT_02cd9122) * uVar5) / 0xff + (uint)DAT_02cd9122 &
                                 0xff,*(undefined4 *)(param_2 + 0xc + local_24 * 0x18),
                          *(undefined4 *)(param_2 + 0x10 + local_24 * 0x18));
    *local_30 = *puVar2;
    local_30[1] = puVar2[1];
    local_30[2] = puVar2[2];
    local_30[3] = puVar2[3];
    local_30[4] = puVar2[4];
    local_30[5] = puVar2[5];
    local_30 = local_30 + 6;
  }
  local_28 = (short *)FUN_0067a1e0(iVar3);
  for (local_2c = 2; local_2c < param_3; local_2c = local_2c + 1) {
    *local_28 = sVar1;
    local_28[1] = sVar1 + (short)local_2c;
    local_28[2] = sVar1 + -1 + (short)local_2c;
    local_28 = local_28 + 3;
  }
  FUN_0083e885();
  return;
}

