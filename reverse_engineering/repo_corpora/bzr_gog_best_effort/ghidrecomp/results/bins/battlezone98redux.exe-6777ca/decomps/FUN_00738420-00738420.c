
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_00738420(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855c68;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = forward<>(0x38,param_3,0,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (iVar1 != 0) {
    uVar2 = FUN_00417780(param_4);
    FUN_007384c0(uVar2);
  }
  ExceptionList = local_10;
  return;
}

