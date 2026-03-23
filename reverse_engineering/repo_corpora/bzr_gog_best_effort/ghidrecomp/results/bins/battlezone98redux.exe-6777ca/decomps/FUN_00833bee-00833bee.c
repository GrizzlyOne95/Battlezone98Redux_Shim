
int FUN_00833bee(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  FUN_0082bbb2(param_1,1,5);
  iVar1 = FUN_0082c1fd(param_1,2,1);
  iVar2 = FUN_0082d490(param_1,3);
  if (iVar2 < 1) {
    iVar2 = FUN_0082cb3b(param_1,1);
  }
  else {
    iVar2 = FUN_0082ba1c(param_1,3);
  }
  if (iVar2 < iVar1) {
    iVar3 = 0;
  }
  else {
    iVar3 = (iVar2 - iVar1) + 1;
    if ((iVar3 < 1) || (iVar4 = FUN_0082c5be(param_1,iVar3), iVar4 == 0)) {
      iVar3 = FUN_0082bc39(param_1,"too many results to unpack");
    }
    else {
      FUN_0082ce9d(param_1,1,iVar1);
      while (iVar1 < iVar2) {
        iVar1 = iVar1 + 1;
        FUN_0082ce9d(param_1,1,iVar1);
      }
    }
  }
  return iVar3;
}

