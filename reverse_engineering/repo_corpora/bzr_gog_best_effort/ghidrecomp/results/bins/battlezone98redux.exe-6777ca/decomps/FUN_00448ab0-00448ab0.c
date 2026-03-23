
void FUN_00448ab0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846188;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_00448a80(0,param_1,param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (iVar1 == 0) {
    uVar2 = FUN_00448a00();
    local_8 = 0;
    FUN_00449df0(uVar2);
    local_8 = 0xffffffff;
    FUN_00448a30();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

