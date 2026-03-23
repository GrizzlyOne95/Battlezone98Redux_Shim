
void FUN_007311e0(void)

{
  uint uVar1;
  int iVar2;
  int *in_stack_0000001c;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00859d30;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  iVar2 = FUN_00732e10(&stack0x00000004);
  *in_stack_0000001c = iVar2 + *in_stack_0000001c;
  local_8 = local_8 & 0xffffff00;
  FUN_004bb3b0(uVar1);
  local_8 = 0xffffffff;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return;
}

