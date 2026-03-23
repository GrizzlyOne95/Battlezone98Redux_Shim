
void FUN_0068a6f0(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5,
                 int param_6)

{
  float fVar1;
  float fVar2;
  undefined4 *puVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  float10 fVar7;
  float fVar8;
  float local_6c;
  int local_68;
  float local_64;
  float local_58;
  int local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 auStack_38 [12];
  uint local_8;
  
  iVar6 = DAT_02bf0434;
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar3 = (undefined4 *)FUN_00440300();
  local_50 = *puVar3;
  local_4c = puVar3[1];
  local_48 = puVar3[2];
  fVar1 = *(float *)(&DAT_008ed6ec + DAT_02bf0428 * 0x14);
  fVar2 = *(float *)(&DAT_008ed6f0 + DAT_02bf0428 * 0x14);
  iVar4 = FUN_0068a110();
  if (iVar4 == 1) {
    iVar6 = FUN_004978d0();
    if (iVar6 == 0) {
      for (local_54 = 0; local_54 < param_6; local_54 = local_54 + 1) {
        fVar7 = (float10)FUN_0068a0c0();
        *(float *)(param_1 + local_54 * 4) = (float)fVar7 * 0.7 + 0.3;
      }
    }
    else {
      for (local_54 = 0; local_54 < param_6; local_54 = local_54 + 1) {
        *(undefined4 *)(param_1 + local_54 * 4) = 0x3e99999a;
      }
    }
  }
  else {
    for (local_54 = 0; local_54 < iVar6; local_54 = local_54 + 1) {
      puVar3 = (undefined4 *)FUN_00440300();
      auStack_38[local_54 * 3] = *puVar3;
      auStack_38[local_54 * 3 + 1] = puVar3[1];
      auStack_38[local_54 * 3 + 2] = puVar3[2];
    }
    for (local_54 = 0; local_54 < param_6; local_54 = local_54 + 1) {
      fVar7 = (float10)FUN_004428b0(&local_50,local_54 * 0xc + param_3);
      local_58 = (float)fVar7 * -fVar1;
      if (local_58 < 0.0) {
        local_58 = 0.0;
      }
      for (local_68 = 0; local_68 < iVar6; local_68 = local_68 + 1) {
        iVar4 = (&DAT_02bf0438)[local_68];
        local_44 = *(float *)(param_2 + local_54 * 0xc) - *(float *)(iVar4 + 0x48);
        local_40 = *(float *)(param_2 + 4 + local_54 * 0xc) - *(float *)(iVar4 + 0x4c);
        local_3c = *(float *)(param_2 + 8 + local_54 * 0xc) - *(float *)(iVar4 + 0x50);
        local_6c = 1.0 / ((local_44 * local_44 + local_40 * local_40 + local_3c * local_3c) *
                          *(float *)(iVar4 + 0xc) + 1.0);
        if ((*(uint *)(iVar4 + 4) & 1) == 0) {
          fVar7 = (float10)FUN_00417910();
          fVar8 = 1.0 / ((float)fVar7 + 0.5);
          local_44 = local_44 * fVar8;
          local_40 = local_40 * fVar8;
          local_3c = local_3c * fVar8;
          pfVar5 = (float *)FUN_00440300();
          local_44 = *pfVar5;
          local_40 = pfVar5[1];
          local_3c = pfVar5[2];
          fVar7 = (float10)FUN_004428b0(&local_44,local_54 * 0xc + param_3);
          local_64 = (float)fVar7 * local_6c;
          if (local_64 < 0.0) {
            local_64 = 0.0;
          }
        }
        else {
          fVar7 = (float10)FUN_004428b0(auStack_38 + local_68 * 3,local_54 * 0xc + param_3);
          local_64 = -(float)fVar7;
          if (local_64 <= 0.0) {
            local_64 = 0.0;
          }
          else {
            fVar7 = (float10)FUN_00417910();
            fVar8 = 1.0 / ((float)fVar7 + 0.5);
            local_44 = local_44 * fVar8;
            local_40 = local_40 * fVar8;
            local_3c = local_3c * fVar8;
            fVar7 = (float10)FUN_004428b0(iVar4 + 0x3c,&local_44);
            fVar7 = (float10)FUN_0068a080((double)((1.0 - (float)fVar7) * 0.5));
            local_6c = (float)fVar7 * local_6c;
          }
          local_64 = local_64 * local_6c * 1.25;
        }
        local_58 = local_58 + local_64;
      }
      fVar7 = (float10)FUN_0068a0c0();
      local_58 = (1.0 - (float)fVar7) * (local_58 + fVar2);
      if (1.0 <= local_58) {
        local_58 = 1.0;
      }
      *(float *)(param_1 + local_54 * 4) = local_58;
    }
  }
  FUN_0083e885();
  return;
}

