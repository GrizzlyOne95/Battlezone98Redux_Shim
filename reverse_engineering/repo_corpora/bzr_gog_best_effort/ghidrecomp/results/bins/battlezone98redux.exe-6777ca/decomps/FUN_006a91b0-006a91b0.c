
undefined4 * __fastcall FUN_006a91b0(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fc4e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00764160(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_006a9a90(0);
  local_8._0_1_ = 1;
  FUN_006a9c00(0);
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_006a9d70(0);
  *param_1 = CAchievementsGog::vftable;
  param_1[4] = CAchievementsGog::vftable;
  param_1[6] = CAchievementsGog::vftable;
  param_1[8] = CAchievementsGog::vftable;
  *(undefined1 *)(param_1 + 3) = 1;
  ExceptionList = local_10;
  return param_1;
}

