
undefined4 FUN_00737940(undefined4 param_1)

{
  uint uVar1;
  undefined4 in_stack_00000040;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085a638;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = 0;
  local_8 = 0;
  FUN_007081e0(&stack0x00000008,in_stack_00000040);
  local_8 = 0xffffffff;
  FUN_006d4f70(uVar1,uVar2 | 1);
  ExceptionList = local_10;
  return param_1;
}

