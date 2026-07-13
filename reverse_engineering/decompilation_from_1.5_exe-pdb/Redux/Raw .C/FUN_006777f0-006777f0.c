
void FUN_006777f0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008499b1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = forward<>(0x68,param_3,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (iVar1 != 0) {
    uVar2 = FUN_00417780(param_4);
    FUN_00677960(uVar2);
  }
  ExceptionList = local_10;
  return;
}

