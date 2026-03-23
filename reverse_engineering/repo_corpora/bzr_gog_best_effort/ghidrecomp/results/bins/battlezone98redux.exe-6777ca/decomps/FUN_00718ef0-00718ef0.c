
undefined4 FUN_00718ef0(undefined4 param_1)

{
  uint uVar1;
  undefined4 in_stack_00000040;
  undefined4 in_stack_00000044;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008582b8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = 0;
  local_8 = 0;
  FUN_0071c2d0(&stack0x00000008,in_stack_00000040,in_stack_00000044);
  local_8 = 0xffffffff;
  ~input_processor<>(uVar1,uVar2 | 1);
  ExceptionList = local_10;
  return param_1;
}

