
int FUN_006b2220(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008505d8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_006b2130(param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (iVar1 == 0) {
    uVar2 = FUN_00448470("could not convert calendar time to UTC time");
    local_8 = 0;
    FUN_006d9070(uVar2);
    local_8 = 0xffffffff;
    FUN_004484d0();
  }
  ExceptionList = local_10;
  return iVar1;
}

