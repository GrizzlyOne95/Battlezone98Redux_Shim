
undefined4 FUN_007103a0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008554c1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = forward<>(4,param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (iVar1 != 0) {
    uVar2 = FUN_00417780(param_2);
    FUN_0071ad30(uVar2);
  }
  ExceptionList = local_10;
  return 6;
}

