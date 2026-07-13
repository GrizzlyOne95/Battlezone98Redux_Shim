
undefined4 * __thiscall FUN_005d9670(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847938;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00611300(param_2,param_3);
  local_8 = 0;
  *param_1 = SpecialItem::vftable;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined1 *)((int)param_1 + 0xc1) = 0;
  param_1[0x31] = 0;
  param_1[0x32] = 0;
  uVar2 = FUN_00479f30(param_1[6],uVar1);
  param_1[0x33] = uVar2;
  param_1[0x34] = param_1[0x2a];
  param_1[0x35] = 0;
  ExceptionList = local_10;
  return param_1;
}

