
int __thiscall FUN_00704d90(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856d88;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006b2b10(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  uVar1 = FUN_006ac540(param_2);
  *(undefined4 *)(param_1 + 0x20) = uVar1;
  FUN_00417c60();
  FUN_0070f800(param_1);
  ExceptionList = local_10;
  return param_1;
}

