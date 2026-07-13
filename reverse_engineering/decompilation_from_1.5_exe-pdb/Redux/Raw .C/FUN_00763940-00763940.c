
undefined4 * __fastcall FUN_00763940(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085cff3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00758b90(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = CSteamP2P::vftable;
  FUN_00763f40(param_1,&LAB_00763d90);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00763fd0(param_1,FUN_00763c90);
  ExceptionList = local_10;
  return param_1;
}

