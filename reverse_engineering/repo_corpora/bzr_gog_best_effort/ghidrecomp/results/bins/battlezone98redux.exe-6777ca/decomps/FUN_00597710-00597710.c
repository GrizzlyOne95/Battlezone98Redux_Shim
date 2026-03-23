
void __fastcall FUN_00597710(int param_1)

{
  undefined4 uVar1;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  int local_a8;
  undefined1 local_a4 [4];
  undefined1 local_a0 [4];
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  int local_90;
  int local_8c;
  char local_88 [128];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_94 = *(undefined4 *)(param_1 + 0x18);
  local_90 = *(int *)(param_1 + 8);
  if (*(int *)(param_1 + 0x6c) == 3) {
    local_d0 = DAT_0091755c;
  }
  else {
    if (*(int *)(param_1 + 0x6c) == 0) {
      local_cc = DAT_009175b0;
    }
    else {
      local_cc = DAT_00917588;
    }
    local_d0 = local_cc;
  }
  if (*(int *)(param_1 + 0x6c) == 0) {
    local_a8 = *(int *)(param_1 + 0x158) + 4;
  }
  else {
    local_a8 = 0;
  }
  local_8c = param_1;
  FUN_00595080(local_94,local_90,local_a8,"Resource",local_d0,DAT_00917584);
  local_90 = local_90 + *(int *)(local_8c + 0x24);
  if (*(int *)(local_8c + 0x6c) == 3) {
    local_98 = FUN_005e0bc0(1);
    local_9c = FUN_005e0bc0(2);
    if (DAT_00919879 != '\0') {
      if (DAT_00919875 == '\0') {
        local_b4 = 1;
      }
      else {
        local_b4 = 10;
      }
      FUN_005e1010(local_b4);
    }
    if (DAT_0091987a != '\0') {
      if (DAT_00919875 == '\0') {
        local_c4 = 0xffffffff;
      }
      else {
        local_c4 = 0xfffffff6;
      }
      FUN_005e1010(local_c4);
    }
    uVar1 = FUN_005e1190();
    uVar1 = FUN_005e10b0(uVar1);
    sprintf(local_88,"Team 1 Scrap: %ld/%ld",uVar1);
    FUN_004c0100(DAT_00917580,local_94,local_90,local_a0,local_a4,local_88,DAT_00917550,DAT_0091755c
                 ,DAT_00917584,0,0,0);
    local_90 = local_90 + *(int *)(local_8c + 0x28);
    FUN_00595080(local_94,local_90,*(int *)(local_8c + 0x158) + 1,"Add Scrap",DAT_009175b0,
                 DAT_00917584);
    local_90 = local_90 + *(int *)(local_8c + 0x28);
    FUN_00595080(local_94,local_90,*(int *)(local_8c + 0x158) + 2,"Sub Scrap",DAT_009175b0,
                 DAT_00917584);
    local_90 = *(int *)(local_8c + 0x28) + *(int *)(local_8c + 0x2c) + local_90;
    if (DAT_0091987b != '\0') {
      if (DAT_00919875 == '\0') {
        local_bc = 1;
      }
      else {
        local_bc = 10;
      }
      FUN_005e11b0(local_bc);
    }
    if (DAT_0091987c != '\0') {
      if (DAT_00919875 == '\0') {
        local_ac = 0xffffffff;
      }
      else {
        local_ac = 0xfffffff6;
      }
      FUN_005e11b0(local_ac);
    }
    uVar1 = FUN_0045bba0();
    uVar1 = FUN_005e1220(uVar1);
    sprintf(local_88,"Team 1 Pilots: %ld/%ld",uVar1);
    FUN_004c0100(DAT_00917580,local_94,local_90,local_a0,local_a4,local_88,DAT_00917550,DAT_0091755c
                 ,DAT_00917584,0,0,0);
    local_90 = local_90 + *(int *)(local_8c + 0x28);
    FUN_00595080(local_94,local_90,*(int *)(local_8c + 0x158) + 3,"Add Pilot",DAT_009175b0,
                 DAT_00917584);
    local_90 = local_90 + *(int *)(local_8c + 0x28);
    FUN_00595080(local_94,local_90,*(int *)(local_8c + 0x158) + 4,"Sub Pilot",DAT_009175b0,
                 DAT_00917584);
    local_90 = *(int *)(local_8c + 0x28) + *(int *)(local_8c + 0x2c) + local_90;
    if (DAT_0091987d != '\0') {
      if (DAT_00919875 == '\0') {
        local_b0 = 1;
      }
      else {
        local_b0 = 10;
      }
      FUN_005e1010(local_b0);
    }
    if (DAT_0091987e != '\0') {
      if (DAT_00919875 == '\0') {
        local_b8 = 0xffffffff;
      }
      else {
        local_b8 = 0xfffffff6;
      }
      FUN_005e1010(local_b8);
    }
    uVar1 = FUN_005e1190();
    uVar1 = FUN_005e10b0(uVar1);
    sprintf(local_88,"Team 2 Scrap: %ld/%ld",uVar1);
    FUN_004c0100(DAT_00917580,local_94,local_90,local_a0,local_a4,local_88,DAT_00917550,DAT_0091755c
                 ,DAT_00917584,0,0,0);
    local_90 = local_90 + *(int *)(local_8c + 0x28);
    FUN_00595080(local_94,local_90,*(int *)(local_8c + 0x158) + 5,"Add Scrap",DAT_0091757c,
                 DAT_00917584);
    local_90 = local_90 + *(int *)(local_8c + 0x28);
    FUN_00595080(local_94,local_90,*(int *)(local_8c + 0x158) + 6,"Sub Scrap",DAT_0091757c,
                 DAT_00917584);
    local_90 = *(int *)(local_8c + 0x28) + *(int *)(local_8c + 0x2c) + local_90;
    if (DAT_0091987f != '\0') {
      if (DAT_00919875 == '\0') {
        local_c0 = 1;
      }
      else {
        local_c0 = 10;
      }
      FUN_005e11b0(local_c0);
    }
    if (DAT_00919880 != '\0') {
      if (DAT_00919875 == '\0') {
        local_c8 = 0xffffffff;
      }
      else {
        local_c8 = 0xfffffff6;
      }
      FUN_005e11b0(local_c8);
    }
    uVar1 = FUN_0045bba0();
    uVar1 = FUN_005e1220(uVar1);
    sprintf(local_88,"Team 2 Pilots: %ld/%ld",uVar1);
    FUN_004c0100(DAT_00917580,local_94,local_90,local_a0,local_a4,local_88,DAT_00917550,DAT_0091755c
                 ,DAT_00917584,0,0,0);
    local_90 = local_90 + *(int *)(local_8c + 0x28);
    FUN_00595080(local_94,local_90,*(int *)(local_8c + 0x158) + 7,"Add Pilot",DAT_0091757c,
                 DAT_00917584);
    local_90 = local_90 + *(int *)(local_8c + 0x28);
    FUN_00595080(local_94,local_90,*(int *)(local_8c + 0x158) + 8,"Sub Pilot",DAT_0091757c,
                 DAT_00917584);
    local_90 = *(int *)(local_8c + 0x28) + *(int *)(local_8c + 0x2c) + local_90;
    FUN_00595080(local_94,local_90,*(undefined4 *)(local_8c + 0x15c),"Cancel",DAT_0091755c,
                 DAT_00917584);
    if (DAT_0091988b != '\0') {
      *(undefined4 *)(local_8c + 0x6c) = 0;
    }
  }
  FUN_0083e885();
  return;
}

