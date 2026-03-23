
int FUN_007f0c40(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855ad8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_007f1590(param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (iVar1 == 0) {
    uVar2 = FUN_006ff730();
    local_8 = 0;
    FUN_0070ad90(uVar2);
    local_8 = 0xffffffff;
    FUN_004484d0();
  }
  ExceptionList = local_10;
  return iVar1;
}

