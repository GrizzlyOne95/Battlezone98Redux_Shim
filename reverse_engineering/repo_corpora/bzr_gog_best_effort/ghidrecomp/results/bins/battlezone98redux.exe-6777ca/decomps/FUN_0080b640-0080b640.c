
undefined4 * __thiscall FUN_0080b640(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864ab8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = param_2;
  param_1[1] = param_3;
  uVar2 = vector<>(uVar1);
  local_8 = 0;
  FUN_0080be70(uVar2);
  local_8 = 0xffffffff;
  FUN_00804ff0();
  ExceptionList = local_10;
  return param_1;
}

