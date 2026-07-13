
undefined4 __thiscall FUN_007bb620(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e298;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00662ea0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_006673e0();
  FUN_006673e0();
  uVar1 = FUN_00417780(param_2);
  FUN_00773a70(uVar1);
  uVar1 = FUN_00417780(param_2 + 0x18);
  FUN_00450be0(uVar1);
  uVar1 = FUN_00417780(param_2 + 0x20);
  FUN_00450be0(uVar1);
  ExceptionList = local_10;
  return param_1;
}

