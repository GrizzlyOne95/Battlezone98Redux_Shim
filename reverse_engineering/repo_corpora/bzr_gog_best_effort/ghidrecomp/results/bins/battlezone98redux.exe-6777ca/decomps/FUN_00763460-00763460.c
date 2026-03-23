
undefined4 * __fastcall FUN_00763460(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085cf88;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00758b90(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_00763740(0);
  *param_1 = CGalaxyP2P::vftable;
  param_1[0xe] = CGalaxyP2P::vftable;
  ExceptionList = local_10;
  return param_1;
}

