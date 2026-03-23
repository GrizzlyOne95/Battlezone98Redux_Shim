
undefined4 * __thiscall FUN_004d3790(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
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
  *param_1 = FollowTask::vftable;
  if (param_1[5] == 0) {
    param_1[0x47] = 0;
    param_1[2] = 0xd;
  }
  else {
    uVar2 = FUN_004d3130(param_3,uVar1);
    param_1[0x47] = uVar2;
    FUN_004d3260(param_2);
    param_1[0x44] = 0;
    param_1[0x45] = 0xc1a00000;
    param_1[2] = 1;
    param_1[3] = 1;
  }
  ExceptionList = local_10;
  return param_1;
}

