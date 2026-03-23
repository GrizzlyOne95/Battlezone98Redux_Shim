
undefined4 * __thiscall FUN_004e6bf0(undefined4 *param_1,int param_2,int param_3,float param_4)

{
  undefined4 uVar1;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a4a8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_3 == 0) {
    local_18 = (**(code **)(*(int *)(param_2 + 0x18) + 0xc))();
  }
  else {
    local_18 = (**(code **)(*(int *)(param_3 + 0x18) + 0xc))(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  }
  FUN_004e5770(param_2,local_18);
  local_8 = 0;
  *param_1 = GoNear::vftable;
  if (param_3 == 0) {
    param_1[3] = 0xd;
  }
  else {
    uVar1 = FUN_00477590(param_3);
    param_1[5] = uVar1;
    *(undefined1 *)((int)param_1 + 0x13e) = 1;
    param_1[0x53] = param_4 * param_4;
    *(undefined1 *)(param_1 + 0x54) = 0;
    param_1[0x55] = 0;
  }
  ExceptionList = local_10;
  return param_1;
}

