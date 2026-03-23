
void FUN_00717710(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 auStack_5c [4];
  undefined4 uStack_58;
  undefined1 *puStack_54;
  undefined1 *puStack_50;
  undefined4 uStack_4c;
  uint uStack_48;
  undefined1 local_44 [12];
  undefined1 local_38 [12];
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 *local_24;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858168;
  local_10 = ExceptionList;
  uStack_48 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_4c = param_2;
  puStack_50 = local_1c;
  puStack_54 = (undefined1 *)0x717742;
  puVar1 = (undefined4 *)FUN_006ff2a0();
  uStack_4c = *puVar1;
  puStack_50 = (undefined1 *)param_2;
  puStack_54 = local_20;
  uStack_58 = 0x717755;
  puVar1 = (undefined4 *)FUN_006ff280();
  puStack_50 = (undefined1 *)*puVar1;
  puStack_54 = local_44;
  uStack_58 = 0x717767;
  local_18 = FUN_004bb570();
  local_8 = 0;
  local_24 = auStack_5c;
  local_14 = local_18;
  local_28 = _String_const_iterator<>(local_18);
  local_2c = FUN_007233a0(local_38);
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return;
}

