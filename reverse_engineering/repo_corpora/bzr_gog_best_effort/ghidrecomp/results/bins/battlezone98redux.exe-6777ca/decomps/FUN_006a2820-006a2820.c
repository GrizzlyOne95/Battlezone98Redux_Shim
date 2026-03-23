
undefined4 * __thiscall FUN_006a2820(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b438;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00461580(param_2,0);
  local_8 = 0;
  *param_1 = FindSendPoints::vftable;
  iVar2 = DAT_02c00a94 * DAT_02c00ed8;
  DAT_009310a8 = FUN_0083d92c(iVar2,uVar1);
  param_1[8] = 0;
  while ((int)param_1[8] < iVar2) {
    *(undefined1 *)(DAT_009310a8 + param_1[8]) = 0xff;
    param_1[8] = param_1[8] + 1;
  }
  param_1[6] = 0xffffffff;
  param_1[7] = 0xffffffff;
  param_1[8] = 0xffffffff;
  ExceptionList = local_10;
  return param_1;
}

