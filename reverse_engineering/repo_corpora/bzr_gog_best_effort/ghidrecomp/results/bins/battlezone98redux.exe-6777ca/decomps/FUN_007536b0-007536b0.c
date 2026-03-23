
undefined4 * __fastcall FUN_007536b0(undefined4 *param_1)

{
  uint uVar1;
  undefined1 *puVar2;
  undefined4 local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c1d6;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cNetFriends::vftable;
  local_14 = param_1;
  vector<>(uVar1);
  local_8 = 0;
  FUN_0073a6b0();
  FUN_0045e380();
  local_8 = CONCAT31(local_8._1_3_,1);
  local_18 = 0;
  puVar2 = (undefined1 *)FUN_00753940(&local_18);
  *puVar2 = 1;
  ExceptionList = local_10;
  return local_14;
}

