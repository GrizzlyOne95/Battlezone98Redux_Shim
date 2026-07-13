
/* WARNING: Removing unreachable block (ram,0x004671d0) */

void FUN_00466e50(float *param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  float *pfVar4;
  int iVar5;
  undefined4 *puVar6;
  bool bVar7;
  longlong lVar8;
  undefined1 local_14c [44];
  int local_120;
  int local_11c;
  undefined4 *local_118;
  undefined8 local_114;
  uint local_10c;
  int iStack_108;
  uint local_104;
  uint local_100;
  int iStack_fc;
  int local_f8;
  int local_f4;
  int local_f0;
  int local_ec;
  int local_e8;
  int local_e4;
  float local_e0;
  int local_dc;
  uint local_d8;
  int local_d4;
  int local_d0;
  int local_cc;
  int local_c8;
  undefined4 local_c4 [16];
  undefined4 local_84 [16];
  float local_44;
  float local_40;
  float local_3c;
  float local_38 [10];
  undefined4 local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_38[0] = *param_1;
  local_38[1] = 0.0;
  local_38[2] = param_1[2];
  local_38[3] = *param_1;
  local_38[4] = 0.0;
  local_38[5] = param_1[5];
  local_38[6] = param_1[3];
  local_38[7] = 0.0;
  local_38[8] = param_1[5];
  local_38[9] = param_1[3];
  local_10 = 0;
  local_c = param_1[2];
  FUN_00820180();
  local_f0 = 0x7fffffff;
  local_e8 = 0x7fffffff;
  local_e4 = -0x80000000;
  local_f4 = -0x80000000;
  for (local_d8 = 0; local_d8 < 4; local_d8 = local_d8 + 1) {
    FUN_00461fd0(local_38[local_d8 * 3] * DAT_02cc50e4);
    local_ec = FUN_0083f040();
    FUN_00461fd0(local_38[local_d8 * 3 + 2] * DAT_02cc50e4);
    local_f8 = FUN_0083f040();
    if (local_ec < local_f0) {
      local_f0 = local_ec;
    }
    if (local_e4 < local_ec) {
      local_e4 = local_ec;
    }
    if (local_f8 < local_e8) {
      local_e8 = local_f8;
    }
    if (local_f4 < local_f8) {
      local_f4 = local_f8;
    }
  }
  local_100 = 0;
  iStack_fc = 0;
  local_10c = 0;
  iStack_108 = 0;
  local_c8 = 0;
  for (local_d4 = local_e8; local_d4 <= local_f4; local_d4 = local_d4 + 1) {
    for (local_dc = local_f0; local_dc <= local_e4; local_dc = local_dc + 1) {
      cVar1 = FUN_0046ae20();
      if (cVar1 != '\0') goto LAB_00467423;
      local_104 = FUN_0077d640();
      bVar7 = CARRY4(local_104,local_100);
      local_100 = local_104 + local_100;
      iStack_fc = ((int)local_104 >> 0x1f) + iStack_fc + (uint)bVar7;
      uVar2 = local_104 * local_104;
      bVar7 = CARRY4(uVar2,local_10c);
      local_10c = uVar2 + local_10c;
      iStack_108 = ((int)uVar2 >> 0x1f) + iStack_108 + (uint)bVar7;
      local_c8 = local_c8 + 1;
    }
  }
  lVar8 = __allmul();
  local_114 = __allmul();
  local_114 = lVar8 - local_114;
  local_120 = (local_c8 * local_c8 - local_c8) * 100;
  local_11c = local_120 >> 0x1f;
  if (local_114 <= local_120) {
    puVar3 = (undefined4 *)FUN_008203f0();
    puVar6 = local_c4;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar3 = local_c4;
    puVar6 = local_84;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar6 = puVar6 + 1;
    }
    FUN_005b2950((double)((float)local_f0 * DAT_02cc50e0 - 20.0),
                 (double)((float)local_e8 * DAT_02cc50e0 - 20.0),
                 (double)((float)local_e4 * DAT_02cc50e0 + 20.0),
                 (double)((float)local_f4 * DAT_02cc50e0 + 20.0),local_14c);
    do {
      do {
        do {
          cVar1 = FUN_00462710(&local_118);
          if (cVar1 == '\0') goto LAB_00467423;
          local_d0 = FUN_00462630(*local_118);
        } while (local_d0 == 0);
        local_cc = (*(code *)**(undefined4 **)(local_d0 + 0x18))();
      } while (((((*(int *)(local_cc + 0x1c) != 2) && (*(int *)(local_cc + 0x1c) != 10)) &&
                (*(int *)(local_cc + 0x1c) != 5)) &&
               ((*(int *)(local_cc + 0x1c) != 7 && (*(int *)(local_cc + 0x1c) != 3)))) &&
              (*(int *)(local_cc + 0x14) != 0x54555252));
      iVar5 = FUN_00462400();
      local_e0 = *(float *)(iVar5 + 0xc);
      pfVar4 = (float *)(**(code **)(*(int *)(local_d0 + 0x18) + 0xc))();
      local_44 = *pfVar4;
      local_40 = pfVar4[1];
      local_3c = pfVar4[2];
      FUN_00820180();
    } while (((local_44 <= *param_1 - local_e0) || (param_1[3] + local_e0 <= local_44)) ||
            ((local_3c <= param_1[2] - local_e0 || (param_1[5] + local_e0 <= local_3c))));
  }
LAB_00467423:
  FUN_0083e885();
  return;
}

