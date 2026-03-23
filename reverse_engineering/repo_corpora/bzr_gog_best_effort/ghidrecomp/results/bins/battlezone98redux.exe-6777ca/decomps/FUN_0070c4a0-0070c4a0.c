
void FUN_0070c4a0(undefined4 param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00857630;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  for (; param_2 != param_3; param_2 = param_2 + 0x20) {
    uVar1 = FUN_00417780(param_2);
    uVar2 = FUN_006ef1a0(&param_4);
    FUN_006ef1f0(param_1,uVar2,uVar1);
    param_4 = param_4 + 0x20;
  }
  FUN_0070c566();
  return;
}

