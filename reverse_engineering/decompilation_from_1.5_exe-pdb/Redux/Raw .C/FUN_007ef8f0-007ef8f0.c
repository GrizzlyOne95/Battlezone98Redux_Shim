
void FUN_007ef8f0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863fb0;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007ed7e0(param_1,0xffffffff);
  local_8 = 0;
  FUN_007ed940(param_1);
  local_8._0_1_ = 1;
  cVar1 = FUN_007f0470(param_1,param_2,param_3,param_4);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007ed6c0(uVar2);
  if (cVar1 != '\0') {
    FUN_007ed8e0(0xffffffff,1);
  }
  local_8 = 0xffffffff;
  FUN_007ed880();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

