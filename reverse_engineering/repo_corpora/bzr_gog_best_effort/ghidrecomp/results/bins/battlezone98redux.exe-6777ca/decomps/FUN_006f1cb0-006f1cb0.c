
void FUN_006f1cb0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  _ATL_WIN_MODULE70 local_bc [104];
  undefined1 local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855153;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_006f4bc0(param_3);
  local_8 = 0;
  uVar1 = FUN_006b2d70(uVar2);
  FUN_006f4c30(param_1,param_2,uVar1,local_54);
  local_8._0_1_ = 1;
  uVar5 = 1;
  uVar4 = 0;
  uVar3 = FUN_004fbb60(0,1);
  FUN_006f4cc0(uVar3,uVar4,uVar5);
  local_8 = (uint)local_8._1_3_ << 8;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70(local_bc);
  FUN_00417c60();
  local_8 = 0xffffffff;
  FUN_006f2320();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

