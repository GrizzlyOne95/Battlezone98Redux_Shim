
void FUN_00734060(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085a0e0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  while( true ) {
    if (param_4 == 0) break;
    uVar1 = FUN_00422e60();
    uVar2 = FUN_006ef1a0(&param_5);
    FUN_006ef1f0(param_2,uVar2,uVar1);
    FUN_006cc780();
    param_5 = param_5 + 0x20;
    param_4 = param_4 + -1;
  }
  FUN_0073412e();
  return;
}

