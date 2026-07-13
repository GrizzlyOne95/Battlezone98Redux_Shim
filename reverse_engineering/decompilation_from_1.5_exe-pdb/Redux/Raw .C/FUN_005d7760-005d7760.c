
void __fastcall FUN_005d7760(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084a278;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = SoldierProcess::vftable;
  local_8 = 0;
  FUN_005fa940(uVar1);
  param_1[7] = 0;
  local_8 = 0xffffffff;
  FUN_00582c30();
  ExceptionList = local_10;
  return;
}

