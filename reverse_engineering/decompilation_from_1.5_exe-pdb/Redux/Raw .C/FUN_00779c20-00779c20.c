
void __thiscall
FUN_00779c20(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,int param_9)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  float *pfVar6;
  undefined4 uVar7;
  undefined1 local_e0 [12];
  float local_d4;
  float local_d0;
  int local_cc;
  float local_c8;
  float local_c4;
  int local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  int local_ac;
  float local_a8;
  float local_a4;
  undefined4 local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  int local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  undefined4 local_70;
  int local_6c;
  float local_68;
  float local_64;
  undefined4 local_60;
  int local_5c;
  undefined4 local_58;
  int local_54;
  float local_50;
  float local_4c;
  int local_48;
  float local_44;
  int local_40;
  undefined4 local_3c;
  float *local_38;
  int local_34;
  int local_30;
  int local_2c;
  float *local_28;
  int local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_50 = 3.4028235e+38;
  local_4c = -3.4028235e+38;
  local_3c = *(undefined4 *)(param_1 + 0x39c);
  local_54 = *(int *)(param_1 + 0x240) * 0x100 + DAT_02ce99c0 + -0x80 +
             (param_2 * 0x10 + param_4) * 4;
  local_48 = *(int *)(param_1 + 0x244) * 0x100 + DAT_02cd9984 + -0x80 +
             (param_3 * 0x10 + param_5) * 4;
  local_24 = param_1;
  local_a0 = FUN_00780dc0(local_54,local_48);
  local_cc = FUN_00780e40(local_54,local_48);
  local_38 = (float *)(&DAT_008ed0e8 + local_cc * 0x20);
  uVar7 = local_a0;
  FUN_0077c670(local_a0);
  local_28 = (float *)FUN_0050ce10(uVar7);
  local_d4 = local_38[2] * local_28[2] + *local_28;
  local_d0 = local_38[3] * local_28[3] + local_28[1];
  local_68 = *local_38 * local_28[2] + *local_28;
  local_64 = local_38[1] * local_28[3] + local_28[1];
  local_c8 = local_38[6] * local_28[2] + *local_28;
  local_c4 = local_38[7] * local_28[3] + local_28[1];
  local_94 = local_d4 - local_68;
  local_90 = local_d0 - local_64;
  local_9c = local_94 / 5.0;
  local_98 = local_90 / 5.0;
  local_bc = local_c8 - local_68;
  local_b8 = local_c4 - local_64;
  local_a8 = local_bc / 5.0;
  local_a4 = local_b8 / 5.0;
  local_70 = 0x43a00000;
  local_60 = 0x41a00000;
  local_7c = ((float)param_2 * 320.0 + *(float *)(local_24 + 0x248) + (float)param_4 * 20.0) -
             *(float *)(local_24 + 0x100 + param_2 * 0x30 + param_3 * 0xc);
  local_78 = ((*(float *)(local_24 + 0x24c) - (float)param_3 * 320.0) - (float)param_5 * 20.0) -
             *(float *)(local_24 + param_2 * 0x30 + 0x108 + param_3 * 0xc);
  local_58 = 0x40a00000;
  local_88 = (float)param_6 * 5.0 + local_7c +
             *(float *)(local_24 + 0x100 + param_2 * 0x30 + param_3 * 0xc);
  local_74 = (float)(param_7 + -1) * 5.0 + local_7c +
             *(float *)(local_24 + 0x100 + param_2 * 0x30 + param_3 * 0xc);
  local_8c = (local_78 - (float)(param_9 + -1) * 5.0) +
             *(float *)(local_24 + param_2 * 0x30 + 0x108 + param_3 * 0xc);
  local_80 = (local_78 - (float)param_8 * 5.0) +
             *(float *)(local_24 + param_2 * 0x30 + 0x108 + param_3 * 0xc);
  if (local_88 < *(float *)(local_24 + 0x280 + param_2 * 0x40 + param_3 * 0x10)) {
    *(float *)(local_24 + 0x280 + param_2 * 0x40 + param_3 * 0x10) = local_88;
  }
  pfVar6 = (float *)(local_24 + param_2 * 0x40 + 0x288 + param_3 * 0x10);
  if (*pfVar6 <= local_74 && local_74 != *pfVar6) {
    *(float *)(local_24 + param_2 * 0x40 + 0x288 + param_3 * 0x10) = local_74;
  }
  if (local_8c < *(float *)(local_24 + param_2 * 0x40 + 0x284 + param_3 * 0x10)) {
    *(float *)(local_24 + param_2 * 0x40 + 0x284 + param_3 * 0x10) = local_8c;
  }
  pfVar6 = (float *)(local_24 + param_2 * 0x40 + 0x28c + param_3 * 0x10);
  if (*pfVar6 <= local_80 && local_80 != *pfVar6) {
    *(float *)(local_24 + param_2 * 0x40 + 0x28c + param_3 * 0x10) = local_80;
  }
  for (local_30 = param_8; local_30 < param_9; local_30 = local_30 + 1) {
    for (local_34 = param_6; local_34 < param_7; local_34 = local_34 + 1) {
      local_b4 = (float)local_30 * local_9c + local_68 + (float)local_34 * local_a8;
      local_b0 = (float)local_30 * local_98 + local_64 + (float)local_34 * local_a4;
      iVar5 = FUN_0077d640(local_54 + local_34,local_48 + local_30);
      local_44 = (float)iVar5 * 0.1;
      pfVar6 = (float *)FUN_0077d7c0(local_e0,local_54 + local_34,local_48 + local_30);
      local_20 = *pfVar6;
      local_1c = pfVar6[1];
      local_18 = pfVar6[2];
      if (local_44 < local_50) {
        local_50 = local_44;
      }
      if (local_4c < local_44) {
        local_4c = local_44;
      }
      **(float **)(local_24 + 0x3ac) = local_44;
      *(int *)(local_24 + 0x3ac) = *(int *)(local_24 + 0x3ac) + 4;
      **(undefined1 **)(local_24 + 0x3a8) = (char)(int)(local_b4 * 160.0);
      *(int *)(local_24 + 0x3a8) = *(int *)(local_24 + 0x3a8) + 1;
      **(undefined1 **)(local_24 + 0x3a8) = (char)(int)(local_b0 * 160.0);
      *(int *)(local_24 + 0x3a8) = *(int *)(local_24 + 0x3a8) + 1;
      **(undefined1 **)(local_24 + 0x3a8) = (char)(int)(local_20 * 127.0 + 127.0);
      *(int *)(local_24 + 0x3a8) = *(int *)(local_24 + 0x3a8) + 1;
      **(undefined1 **)(local_24 + 0x3a8) = (char)(int)(-local_18 * 127.0 + 127.0);
      *(int *)(local_24 + 0x3a8) = *(int *)(local_24 + 0x3a8) + 1;
      *(int *)(local_24 + 0x39c) = *(int *)(local_24 + 0x39c) + 1;
      local_14 = local_20;
      local_10 = local_1c;
      local_c = local_18;
    }
  }
  if (local_50 < *(float *)(local_24 + 0x1c0 + param_2 * 0x10 + param_3 * 4)) {
    *(float *)(local_24 + 0x1c0 + param_2 * 0x10 + param_3 * 4) = local_50;
  }
  pfVar6 = (float *)(local_24 + 0x200 + param_2 * 0x10 + param_3 * 4);
  if (*pfVar6 <= local_4c && local_4c != *pfVar6) {
    *(float *)(local_24 + 0x200 + param_2 * 0x10 + param_3 * 4) = local_4c;
  }
  if (*(int *)(local_24 + 0x3a4) != 0) {
    local_ac = (param_9 + -1) - param_8;
    local_c0 = (param_7 + -1) - param_6;
    local_84 = param_7 - param_6;
    for (local_40 = 0; local_40 < local_ac; local_40 = local_40 + 1) {
      local_5c = local_84 * local_40;
      local_6c = (local_40 + 1) * local_84;
      for (local_2c = 0; local_2c < local_c0; local_2c = local_2c + 1) {
        sVar2 = (short)local_3c;
        sVar3 = (short)local_5c;
        sVar1 = (short)local_2c;
        **(short **)(local_24 + 0x3a4) = sVar2 + sVar3 + sVar1;
        *(int *)(local_24 + 0x3a4) = *(int *)(local_24 + 0x3a4) + 2;
        **(short **)(local_24 + 0x3a4) = sVar2 + sVar3 + 1 + sVar1;
        *(int *)(local_24 + 0x3a4) = *(int *)(local_24 + 0x3a4) + 2;
        sVar4 = (short)local_6c;
        **(short **)(local_24 + 0x3a4) = sVar2 + sVar4 + 1 + sVar1;
        *(int *)(local_24 + 0x3a4) = *(int *)(local_24 + 0x3a4) + 2;
        **(short **)(local_24 + 0x3a4) = sVar2 + sVar3 + sVar1;
        *(int *)(local_24 + 0x3a4) = *(int *)(local_24 + 0x3a4) + 2;
        **(short **)(local_24 + 0x3a4) = sVar2 + sVar4 + 1 + sVar1;
        *(int *)(local_24 + 0x3a4) = *(int *)(local_24 + 0x3a4) + 2;
        **(short **)(local_24 + 0x3a4) = sVar2 + sVar4 + sVar1;
        *(int *)(local_24 + 0x3a4) = *(int *)(local_24 + 0x3a4) + 2;
        *(int *)(local_24 + 0x3a0) = *(int *)(local_24 + 0x3a0) + 6;
      }
    }
  }
  FUN_0083e885();
  return;
}

