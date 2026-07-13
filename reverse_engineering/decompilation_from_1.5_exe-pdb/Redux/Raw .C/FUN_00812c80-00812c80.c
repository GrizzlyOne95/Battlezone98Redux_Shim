
void FUN_00812c80(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864c51;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007fb800();
  local_8 = 0;
  uVar1 = FUN_006d0d10();
  iVar2 = forward<>(4,uVar1);
  local_8._0_1_ = 1;
  if (iVar2 != 0) {
    uVar1 = FUN_00417780(param_1);
    FUN_00813ab0(uVar1);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00812d41();
  return;
}

