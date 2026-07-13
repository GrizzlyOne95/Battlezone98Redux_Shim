
void __thiscall
FUN_007e4600(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 local_e0 [104];
  undefined1 local_78 [100];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863be3;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = param_5;
  uVar1 = FUN_007e2fb0(param_3,param_4,param_5,local_14,param_1);
  uVar2 = FUN_007e7180(local_78,uVar1,param_4,uVar2);
  local_8 = 0;
  uVar2 = FUN_007e71c0(local_e0,uVar2);
  local_8._0_1_ = 1;
  FUN_007e71f0(param_2,uVar2,param_5);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007dbbf0();
  local_8 = 0xffffffff;
  FUN_007dbc30();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

