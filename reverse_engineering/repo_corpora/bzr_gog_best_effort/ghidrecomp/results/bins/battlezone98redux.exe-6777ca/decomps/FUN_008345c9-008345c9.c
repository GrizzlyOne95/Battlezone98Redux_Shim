
undefined4 FUN_008345c9(undefined4 param_1)

{
  int iVar1;
  
  FUN_0082bbb2(param_1,1,5);
  FUN_0082bbb2(param_1,2,6);
  FUN_0082cd45(param_1);
  iVar1 = FUN_0082cb08(param_1,1);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    FUN_0082cdd2(param_1,2);
    FUN_0082cdd2(param_1,0xfffffffd);
    FUN_0082cdd2(param_1,0xfffffffd);
    FUN_0082c585(param_1,2,1);
    iVar1 = FUN_0082d490(param_1,0xffffffff);
    if (iVar1 != 0) break;
    FUN_0082d226(param_1,0xfffffffd);
    iVar1 = FUN_0082cb08(param_1,1);
  }
  return 1;
}

