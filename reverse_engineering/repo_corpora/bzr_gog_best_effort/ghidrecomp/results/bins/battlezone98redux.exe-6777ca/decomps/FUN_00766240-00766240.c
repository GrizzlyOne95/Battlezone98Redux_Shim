
/* WARNING: Removing unreachable block (ram,0x00766296) */

undefined4 * __thiscall FUN_00766240(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c7c8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00758870(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = CCallback<class_cSteamTicketGen,struct_SteamServersConnected_t,0>::vftable;
  param_1[3] = 0;
  param_1[4] = 0;
  FUN_007662d0(param_2,param_3);
  ExceptionList = local_10;
  return param_1;
}

