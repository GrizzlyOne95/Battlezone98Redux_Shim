
/* WARNING: Removing unreachable block (ram,0x005d34d9) */
/* WARNING: Removing unreachable block (ram,0x005d34f3) */
/* WARNING: Removing unreachable block (ram,0x005d3516) */
/* WARNING: Removing unreachable block (ram,0x005d3564) */
/* WARNING: Removing unreachable block (ram,0x005d34f1) */
/* WARNING: Removing unreachable block (ram,0x005d356c) */
/* WARNING: Removing unreachable block (ram,0x005d35e7) */
/* WARNING: Removing unreachable block (ram,0x005d3635) */

void FUN_005d32b0(undefined4 param_1,char param_2,undefined4 param_3,undefined1 param_4)

{
  uint uStack_ac;
  undefined1 local_90 [4];
  undefined4 local_8c;
  undefined4 *local_88;
  undefined4 *local_84;
  undefined4 *local_80;
  undefined4 local_78;
  undefined4 local_70;
  undefined4 *local_68;
  undefined4 local_60;
  undefined4 *local_58;
  undefined4 *local_50;
  char *local_48;
  undefined4 *local_40;
  undefined4 local_3c;
  uint local_38;
  undefined1 local_33 [2];
  undefined1 local_31 [5];
  undefined4 local_2c;
  undefined4 local_28;
  char local_23;
  undefined1 local_21 [2];
  char local_1f;
  undefined4 *local_1c;
  char local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084c9b0;
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
      local_58 = (undefined4 *)FUN_00422f10(local_28);
      local_84 = (undefined4 *)FUN_004241e0(param_3);
      local_60 = FUN_005d36a0(local_31);
      local_23 = FUN_005d3020(*local_84,local_84[1],local_84[2],*local_58,local_58[1],local_58[2]);
      local_15 = local_23;
    }
    else {
      local_40 = (undefined4 *)FUN_004241e0(param_3);
      local_50 = (undefined4 *)FUN_00422f10(local_28);
      local_78 = FUN_005d36a0(local_33);
      local_1f = FUN_005d3020(*local_50,local_50[1],local_50[2],*local_40,local_40[1],local_40[2]);
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
  local_21[0] = 1;
  local_8c = FUN_00417780(param_3);
  local_70 = FUN_005d36c0(local_90,local_15,local_2c,local_8c,param_4);
  FUN_0042c980(local_70,local_21);
  FUN_005d3689();
  return;
}

