
void FUN_007ea5d0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863ef1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = forward<>(7,param_3,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (iVar1 != 0) {
    FUN_007dd830(&param_1);
  }
  ExceptionList = local_10;
  return;
}

