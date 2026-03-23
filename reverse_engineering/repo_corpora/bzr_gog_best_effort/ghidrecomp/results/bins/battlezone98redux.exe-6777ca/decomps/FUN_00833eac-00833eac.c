
int FUN_00833eac(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0082d447(param_1,1);
  if (iVar1 == 0) {
    FUN_0082b8e4(param_1,1,"coroutine expected");
  }
  iVar2 = FUN_0082c8f6(param_1);
  iVar1 = FUN_00834002(param_1,iVar1,iVar2 + -1);
  if (iVar1 < 0) {
    FUN_0082cbf5(param_1,0);
    FUN_0082c953(param_1,0xfffffffe);
    iVar1 = 2;
  }
  else {
    FUN_0082cbf5(param_1,1);
    FUN_0082c953(param_1,-1 - iVar1);
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

