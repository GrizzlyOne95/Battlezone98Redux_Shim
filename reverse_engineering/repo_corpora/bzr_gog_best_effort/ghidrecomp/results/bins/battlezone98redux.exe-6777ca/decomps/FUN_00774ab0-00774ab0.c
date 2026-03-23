
/* WARNING: Removing unreachable block (ram,0x00774b06) */

undefined4 * __thiscall FUN_00774ab0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fef8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006ab0e0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = CCallback<class_cWorkshopSteam,struct_DownloadItemResult_t,0>::vftable;
  param_1[3] = 0;
  param_1[4] = 0;
  FUN_00774ce0(param_2,param_3);
  ExceptionList = local_10;
  return param_1;
}

