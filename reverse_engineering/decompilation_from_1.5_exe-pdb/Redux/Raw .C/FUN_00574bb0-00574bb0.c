
undefined4 * __fastcall FUN_00574bb0(undefined4 *param_1)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b808;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00508f40(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = NetPlayerMgr::vftable;
  iVar1 = FUN_007659f0();
  if (iVar1 != 0) {
    FUN_00758af0(0x7a,param_1);
  }
  ExceptionList = local_10;
  return param_1;
}

