
undefined4 FUN_00833783(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0082d490(param_1,2);
  FUN_0082bbb2(param_1,1,5);
  if ((iVar1 != 0) && (iVar1 != 5)) {
    FUN_0082b8e4(param_1,2,"nil or table expected");
  }
  iVar1 = FUN_0082bd41(param_1,1,"__metatable");
  if (iVar1 != 0) {
    FUN_0082bc39(param_1,"cannot change a protected metatable");
  }
  FUN_0082d226(param_1,2);
  FUN_0082d16f(param_1,1);
  return 1;
}

