
void __fastcall FUN_00471550(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008475f8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = APCProcess::vftable;
  local_8 = 0;
  FUN_005fa940(uVar1);
  param_1[7] = 0;
  local_8 = 0xffffffff;
  FID_conflict__ctype<char>();
  ExceptionList = local_10;
  return;
}

