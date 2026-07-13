
void FUN_004f1a40(float *param_1)

{
  float fVar1;
  char cVar2;
  float *pfVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  float local_e4;
  undefined4 local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  int local_d0;
  int local_cc;
  int local_c8;
  int local_c4;
  float local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float afStack_6c [15];
  int aiStack_30 [5];
  float afStack_1c [5];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_b0 = 0;
  local_b8 = 0;
  local_b4 = 0;
  fVar6 = (float10)FUN_00822d80(0,0xbf800000);
  local_d8 = (float)fVar6;
  if ((5.0 < local_d8 - *(float *)(local_a8 + 0x150)) || (*(int *)(local_a8 + 0x164) < 5)) {
    for (local_a4 = 0; local_a4 < 5; local_a4 = local_a4 + 1) {
      afStack_1c[local_a4] = -1.0;
      aiStack_30[local_a4] = 0;
    }
    local_c8 = (**(code **)(*(int *)(*(int *)(local_a8 + 0x10) + 0x18) + 4))();
    pfVar3 = (float *)(**(code **)(*(int *)(*(int *)(local_a8 + 0x10) + 0x18) + 0xc))();
    local_90 = *pfVar3;
    local_8c = pfVar3[1];
    local_88 = pfVar3[2];
    for (local_a4 = 0; local_a4 < 0x10; local_a4 = local_a4 + 1) {
      if ((local_a4 != local_c8) && (cVar2 = FUN_004db560(local_a4), cVar2 == '\0')) {
        local_e0 = FUN_005e0bc0(local_a4);
        for (local_bc = 0; local_bc < 0x5b; local_bc = local_bc + 1) {
          local_ac = FUN_005e0f70(local_bc);
          if ((local_ac != 0) && (cVar2 = FUN_004625d0(local_c8), cVar2 != '\0')) {
            pfVar3 = (float *)(**(code **)(*(int *)(local_ac + 0x18) + 0xc))();
            local_78 = *pfVar3;
            local_74 = pfVar3[1];
            local_70 = pfVar3[2];
            local_c0 = (local_78 - local_90) * (local_78 - local_90) +
                       (local_70 - local_88) * (local_70 - local_88);
            if (local_c0 < 22500.0) {
              uVar4 = (**(code **)(*(int *)(local_ac + 0x18) + 0x30))();
              iVar5 = FUN_00477d70(uVar4);
              if (iVar5 != 0) goto LAB_004f1bf0;
            }
            local_b4 = local_b4 + 1;
            local_c4 = 0;
            for (local_a0 = 0; local_a0 < 5; local_a0 = local_a0 + 1) {
              if (local_c4 == 0) {
                if ((local_c0 < afStack_1c[local_a0]) || (aiStack_30[local_a0] == 0)) {
                  local_cc = aiStack_30[local_a0];
                  local_d4 = afStack_1c[local_a0];
                  local_84 = afStack_6c[local_a0 * 3];
                  local_80 = afStack_6c[local_a0 * 3 + 1];
                  local_7c = afStack_6c[local_a0 * 3 + 2];
                  aiStack_30[local_a0] = local_ac;
                  afStack_1c[local_a0] = local_c0;
                  afStack_6c[local_a0 * 3] = local_78;
                  afStack_6c[local_a0 * 3 + 1] = local_74;
                  afStack_6c[local_a0 * 3 + 2] = local_70;
                  local_c4 = 1;
                }
              }
              else {
                iVar5 = aiStack_30[local_a0];
                fVar1 = afStack_1c[local_a0];
                local_9c = afStack_6c[local_a0 * 3];
                local_98 = afStack_6c[local_a0 * 3 + 1];
                local_94 = afStack_6c[local_a0 * 3 + 2];
                aiStack_30[local_a0] = local_cc;
                afStack_1c[local_a0] = local_d4;
                afStack_6c[local_a0 * 3] = local_84;
                afStack_6c[local_a0 * 3 + 1] = local_80;
                afStack_6c[local_a0 * 3 + 2] = local_7c;
                local_d4 = fVar1;
                local_cc = iVar5;
                local_84 = local_9c;
                local_80 = local_98;
                local_7c = local_94;
              }
            }
          }
LAB_004f1bf0:
        }
      }
    }
    if (5 < local_b4) {
      local_b4 = 5;
    }
    if (0 < local_b4) {
      local_d0 = rand();
      local_d0 = local_d0 % local_b4;
      local_b0 = 1;
      *param_1 = afStack_6c[local_d0 * 3];
      param_1[1] = 0.0;
      param_1[2] = afStack_6c[local_d0 * 3 + 2];
      goto LAB_004f1fc0;
    }
  }
  for (; (local_b0 == 0 && (local_b8 < 8)); local_b8 = local_b8 + 1) {
    local_b0 = FUN_004f18f0(&local_dc,&local_e4,local_b8);
  }
  if (local_b0 != 0) {
    *param_1 = local_dc;
    param_1[1] = 0.0;
    param_1[2] = local_e4;
  }
LAB_004f1fc0:
  FUN_0083e885();
  return;
}

