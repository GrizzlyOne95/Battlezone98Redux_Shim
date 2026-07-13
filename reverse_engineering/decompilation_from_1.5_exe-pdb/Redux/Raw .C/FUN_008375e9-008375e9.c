
int FUN_008375e9(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = FUN_0082ba1c(param_1,2);
  FUN_0082bbb2(param_1,1,6);
  iVar2 = FUN_0082c99e(param_1,1);
  if (iVar2 == 0) {
    if (param_2 == 0) {
      iVar2 = FUN_0082d265(param_1,1,uVar1);
    }
    else {
      iVar2 = FUN_0082c907();
    }
    iVar3 = 0;
    if (iVar2 != 0) {
      FUN_0082cd77(param_1,iVar2);
      FUN_0082c953(param_1,-1 - param_2);
      iVar3 = param_2 + 1;
    }
  }
  else {
    iVar3 = 0;
  }
  return iVar3;
}

