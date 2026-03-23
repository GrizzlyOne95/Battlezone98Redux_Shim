
undefined4 FUN_0070e300(undefined4 param_1)

{
  uint uVar1;
  undefined4 in_stack_00000038;
  undefined4 in_stack_0000003c;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00856568;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = 0;
  local_8 = 0;
  FUN_00710810(&stack0x00000008,in_stack_00000038,in_stack_0000003c);
  local_8 = 0xffffffff;
  FUN_006e4380(uVar1,uVar2 | 1);
  ExceptionList = local_10;
  return param_1;
}

