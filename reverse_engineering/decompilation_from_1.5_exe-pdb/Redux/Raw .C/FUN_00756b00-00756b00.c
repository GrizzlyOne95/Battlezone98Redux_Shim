
void FUN_00756b00(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a01;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = forward<>(0x50,param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (iVar1 != 0) {
    FUN_00756b80(param_2);
  }
  ExceptionList = local_10;
  return;
}

