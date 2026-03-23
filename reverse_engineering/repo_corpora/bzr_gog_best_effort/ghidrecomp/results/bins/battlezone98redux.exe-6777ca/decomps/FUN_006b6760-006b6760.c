
undefined4 FUN_006b6760(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_stack_00000020;
  undefined4 in_stack_00000024;
  undefined4 uVar4;
  uint uVar5;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00850bd8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar5 = 0;
  local_8 = 0;
  local_14 = 0;
  while( true ) {
    iVar2 = AddRequestHeaders(in_stack_00000020,local_14);
    if (iVar2 == -1) break;
    uVar4 = in_stack_00000024;
    uVar3 = FUN_004170c0(in_stack_00000024);
    FUN_006c88e0(iVar2,uVar3,uVar4);
    local_14 = FUN_004170c0();
    local_14 = local_14 + iVar2;
  }
  basic_string<>(&stack0x00000008);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar1,uVar5 | 1);
  ExceptionList = local_10;
  return param_1;
}

