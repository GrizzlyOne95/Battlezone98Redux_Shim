
undefined4 * __fastcall FUN_00773aa0(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e206;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00767a30(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cWorkshopSteam::vftable;
  FUN_00774a20(param_1,FUN_00773c10);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00774ab0(param_1,FUN_00773bd0);
  ExceptionList = local_10;
  return param_1;
}

