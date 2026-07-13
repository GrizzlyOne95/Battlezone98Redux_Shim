
undefined4 * __thiscall FUN_0041ab20(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844bc8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00418d40(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = TouchInputButton::vftable;
  basic_string<>();
  param_1[0x25] = param_2;
  uVar1 = FUN_0068bed0("button_fire");
  param_1[0x1b] = uVar1;
  ExceptionList = local_10;
  return param_1;
}

