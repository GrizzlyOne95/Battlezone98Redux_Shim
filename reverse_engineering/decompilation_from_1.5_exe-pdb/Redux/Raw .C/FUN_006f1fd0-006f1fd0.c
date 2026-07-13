
void FUN_006f1fd0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  _ATL_WIN_MODULE70 local_b4 [96];
  undefined1 local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008551d3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_006f4fc0(param_4);
  local_8 = 0;
  FUN_006f5030(param_1,param_2,param_3,local_54);
  local_8._0_1_ = 1;
  uVar4 = 1;
  uVar3 = 0;
  uVar2 = FUN_004fbb60(0,1,uVar1);
  FUN_006f50c0(uVar2,uVar3,uVar4);
  local_8 = (uint)local_8._1_3_ << 8;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70(local_b4);
  FUN_00417c60();
  local_8 = 0xffffffff;
  FUN_006f2320();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

