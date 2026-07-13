
undefined4 FUN_00833e63(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0082d447(param_1,1);
  if (iVar1 == 0) {
    FUN_0082b8e4(param_1,1,"coroutine expected");
  }
  iVar1 = FUN_00834188(param_1,iVar1);
  FUN_0082cd77(param_1,(&PTR_s_running_0086f230)[iVar1]);
  return 1;
}

