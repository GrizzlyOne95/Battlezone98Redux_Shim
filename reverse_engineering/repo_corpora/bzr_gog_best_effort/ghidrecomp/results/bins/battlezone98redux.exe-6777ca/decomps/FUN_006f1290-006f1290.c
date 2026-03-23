
undefined4 FUN_006f1290(undefined4 param_1)

{
  uint uVar1;
  undefined4 in_stack_00000070;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00854f81;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = 0;
  local_8 = 1;
  FUN_006f44e0(&stack0x00000008,in_stack_00000070);
  local_8 = local_8 & 0xffffff00;
  FUN_006e0630(uVar1,uVar2 | 1);
  ExceptionList = local_10;
  return param_1;
}

