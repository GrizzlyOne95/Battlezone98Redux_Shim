
undefined4 FUN_0044fdc0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  uint uStack_94;
  undefined1 local_80 [4];
  undefined1 local_7c [4];
  undefined1 local_78 [20];
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
  undefined4 *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 local_24;
  undefined1 local_18;
  char local_17;
  char local_16;
  char local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846990;
  local_10 = ExceptionList;
  uStack_94 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_94;
  ExceptionList = &local_10;
  FUN_00422170();
  local_8 = 0;
  local_34 = FUN_00417780(param_2);
  local_38 = FUN_0044eea0(local_34);
  local_2c = local_38;
  local_3c = (undefined4 *)FUN_0044f020(local_78,local_38);
  local_24 = *local_3c;
  do {
    local_40 = FUN_0044eff0(local_7c,local_2c);
    local_15 = FUN_00420f10(local_40);
    if (local_15 == '\0') goto LAB_0044ff59;
    local_44 = FUN_0044f170();
    local_48 = FUN_0042de50();
    local_4c = FUN_00417780(local_48);
    local_50 = FUN_00417780(param_2);
    local_16 = FUN_0044ef20(local_50,local_4c);
  } while (local_16 != '\0');
  local_58 = FUN_00417780(param_2);
  local_54 = FUN_0042de50();
  local_5c = FUN_00417780(local_54);
  local_17 = FUN_0044ef20(local_5c,local_58);
  if (local_17 == '\0') {
    FUN_004501f0(param_3);
    local_18 = 0;
    local_60 = local_24;
    local_64 = FUN_0044ec90(local_80,local_24);
    FUN_0042c980(local_64,&local_18);
    ExceptionList = local_10;
    return param_1;
  }
  FUN_0042da80();
LAB_0044ff59:
  uVar1 = FUN_0044ff76();
  return uVar1;
}

