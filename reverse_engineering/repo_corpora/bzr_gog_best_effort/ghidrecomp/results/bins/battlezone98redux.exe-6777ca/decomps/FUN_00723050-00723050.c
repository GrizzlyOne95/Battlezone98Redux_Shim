
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_00723050(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855c68;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = forward<>(0x20,param_3,0,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (iVar1 != 0) {
    FUN_006cc3b0();
  }
  ExceptionList = local_10;
  return;
}

