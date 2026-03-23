
undefined4 * __thiscall FUN_005ec220(undefined4 *param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c378;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004e96d0(param_2,param_3);
  local_8 = 0;
  *param_1 = Tug::vftable;
  param_1[6] = Tug::vftable;
  param_1[0xc0] = 0;
  param_1[0xc6] = 0;
  param_1[199] = 0;
  FUN_005ec1c0(param_1[0x3d],param_1 + 0xc6,uVar1);
  if (param_1[0xc6] == 0) {
    param_1[0xc6] = param_1[0x3d];
  }
  param_1[0x8a] = 0;
  param_1[0xc1] = *(undefined4 *)(param_3 + 0x5f0);
  param_1[0xc4] = 0x3dcccccd;
  param_1[0xc5] = 0x3dcccccd;
  param_1[0xc2] = 0xffffffff;
  ExceptionList = local_10;
  return param_1;
}

