
void FUN_0059a010(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  float10 fVar8;
  undefined8 uVar9;
  int *piVar10;
  undefined4 local_198 [8];
  undefined1 local_178 [4];
  undefined4 local_174;
  int local_170;
  undefined4 local_16c;
  int local_168;
  undefined8 local_15c;
  undefined8 local_154;
  undefined8 local_14c;
  undefined8 local_144;
  undefined8 local_13c;
  undefined8 local_134;
  undefined8 local_12c;
  undefined8 local_124;
  undefined8 local_11c;
  undefined8 local_114;
  int local_10c;
  int local_108;
  undefined4 local_104;
  float local_100;
  undefined4 local_fc;
  undefined4 *local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  undefined4 local_e8;
  int local_e4;
  void *local_e0;
  int local_dc;
  int local_d8;
  int local_d4;
  undefined4 local_d0;
  int local_cc;
  undefined4 local_c8;
  void *local_c4;
  int local_c0;
  undefined4 *local_bc;
  int *local_b8;
  float local_b4;
  float local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int *local_98;
  char local_94 [128];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c0ee;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  local_9c = FUN_00462630();
  local_a0 = FUN_00462630();
  if (DAT_00919871 != '\0') {
    if (((local_9c != 0) && (local_98[0x32] != 0)) &&
       ((local_a0 != 0 || ((local_98[0x34] != 0 || ((float)local_98[0x36] != -1.0)))))) {
      FUN_00477ce0(uVar2);
      local_174 = 1;
      if ((local_a0 == 0) && ((local_dc = local_98[0x32], 3 < local_dc && (local_dc < 6)))) {
        local_98[0x32] = 3;
      }
      local_170 = local_98[0x32];
      if (local_98[0x34] == 0) {
        if ((float)local_98[0x36] == -1.0) {
          local_16c = FUN_00477590();
          local_c4 = operator_new(0x18);
          local_8 = 1;
          if (local_c4 == (void *)0x0) {
            local_d4 = 0;
          }
          else {
            uVar4 = (**(code **)(*(int *)(local_a0 + 0x18) + 0xc))();
            uVar3 = (**(code **)(*(int *)(local_9c + 0x18) + 0xc))();
            local_d4 = FUN_00460490(uVar3,uVar4);
          }
          local_108 = local_d4;
          local_8 = 0xffffffff;
          local_168 = local_d4;
        }
        else {
          local_16c = 0;
          local_e0 = operator_new(0x18);
          local_8 = 0;
          if (local_e0 == (void *)0x0) {
            local_cc = 0;
          }
          else {
            piVar10 = local_98 + 0x35;
            uVar4 = (**(code **)(*(int *)(local_9c + 0x18) + 0xc))();
            local_cc = FUN_00460490(uVar4,piVar10);
          }
          local_10c = local_cc;
          local_8 = 0xffffffff;
          local_168 = local_cc;
        }
      }
      else {
        local_16c = 0;
        local_168 = local_98[0x34];
      }
      local_15c = 0;
      FUN_004dbaf0();
    }
    local_98[0x32] = 0;
    local_98[0x33] = 0;
    local_a0 = 0;
    local_98[0x34] = 0;
    local_98[0x36] = -0x40800000;
  }
  if ((DAT_00919870 != '\0') && (cVar1 = FUN_005996f0(), cVar1 == '\0')) {
    if ((local_9c == 0) || (local_98[0x32] == 0)) {
      local_e4 = local_9c;
      FUN_00599800();
      if (local_9c == 0) {
        local_98[0x31] = 0;
      }
      else {
        iVar5 = FUN_00477590();
        local_98[0x31] = iVar5;
      }
      if ((local_9c != 0) && (local_9c == local_e4)) {
        fVar8 = (float10)FUN_00822da0();
        local_f0 = (float)fVar8;
        if (local_f0 < (float)local_98[0x38]) {
          FUN_0059ad10();
        }
      }
      fVar8 = (float10)FUN_00822da0();
      local_100 = (float)fVar8;
      local_98[0x38] = (int)(local_100 + 0.5);
    }
    else {
      FUN_00599800();
      if (local_a0 == 0) {
        local_98[0x33] = 0;
        FUN_005999f0(local_98 + 0x34,local_178);
        if (local_98[0x34] == 0) {
          (**(code **)(*local_98 + 0x28))(DAT_009175a0,DAT_009175a4,local_98 + 0x35);
          local_98[0x36] = 0;
        }
      }
      else {
        iVar5 = FUN_00477590();
        local_98[0x33] = iVar5;
      }
    }
  }
  if ((DAT_00919874 != '\0') && (local_9c != 0)) {
    if (((*(int *)(local_9c + 0xac) != 0) && (*(int *)(local_9c + 0xa8) == 1)) &&
       ((*(int *)(local_9c + 0xcc) == 0 || (*(int *)(local_9c + 200) == 0)))) {
      puVar6 = (undefined4 *)(local_9c + 0xa8);
      puVar7 = local_198;
      for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      FUN_004dbc00();
      FUN_004dbaf0();
    }
    local_f8 = (undefined4 *)FUN_0045bdf0();
    local_bc = local_f8;
    if (local_f8 == (undefined4 *)0x0) {
      local_e8 = 0;
    }
    else {
      local_e8 = (**(code **)*local_f8)();
    }
    uVar4 = FUN_0045ca50();
    FUN_00461440(uVar4);
  }
  FUN_00596190();
  local_114 = FUN_00689eb0();
  local_d8 = (int)((float)local_114 * 15.0);
  local_a4 = local_d8;
  local_124 = FUN_00689eb0();
  local_ac = (int)((float)DAT_00917580[1] - (float)((ulonglong)local_124 >> 0x20) * 60.0);
  if (local_9c != 0) {
    FUN_00595460();
    FUN_00595400();
    sprintf(local_94," Subject: Name (%s) Current Command (%s) Next Command (%s)");
    FUN_00596140();
    FUN_00596140();
    local_b8 = (int *)FUN_0045bdf0();
    local_154 = FUN_00689eb0();
    local_134 = FUN_00689eb0();
    FUN_004b70d0((int)((float)(DAT_00917580[4] - DAT_00917580[2]) - (float)local_134 * 150.0));
    if (local_b8 == (int *)0x0) {
      FUN_00599b30();
    }
    else {
      (**(code **)(*local_b8 + 0x14))();
    }
    FUN_004c0100(DAT_00917580,local_a4,local_ac,&local_b0,&local_b4,local_94,DAT_00917550,
                 DAT_0091755c,DAT_00917584,0,0);
    local_14c = FUN_00689eb0();
    local_ac = (int)((float)((ulonglong)local_14c >> 0x20) * 2.0 + local_b4);
    FUN_004c0100(DAT_00917580,local_a4,local_ac,&local_b0,&local_b4," Set Command:",DAT_00917550,
                 DAT_0091755c,DAT_00917584,0,0);
    local_144 = FUN_00689eb0();
    uVar9 = CONCAT44(local_12c._4_4_,(undefined4)local_12c);
    DAT_02a13ccc = (int)((float)local_144 * 5.0 + local_b0);
    DAT_02a13cd0 = local_ac;
    DAT_02a13cd4 = DAT_02a13ccc;
    local_a4 = DAT_02a13ccc;
    for (local_a8 = 0; local_12c = uVar9, local_a8 < 0x1d; local_a8 = local_a8 + 1) {
      local_c0 = local_a8;
      if ((local_a8 != 1) && ((local_a8 < 10 || (0xe < local_a8)))) {
        if (local_98[0x32] == local_a8) {
          local_c8 = DAT_00917584;
        }
        else {
          local_c8 = DAT_0091755c;
        }
        local_104 = local_c8;
        if (local_98[0x32] == local_a8) {
          local_d0 = DAT_0091755c;
        }
        else {
          local_d0 = DAT_00917584;
        }
        local_fc = local_d0;
        local_ec = (float)local_a4;
        fVar8 = (float10)FUN_00689cb0(DAT_00917550);
        local_f4 = (float)fVar8;
        if ((float)*DAT_00917580 < local_ec + local_f4) {
          local_a4 = DAT_02a13ccc;
          uVar9 = FUN_00689eb0();
          local_ac = (int)((float)((ulonglong)uVar9 >> 0x20) * 2.0 + local_b4);
          local_11c = uVar9;
          DAT_02a13cd4 = FUN_0043d130(DAT_02a13cd4);
        }
        FUN_004c0100(DAT_00917580,local_a4,local_ac,&local_b0,&local_b4,
                     (&PTR_DAT_00872448)[local_a8],DAT_00917550,local_104,local_fc,0,0);
        if ((((DAT_00919870 != '\0') && (local_a4 <= DAT_009175a0)) &&
            ((float)DAT_009175a0 < local_b0)) &&
           ((local_ac <= DAT_009175a4 && ((float)DAT_009175a4 < local_b4)))) {
          local_98[0x32] = local_a8;
        }
        uVar9 = FUN_00689eb0();
        local_a4 = (int)((float)uVar9 * 5.0 + local_b0);
      }
    }
    DAT_02a13cd4 = FUN_0043d130(DAT_02a13cd4);
    DAT_02a13cc8 = (int)local_b4;
    local_a4 = local_d8;
    local_13c = FUN_00689eb0();
    local_ac = (int)((float)((ulonglong)local_13c >> 0x20) * 2.0 + local_b4);
    if (local_98[0x34] == 0) {
      if ((float)local_98[0x36] == -1.0) {
        if (local_a0 == 0) goto LAB_0059acf5;
        FUN_00595400();
        sprintf(local_94," Object: Name (%s)");
      }
      else {
        sprintf(local_94," Object: Pos X(%f), Z(%f)",(double)(float)local_98[0x35],
                (double)(float)local_98[0x37]);
      }
    }
    else {
      sprintf(local_94," Object: Path (%s)");
    }
    FUN_004c0100(DAT_00917580,local_a4,local_ac,&local_b0,&local_b4,local_94,DAT_00917550,
                 DAT_0091755c,DAT_00917584,0,0,0);
  }
LAB_0059acf5:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

