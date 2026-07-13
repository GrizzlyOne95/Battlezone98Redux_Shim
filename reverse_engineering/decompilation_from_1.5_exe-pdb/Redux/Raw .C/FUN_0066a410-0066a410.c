
undefined4 __fastcall FUN_0066a410(undefined4 param_1)

{
  undefined4 uVar1;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e900;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_0066bb70(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_0066bab0(&local_11,uVar1);
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_0066ad70();
  ExceptionList = local_10;
  return param_1;
}

