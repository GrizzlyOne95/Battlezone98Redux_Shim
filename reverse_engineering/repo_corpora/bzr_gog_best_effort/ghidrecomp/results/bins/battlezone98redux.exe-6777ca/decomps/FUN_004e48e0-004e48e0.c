
undefined4 * __thiscall FUN_004e48e0(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849568;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = (**(code **)(*(int *)(param_2 + 0x18) + 0xc))(0,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  uVar1 = FUN_004e4750(uVar1);
  FUN_004e58d0(param_2,uVar1);
  local_8 = 0;
  *param_1 = GotoGeyser::vftable;
  if (param_1[5] == 0) {
    FUN_005f91e0(param_2,0xe,0);
  }
  else {
    FUN_005f91e0(param_2,0xf,0);
    *(undefined1 *)((int)param_1 + 0x13e) = 1;
    *(undefined1 *)(param_1 + 0x53) = 0;
    param_1[0x54] = 0;
  }
  ExceptionList = local_10;
  return param_1;
}

