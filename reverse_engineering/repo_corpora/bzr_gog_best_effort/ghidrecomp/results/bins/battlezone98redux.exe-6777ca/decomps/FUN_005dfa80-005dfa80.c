
void __fastcall FUN_005dfa80(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00847938;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = TargetingGun::vftable;
  local_8 = 0;
  if (param_1[0x36] != 0) {
    FUN_005df1f0(0);
  }
  local_8 = 0xffffffff;
  FUN_00611500(uVar1);
  ExceptionList = local_10;
  return;
}

