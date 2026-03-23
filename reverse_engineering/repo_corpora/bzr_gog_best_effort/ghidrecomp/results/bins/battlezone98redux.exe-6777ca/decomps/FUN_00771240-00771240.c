
undefined4 FUN_00771240(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085dfc8;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar4 = 0;
  local_8 = 2;
  while( true ) {
    cVar1 = FID_conflict_operator__(&stack0x00000014);
    if (cVar1 == '\0') break;
    FUN_00770860();
    uVar3 = FUN_0076f9d0();
    uVar3 = FUN_00417780(uVar3);
    FUN_00770860(uVar3);
    FUN_0076f9d0();
    FUN_0076be70(uVar3);
  }
  FUN_004bbb20(&stack0x00000020);
  local_8._0_1_ = 1;
  FUN_004bb3b0(uVar2,uVar4 | 1);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return param_1;
}

