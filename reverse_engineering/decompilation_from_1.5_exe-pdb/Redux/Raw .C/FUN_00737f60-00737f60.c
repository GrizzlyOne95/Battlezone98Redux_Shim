
void FUN_00737f60(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085a710;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  while( true ) {
    cVar1 = FUN_006cc7a0(&param_2,&param_3);
    if (cVar1 == '\0') break;
    uVar2 = FUN_00422e60();
    uVar3 = FUN_006ef1a0(&param_4);
    FUN_006ef1f0(param_1,uVar3,uVar2);
    FUN_006cc780();
    param_4 = param_4 + 0x20;
  }
  FUN_00738034();
  return;
}

