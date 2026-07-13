
undefined4 * __fastcall FUN_00758b90(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c811;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = CGameNetP2P::vftable;
  FUN_00422260(uVar1);
  local_8 = 0;
  FUN_00422260();
  local_8._0_1_ = 1;
  FUN_0045e380();
  local_8 = CONCAT31(local_8._1_3_,2);
  param_1[0xd] = 0;
  FUN_0056f860();
  ExceptionList = local_10;
  return param_1;
}

