
undefined4 * __thiscall FUN_005f2250(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c378;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004e96d0(param_2,param_3);
  local_8 = 0;
  *param_1 = TurretTank::vftable;
  param_1[6] = TurretTank::vftable;
  param_1[0x8a] = 0;
  param_1[0xc0] = 0;
  param_1[0xc1] = 0xffffffff;
  param_1[0xc2] = 0xf149f2ca;
  param_1[0xc3] = 0;
  param_1[200] = 0;
  FUN_005f2130(param_1[0x3d]);
  *(undefined1 *)(param_1 + 0xc9) = 1;
  param_1[0xda] = 0;
  if (param_1[0x68] != 0) {
    FUN_004d9950(0);
  }
  param_1[0xdb] = 0;
  ExceptionList = local_10;
  return param_1;
}

