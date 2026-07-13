
undefined4 * __thiscall FUN_00700c20(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00856568;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  *param_1 = param_2;
  FUN_00700b40(&stack0x00000008);
  local_8 = 0xffffffff;
  FUN_006e4380(uVar1);
  ExceptionList = local_10;
  return param_1;
}

