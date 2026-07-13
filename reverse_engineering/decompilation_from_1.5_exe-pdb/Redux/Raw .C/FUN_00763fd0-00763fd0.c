
/* WARNING: Removing unreachable block (ram,0x00764026) */

undefined4 * __thiscall FUN_00763fd0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d078;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00764080(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = CCallback<class_CSteamP2P,struct_P2PSessionConnectFail_t,0>::vftable;
  param_1[3] = 0;
  param_1[4] = 0;
  FUN_00764100(param_2,param_3);
  ExceptionList = local_10;
  return param_1;
}

