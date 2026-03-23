
void __thiscall FUN_00736cb0(int param_1,undefined4 param_2)

{
  undefined1 auStack_a8 [52];
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
  puStack_c = &LAB_0085a4a8;
  local_10 = ExceptionList;
  uStack_6c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_70 = param_2;
  local_68 = auStack_a8;
  local_58 = param_1;
  local_14 = uStack_6c;
  local_64 = FUN_0071e770(param_1 + 8);
  uStack_70 = FUN_00737940(local_54);
  local_8 = 0;
  uStack_74 = 0x736d20;
  local_60 = uStack_70;
  local_5c = uStack_70;
  FUN_007379b0();
  local_8 = 0xffffffff;
  uStack_70 = 0x736d2f;
  FUN_006f2210();
  ExceptionList = local_10;
  uStack_6c = 0x736d44;
  FUN_0083e885();
  return;
}

