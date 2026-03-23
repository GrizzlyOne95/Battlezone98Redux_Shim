
undefined4 __thiscall FUN_0081be00(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845ab8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_00417780(param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  uVar1 = FUN_00433f60(uVar1);
  basic_string<>(uVar1);
  local_8 = 0;
  FUN_0081be80();
  ExceptionList = local_10;
  return param_1;
}

