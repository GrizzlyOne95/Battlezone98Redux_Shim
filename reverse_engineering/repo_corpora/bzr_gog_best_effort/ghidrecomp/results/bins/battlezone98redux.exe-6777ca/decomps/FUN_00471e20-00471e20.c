
undefined4 * __thiscall FUN_00471e20(undefined4 *param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847688;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_005fe690(param_2,param_3);
  local_8 = 0;
  *param_1 = APCAttack::vftable;
  param_1[2] = 1;
  if (param_3 == 0) {
    param_1[3] = 0xd;
  }
  else {
    puVar2 = (undefined4 *)(**(code **)(*(int *)(param_3 + 0x18) + 0xc))(uVar1);
    param_1[10] = *puVar2;
    param_1[0xb] = puVar2[1];
    param_1[0xc] = puVar2[2];
    param_1[3] = 2;
  }
  ExceptionList = local_10;
  return param_1;
}

