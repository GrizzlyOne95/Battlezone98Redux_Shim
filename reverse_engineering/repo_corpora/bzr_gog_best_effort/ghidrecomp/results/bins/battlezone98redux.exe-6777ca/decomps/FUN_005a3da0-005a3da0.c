
void FUN_005a3da0(int *param_1,int *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  float *pfVar3;
  int iVar4;
  float10 fVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  undefined1 *puVar10;
  undefined1 local_144 [44];
  undefined1 local_118 [12];
  undefined8 local_10c;
  undefined4 *local_104;
  undefined4 local_100;
  undefined8 local_fc;
  float local_f4;
  undefined4 local_f0;
  float local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  void *local_d8;
  undefined4 local_d4;
  void *local_d0;
  undefined4 local_cc;
  void *local_c8;
  float local_c4;
  int local_c0;
  float local_bc;
  int *local_b8;
  char local_b1;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  float local_8c;
  float local_88;
  float local_84;
  undefined1 local_80 [24];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20 [3];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c25d;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puVar2 = (undefined4 *)(**(code **)(param_1[6] + 0xc))(local_14);
  local_98 = *puVar2;
  local_94 = puVar2[1];
  local_90 = puVar2[2];
  cVar1 = FUN_00466d40(&local_98);
  if ((cVar1 == '\0') || ((*(uint *)(param_1[0x8c] + 0x114) & 4) == 0)) {
    pfVar3 = (float *)(**(code **)(param_2[6] + 0xc))();
    local_8c = *pfVar3;
    local_88 = pfVar3[1];
    local_84 = pfVar3[2];
    cVar1 = FUN_00466d40(&local_8c);
    if (cVar1 != '\0') {
      local_c4 = 1.0;
      local_2c = local_8c;
      local_28 = local_88;
      local_24 = local_84;
      for (local_c0 = 0; local_c0 < 8; local_c0 = local_c0 + 1) {
        uVar6 = FUN_008205a0(((float)local_c0 * 3.1415927) / 4.0);
        local_20[0] = (float)uVar6 * 16.0 * DAT_02cc50e0;
        local_20[1] = 0.0;
        local_20[2] = (float)((ulonglong)uVar6 >> 0x20) * 16.0 * DAT_02cc50e0;
        local_10c = uVar6;
        local_fc = uVar6;
        puVar2 = (undefined4 *)FUN_0049c4f0();
        local_68 = *puVar2;
        local_64 = puVar2[1];
        local_60 = puVar2[2];
        local_5c = puVar2[3];
        local_58 = puVar2[4];
        local_54 = puVar2[5];
        fVar5 = (float10)FUN_00466de0(&local_68,local_20,local_c4);
        local_bc = (float)fVar5;
        if (local_bc < local_c4) {
          local_c4 = local_bc;
          fVar5 = (float10)FUN_00820570((double)(local_20[0] * local_20[0] +
                                                 local_20[2] * local_20[2] + 0.0001));
          local_f4 = (float)fVar5;
          local_bc = local_f4 + local_bc;
          local_2c = local_20[0] * local_bc + local_8c;
          local_28 = local_88;
          local_24 = local_20[2] * local_bc + local_84;
          local_ec = local_f4;
        }
      }
      local_8c = local_2c;
      local_88 = local_28;
      local_84 = local_24;
    }
    local_b1 = '\x01';
    local_b0 = local_98;
    local_ac = local_94;
    local_a8 = local_90;
    puVar2 = (undefined4 *)
             FUN_004401a0(local_118,local_8c,local_88,local_84,local_98,local_94,local_90);
    local_a4 = *puVar2;
    local_a0 = puVar2[1];
    local_9c = puVar2[2];
    local_e4 = 0x3f800000;
    local_50 = local_a4;
    local_4c = local_a0;
    local_48 = local_9c;
    puVar2 = (undefined4 *)FUN_0049c4f0();
    local_44 = *puVar2;
    local_40 = puVar2[1];
    local_3c = puVar2[2];
    local_38 = puVar2[3];
    local_34 = puVar2[4];
    local_30 = puVar2[5];
    iVar4 = FUN_00784620(local_44,local_40,local_3c,local_38,local_34,local_30,local_a4,local_a0,
                         local_9c,&local_e4,local_80);
    if (iVar4 == 0) {
      puVar10 = local_144;
      fVar5 = (float10)FUN_0044fb20(local_90,local_84,puVar10);
      dVar9 = (double)fVar5;
      fVar5 = (float10)FUN_0044fb20(local_98,local_8c,dVar9);
      dVar8 = (double)fVar5;
      fVar5 = (float10)FUN_00456080(local_90,local_84,dVar8);
      dVar7 = (double)fVar5;
      fVar5 = (float10)FUN_00456080(local_98,local_8c,dVar7);
      FUN_005b2950((double)fVar5,dVar7,dVar8,dVar9,puVar10);
LAB_005a430b:
      do {
        do {
          cVar1 = FUN_00462710(&local_104);
          if (cVar1 == '\0') goto LAB_005a440b;
          local_b8 = (int *)FUN_004da060(*local_104);
        } while (((local_b8 == (int *)0x0) || (local_b8 == param_1)) || (local_b8 == param_2));
        local_dc = (**(code **)(local_b8[6] + 0x30))();
        iVar4 = FUN_0062e000(local_dc);
        if (iVar4 != 0) {
          iVar4 = FUN_00417e20(local_dc);
          if (iVar4 == 0) goto LAB_005a430b;
          cVar1 = (**(code **)(*local_b8 + 0x68))();
          if (cVar1 == '\0') goto LAB_005a430b;
        }
        FUN_00462470();
        cVar1 = FUN_00480a30();
      } while (cVar1 == '\0');
      local_b1 = '\0';
    }
    else {
      local_b1 = '\0';
    }
LAB_005a440b:
    if (local_b1 == '\0') {
      local_c8 = operator_new(0x14c);
      local_8 = 2;
      if (local_c8 == (void *)0x0) {
        local_cc = 0;
      }
      else {
        local_cc = FUN_005a54c0(param_1,param_2,&local_8c);
      }
      local_100 = local_cc;
    }
    else {
      local_d0 = operator_new(0x134);
      local_8 = 1;
      if (local_d0 == (void *)0x0) {
        local_e0 = 0;
      }
      else {
        local_e0 = FUN_005a4fb0(param_1,param_2);
      }
      local_e8 = local_e0;
    }
  }
  else {
    local_d8 = operator_new(0x134);
    local_8 = 0;
    if (local_d8 == (void *)0x0) {
      local_d4 = 0;
    }
    else {
      local_d4 = FUN_005a4ad0(param_1,param_2);
    }
    local_f0 = local_d4;
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

