
/* WARNING: Removing unreachable block (ram,0x004d09d6) */

void FUN_004d0860(undefined4 param_1,char param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uStack_ac;
  undefined1 local_9c [4];
  undefined1 local_98 [4];
  undefined1 local_94 [12];
  undefined4 *local_88;
  undefined4 local_84;
  undefined4 *local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_6c;
  undefined4 *local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  char *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  uint local_38;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30 [4];
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_24;
  char local_23;
  char local_22;
  char local_20;
  char local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined4 *local_1c;
  char local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00849fb0;
  local_10 = ExceptionList;
  uStack_ac = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_ac;
  ExceptionList = &local_10;
  local_8 = 0;
  local_88 = (undefined4 *)FUN_00422ea0();
  local_28 = *local_88;
  local_2c = *local_1c;
  local_15 = '\x01';
  while (local_48 = (char *)FUN_004242d0(local_28), *local_48 == '\0') {
    local_2c = local_28;
    if (param_2 == '\0') {
      local_58 = FUN_00422f10(local_28);
      local_84 = FUN_004241e0(param_3);
      local_60 = FUN_00422f60(&local_31);
      local_23 = FUN_0046b460(local_84,local_58);
      local_15 = local_23;
    }
    else {
      local_40 = FUN_004241e0(param_3);
      local_50 = FUN_00422f10(local_28);
      local_78 = FUN_00422f60(&local_33);
      local_1f = FUN_0046b460(local_50,local_40);
      local_15 = local_1f == '\0';
      local_38 = (uint)(byte)local_15;
    }
    if (local_15 == '\0') {
      local_68 = (undefined4 *)FUN_004242f0(local_28);
      local_3c = *local_68;
    }
    else {
      local_80 = (undefined4 *)FUN_00417780(local_28);
      local_3c = *local_80;
    }
    local_28 = local_3c;
  }
  _Vector_iterator<>(local_2c,local_1c);
  if (local_15 != '\0') {
    uVar1 = FUN_00420260(local_98);
    local_20 = FUN_004221b0(uVar1);
    if (local_20 != '\0') {
      local_24 = 1;
      local_44 = FUN_00417780(param_3);
      local_4c = FUN_00432fc0(local_94,1,local_2c,local_44,param_4);
      FUN_0042c980(local_4c,&local_24);
      FUN_004d0bb3();
      return;
    }
    FUN_00430570();
  }
  local_5c = FUN_004241e0(param_3);
  local_54 = get();
  local_64 = FUN_00422f10(local_54);
  local_6c = FUN_00422f60(&local_32);
  local_22 = FUN_0046b460(local_64,local_5c);
  if (local_22 == '\0') {
    FUN_004328f0(param_4);
    local_1d = 0;
    FUN_0042c980(local_30,&local_1d);
    FUN_004d0bb3();
    return;
  }
  local_1e = 1;
  local_74 = FUN_00417780(param_3);
  local_7c = FUN_00432fc0(local_9c,local_15,local_2c,local_74,param_4);
  FUN_0042c980(local_7c,&local_1e);
  FUN_004d0bb3();
  return;
}

