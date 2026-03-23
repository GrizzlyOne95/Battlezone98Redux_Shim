
undefined4 __thiscall FUN_007cec80(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_24 [12];
  uint local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085de78;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = 0;
  local_14 = param_1;
  _String_const_iterator<>(param_1);
  local_8 = 0;
  FUN_007332d0(uVar1);
  _String_const_iterator<>(local_24);
  local_18 = local_18 | 1;
  local_8 = 0xffffffff;
  FUN_004bb3d0();
  ExceptionList = local_10;
  return param_2;
}

