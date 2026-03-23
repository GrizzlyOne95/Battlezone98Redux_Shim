
undefined4 * __fastcall FUN_006aa770(undefined4 *param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fdf9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00764160(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = CAchievementsSteam::vftable;
  FUN_006aaf10(param_1,FUN_006aaa00);
  local_8._0_1_ = 1;
  FUN_006aafc0(param_1,FUN_006aabf0);
  local_8._0_1_ = 2;
  FUN_006ab050(param_1,FUN_006aad00);
  local_8 = CONCAT31(local_8._1_3_,3);
  iVar1 = FUN_006aa1f0();
  if (iVar1 != 0) {
    piVar2 = (int *)FUN_006aa1f0();
    uVar3 = (**(code **)(*piVar2 + 0x24))();
    param_1[4] = uVar3;
    param_1[5] = 0;
    FUN_006aa960();
  }
  ExceptionList = local_10;
  return param_1;
}

