
void __thiscall FUN_006fedd0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 auStack_a4 [48];
  undefined4 uStack_74;
  undefined4 uStack_70;
  uint uStack_6c;
  undefined1 *local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  int local_58;
  undefined1 local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856038;
  local_10 = ExceptionList;
  uStack_6c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_70 = param_3;
  uStack_74 = param_2;
  local_68 = auStack_a4;
  local_58 = param_1;
  local_14 = uStack_6c;
  local_64 = FUN_00700b40(param_1 + 8);
  uStack_70 = FUN_0070e300(local_54);
  local_8 = 0;
  uStack_74 = 0x6fee42;
  local_60 = uStack_70;
  local_5c = uStack_70;
  FUN_0070e370();
  local_8 = 0xffffffff;
  uStack_70 = 0x6fee51;
  FUN_006f23a0();
  ExceptionList = local_10;
  uStack_6c = 0x6fee66;
  FUN_0083e885();
  return;
}

