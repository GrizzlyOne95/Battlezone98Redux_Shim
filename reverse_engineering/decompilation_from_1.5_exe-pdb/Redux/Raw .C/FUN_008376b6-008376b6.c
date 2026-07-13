
undefined4 FUN_008376b6(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = FUN_0082d490(param_1,1);
  if (iVar1 == 8) {
    *param_2 = 1;
    param_1 = FUN_0082d447(param_1,1);
  }
  else {
    *param_2 = 0;
  }
  return param_1;
}

