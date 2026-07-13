
undefined4 * __thiscall FUN_004e49b0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849568;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004e58d0(param_2,param_3);
  local_8 = 0;
  *param_1 = GotoGeyser::vftable;
  FUN_005f91e0(param_2,0xf,0,uVar1);
  *(undefined1 *)((int)param_1 + 0x13e) = 1;
  *(undefined1 *)(param_1 + 0x53) = 0;
  uVar2 = FUN_00462380();
  param_1[0x54] = uVar2;
  ExceptionList = local_10;
  return param_1;
}

