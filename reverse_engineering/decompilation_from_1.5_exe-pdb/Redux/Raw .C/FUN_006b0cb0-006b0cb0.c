
void __thiscall FUN_006b0cb0(int param_1,char param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 local_58 [8];
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 *local_40;
  undefined4 *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  uint local_30;
  int local_2c;
  int local_28;
  int local_24;
  uint local_20;
  int local_1c;
  int local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008504e8;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = param_1;
  FUN_006c8ce0(param_1 + 0x18);
  local_8 = 0;
  if (*(char *)(local_18 + 0xd0) == '\0') {
    for (local_28 = 0; local_28 < 3; local_28 = local_28 + 1) {
      FUN_006ae650();
    }
    uVar3 = get(uVar2);
    FUN_006ae670(uVar3);
    local_20 = 0;
    cVar1 = FUN_006acb40();
    local_11 = cVar1 == '\0';
    local_30 = (uint)(byte)local_11;
    for (local_1c = 0; local_1c < 3; local_1c = local_1c + 1) {
      if ((local_11 == '\0') && (cVar1 = FUN_006c92e0(), cVar1 != '\0')) {
        local_34 = 0;
      }
      else {
        local_34 = 1;
      }
      local_11 = (char)local_34;
      FUN_006ae6f0(local_18 + 0x38 + local_1c * 0x1c,param_3);
      uVar2 = FUN_004714e0();
      if (local_20 < uVar2) {
        local_20 = FUN_004714e0();
      }
    }
    if ((local_11 == '\0') && (cVar1 = FUN_006c92e0(), cVar1 != '\0')) {
      local_38 = 0;
    }
    else {
      local_38 = 1;
    }
    local_11 = (char)local_38;
    FUN_006ae6f0(local_18 + 0x8c,param_3);
    uVar2 = FUN_004714e0();
    if (local_20 < uVar2) {
      local_20 = FUN_004714e0();
    }
    FUN_006ae6f0(local_18 + 0x8c,param_3);
    uVar2 = FUN_004714e0();
    if (local_20 < uVar2) {
      local_20 = FUN_004714e0();
    }
    if ((param_2 == '\0') && (local_11 == '\0')) {
      local_8 = 0xffffffff;
      FUN_006c8d50();
    }
    else {
      local_50 = 0;
      local_4c = 0;
      if (param_2 == '\0') {
        local_3c = &local_50;
      }
      else {
        local_3c = (undefined4 *)FUN_006b11f0(&local_50);
      }
      local_40 = local_3c;
      FUN_006c8de0();
      FUN_004fbb60();
      uVar3 = get(local_40,local_58);
      uVar3 = get(uVar3);
      uVar3 = get(uVar3);
      local_2c = FUN_006af8f0(local_20 + 1,uVar3);
      if (0 < local_2c) {
        uVar3 = get();
        cVar1 = FUN_006ae780(uVar3);
        if (cVar1 != '\0') {
          FUN_006b0580();
          local_2c = local_2c + -1;
        }
      }
      FUN_006c8db0();
      if (0 < local_2c) {
        FUN_006ae7c0(local_18 + 0x8c,param_3);
        FUN_006ae7c0(local_18 + 0x8c,param_3);
        for (local_24 = 2; -1 < local_24; local_24 = local_24 + -1) {
          FUN_006ae7c0(local_18 + 0x38 + local_24 * 0x1c,param_3);
        }
      }
      FUN_006acbe0(param_3);
      local_8 = 0xffffffff;
      FUN_006c8d50();
    }
  }
  else {
    local_8 = 0xffffffff;
    FUN_006c8d50();
  }
  ExceptionList = local_10;
  return;
}

