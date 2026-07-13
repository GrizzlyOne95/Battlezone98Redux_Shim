
void FUN_00723d00(undefined4 param_1,undefined4 param_2)

{
  undefined1 auStack_54 [4];
  undefined4 uStack_50;
  undefined1 *puStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  uint uStack_40;
  undefined1 local_3c [12];
  undefined1 local_30 [12];
  undefined4 local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858df8;
  local_10 = ExceptionList;
  uStack_40 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_44 = param_2;
  uStack_48 = 0x723d2e;
  uStack_44 = FUN_0070c5b0();
  uStack_48 = param_2;
  puStack_4c = (undefined1 *)0x723d3b;
  uStack_48 = FUN_0070c590();
  puStack_4c = local_3c;
  uStack_50 = 0x723d4b;
  local_18 = FUN_004bb570();
  local_8 = 0;
  local_1c = auStack_54;
  local_14 = local_18;
  local_20 = _String_const_iterator<>(local_18);
  local_24 = FUN_007291b0(local_30);
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return;
}

