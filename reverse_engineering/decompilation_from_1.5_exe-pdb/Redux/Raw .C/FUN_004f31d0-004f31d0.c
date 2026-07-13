
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004f31d0(void)

{
  undefined8 uVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int local_ac;
  int local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  float local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined8 local_90;
  float local_88;
  undefined8 local_84;
  float local_7c;
  float local_78;
  float local_74;
  int local_70;
  undefined8 local_6c;
  float local_64;
  int local_60;
  int local_5c;
  float local_58;
  float local_54;
  int local_50;
  float local_4c;
  float local_48;
  int local_44;
  int local_40;
  float local_3c;
  ulong *local_38;
  undefined8 local_34;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_84 = FUN_00689eb0();
  local_38 = DAT_0091552c;
  local_34 = local_84;
  cVar2 = FUN_004f47c0();
  if (cVar2 != '\0') goto LAB_004f3875;
  if (*(char *)(local_2c + 0x11c) == '\0') {
    iVar3 = FUN_004f2db0();
    if (iVar3 != 0) goto LAB_004f3231;
    FUN_004f3f60(0);
    uVar1 = local_34;
  }
  else {
LAB_004f3231:
    local_a4 = FUN_004f4010();
    FUN_004f3f60(local_a4);
    uVar1 = local_34;
  }
  local_34._4_4_ = (float)((ulonglong)uVar1 >> 0x20);
  local_34._0_4_ = (float)uVar1;
  local_34 = uVar1;
  if (*(int *)(local_2c + 0x120) == 0) {
    fVar5 = (float10)FUN_00822da0();
    local_7c = (float)fVar5;
    local_6c = CONCAT44(local_6c._4_4_,(undefined4)local_6c);
    if (local_7c < *(float *)(local_2c + 0xfc)) {
      local_58 = (float)_DAT_008e8688 * (float)local_34;
      local_4c = (float)_DAT_008e8684 * local_34._4_4_;
      local_78 = DAT_00920ef4;
      local_64 = 0.0;
      local_3c = 0.0;
      for (local_44 = 0; local_44 < *(int *)(local_2c + 8); local_44 = local_44 + 1) {
        local_70 = *(int *)(local_2c + 0x1c + local_44 * 0x18);
        if (local_70 != 0) {
          FUN_00689ab0(local_38,local_70,&local_98,&local_88);
          fVar5 = (float10)FUN_0044fb20(local_64,local_98);
          local_64 = (float)fVar5;
          if (0 < local_44) {
            local_3c = local_34._4_4_ * 10.0 + local_3c;
          }
          local_3c = local_3c + local_88;
        }
      }
      fVar5 = (float10)FUN_0044fb20(local_58,local_64);
      local_58 = (float)fVar5;
      fVar5 = (float10)FUN_0044fb20(local_4c,local_3c);
      local_4c = (float)fVar5;
      local_20 = (*(int *)(DAT_00917580 + 0x10) - *(int *)(DAT_00917580 + 8)) -
                 (int)((float)_DAT_008e868c * (float)local_34);
      local_28 = local_20 - (int)local_58;
      local_24 = ((*(int *)(DAT_00917580 + 0x14) - *(int *)(DAT_00917580 + 0xc)) - (int)fVar5) / 2;
      local_1c = (int)fVar5 + local_24;
      if (400 < DAT_02cecee0) {
        DAT_00920ef4 = local_78 + 0.01;
        FUN_0068af70(DAT_00917580,(int)((float)local_28 - (float)local_34 * 15.0),
                     (int)((float)local_24 - local_34._4_4_ * 5.0),
                     (int)((float)local_20 + (float)local_34 * 5.0),
                     (int)((float)local_1c + local_34._4_4_ * 5.0),DAT_00917584,2);
      }
      DAT_00920ef4 = local_78;
      local_5c = local_24;
      local_40 = 0;
      while( true ) {
        local_6c = CONCAT44(local_6c._4_4_,(undefined4)local_6c);
        if (*(int *)(local_2c + 8) <= local_40) break;
        local_60 = *(int *)(local_2c + 0x1c + local_40 * 0x18);
        if (local_60 != 0) {
          std::_Init_atomic_counter(local_38,*(ulong *)(local_2c + 0x20 + local_40 * 0x18));
          FUN_00689d10(local_38,DAT_00917580,local_28,local_5c,local_60);
          fVar5 = (float10)FUN_00689ce0(local_38,local_60);
          local_9c = (float)fVar5;
          local_5c = (int)((float)local_5c + local_9c + local_34._4_4_ * 10.0);
        }
        local_40 = local_40 + 1;
      }
    }
  }
  else {
    local_54 = (float)_DAT_008e8688 * (float)local_34;
    local_48 = (float)_DAT_008e8684 * local_34._4_4_;
    local_74 = DAT_00920ef4;
    local_50 = *(int *)(local_2c + 0x114);
    if (local_50 != 0) {
      FUN_00689ab0(local_38,local_50,&local_a0,&local_94);
      fVar5 = (float10)FUN_0044fb20(local_54,local_a0);
      local_54 = (float)fVar5;
      fVar5 = (float10)FUN_0044fb20(local_48,local_94);
      local_48 = (float)fVar5;
      uVar1 = local_34;
    }
    local_34._4_4_ = (float)((ulonglong)uVar1 >> 0x20);
    local_34._0_4_ = (float)uVar1;
    local_10 = (int)((float)(*(int *)(DAT_00917580 + 0x10) - *(int *)(DAT_00917580 + 8)) -
                    (float)_DAT_008e868c * (float)local_34);
    local_18 = (int)((float)local_10 - local_54);
    local_14 = (int)(((float)(*(int *)(DAT_00917580 + 0x14) - *(int *)(DAT_00917580 + 0xc)) -
                     local_48) / 2.0);
    local_c = (int)((float)local_14 + local_48);
    if (400 < DAT_02cecee0) {
      DAT_00920ef4 = local_74 + 0.01;
      fVar6 = local_34._4_4_ * 5.0;
      fVar7 = (float)local_34 * 5.0;
      fVar8 = local_34._4_4_ * 5.0;
      fVar9 = (float)local_34 * 15.0;
      local_34 = uVar1;
      FUN_0068af70(DAT_00917580,(int)((float)local_18 - fVar9),(int)((float)local_14 - fVar8),
                   (int)((float)local_10 + fVar7),(int)((float)local_c + fVar6),DAT_00917584,2);
      uVar1 = local_34;
    }
    DAT_00920ef4 = local_74;
    local_34 = uVar1;
    if (local_50 != 0) {
      std::_Init_atomic_counter(local_38,*(ulong *)(local_2c + 0x118));
      FUN_00689d10(local_38,DAT_00917580,local_18,local_14,local_50);
    }
    uVar4 = (**(code **)(*(int *)(*(int *)(local_2c + 0x120) + 0x18) + 0xc))(DAT_00917594,0);
    local_90 = FUN_00497780(uVar4);
    iVar3 = (int)((ulonglong)local_90 >> 0x20);
    local_6c = local_90;
    if ((((*(int *)(DAT_00917580 + 8) <= (int)local_90) &&
         ((int)local_90 <= *(int *)(DAT_00917580 + 0x10))) &&
        (*(int *)(DAT_00917580 + 0xc) <= iVar3)) && (iVar3 <= *(int *)(DAT_00917580 + 0x14))) {
      local_ac = local_18 - (int)((float)local_34 * 10.0);
      local_a8 = (local_14 + local_c) / 2;
      FUN_004f2f20(DAT_00917580,&local_18,&local_ac,&local_6c,DAT_0091755c);
    }
  }
LAB_004f3875:
  FUN_0083e885();
  return;
}

