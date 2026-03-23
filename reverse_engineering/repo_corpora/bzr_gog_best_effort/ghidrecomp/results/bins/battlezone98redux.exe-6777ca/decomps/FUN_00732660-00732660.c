
void FUN_00732660(undefined4 param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00859f40;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  while( true ) {
    if (param_3 == 0) break;
    uVar1 = FUN_006ef1a0(&param_4);
    FUN_00733fe0(param_1,uVar1,param_2);
    param_2 = param_2 + 0x20;
    param_4 = param_4 + 0x20;
    param_3 = param_3 + -1;
  }
  FUN_00732724();
  return;
}

