
/* WARNING: Removing unreachable block (ram,0x00763f96) */

undefined4 * __thiscall FUN_00763f40(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d048;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00764060(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = CCallback<class_CSteamP2P,struct_P2PSessionRequest_t,0>::vftable;
  param_1[3] = 0;
  param_1[4] = 0;
  FUN_007640a0(param_2,param_3);
  ExceptionList = local_10;
  return param_1;
}

