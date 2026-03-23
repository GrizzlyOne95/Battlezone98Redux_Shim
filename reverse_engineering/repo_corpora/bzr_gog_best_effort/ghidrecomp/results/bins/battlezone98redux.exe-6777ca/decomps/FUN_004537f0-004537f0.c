
void FUN_004537f0(undefined4 param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_b4 [16];
  float local_a4;
  int local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  float local_94;
  float local_90;
  float local_8c;
  int local_88;
  float local_84;
  int local_80;
  float local_7c;
  float local_74;
  int local_70;
  int local_6c;
  int local_68;
  undefined4 *local_64;
  undefined4 local_60;
  int local_5c;
  int local_58;
  short *local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00447e20();
  while( true ) {
    iVar3 = FUN_00447e70();
    FUN_00447e50();
    iVar4 = FUN_00447e70();
    if (iVar3 == iVar4) break;
    local_a0 = FUN_00447e70();
    local_68 = local_a0;
    FUN_00447e90();
    if (*(char *)(local_68 + 0x1c) != '\0') {
      fVar7 = (float10)FUN_00447ed0();
      local_a4 = (float)fVar7;
      local_70 = FUN_00453d10();
      local_98 = *(undefined4 *)(local_5c + 0x1a4 + local_70 * 8);
      local_9c = *(undefined4 *)(local_5c + local_70 * 8 + 0x1a8);
      local_8c = *(float *)(local_5c + 0x9a4 + local_70 * 8);
      local_7c = *(float *)(local_5c + local_70 * 8 + 0x9a8);
      pfVar5 = (float *)FUN_006897e0(local_b4,param_1,*(undefined8 *)(local_68 + 0x48),
                                     *(undefined8 *)(local_68 + 0x50),
                                     *(undefined8 *)(local_68 + 0x58));
      local_50 = *pfVar5;
      local_4c = pfVar5[1];
      local_48 = pfVar5[2];
      local_14 = local_50;
      local_10 = local_4c;
      local_c = local_48;
      iVar3 = FUN_006895d0();
      if (iVar3 < 1) {
        local_88 = *(int *)(local_5c + 0x1a0) * 2 + 2;
        local_80 = *(int *)(local_5c + 0x1a0) * 6;
        FUN_006855e0(local_5c + 0x144,local_48);
        local_60 = FUN_00685670(local_88,local_80);
        local_64 = (undefined4 *)FUN_006856a0();
        local_54 = (short *)FUN_006856c0();
        local_74 = 0.0;
        local_94 = 6.2831855 / (float)*(int *)(local_5c + 0x1a0);
        for (local_6c = 0; local_6c <= *(int *)(local_5c + 0x1a0); local_6c = local_6c + 1) {
          fVar7 = (float10)FUN_004178f0();
          local_84 = (float)fVar7;
          fVar7 = (float10)FUN_004178b0();
          local_90 = (float)fVar7;
          local_74 = local_74 + local_94;
          puVar6 = (undefined4 *)
                   FUN_00446360(local_90 * local_7c + local_50,local_84 * local_7c + local_4c,
                                -local_48,local_9c,(float)local_6c,0);
          *local_64 = *puVar6;
          local_64[1] = puVar6[1];
          local_64[2] = puVar6[2];
          local_64[3] = puVar6[3];
          local_64[4] = puVar6[4];
          local_64[5] = puVar6[5];
          local_64 = local_64 + 6;
          puVar6 = (undefined4 *)
                   FUN_00446360(local_90 * local_8c + local_50,local_84 * local_8c + local_4c,
                                -local_48,local_98,(float)local_6c,0x3f800000);
          *local_64 = *puVar6;
          local_64[1] = puVar6[1];
          local_64[2] = puVar6[2];
          local_64[3] = puVar6[3];
          local_64[4] = puVar6[4];
          local_64[5] = puVar6[5];
          local_64 = local_64 + 6;
        }
        for (local_58 = 0; local_58 < local_80; local_58 = local_58 + 1) {
          sVar1 = (short)local_60;
          sVar2 = (short)local_58;
          *local_54 = sVar1 + sVar2 * 2;
          local_54[1] = sVar1 + sVar2 * 2 + 2;
          local_54[2] = sVar1 + sVar2 * 2 + 1;
          local_54[3] = sVar1 + sVar2 * 2 + 3;
          local_54[4] = sVar1 + sVar2 * 2 + 1;
          local_54[5] = sVar1 + sVar2 * 2 + 2;
          local_54 = local_54 + 6;
        }
        FUN_006856e0();
      }
    }
  }
  FUN_0083e885();
  return;
}

