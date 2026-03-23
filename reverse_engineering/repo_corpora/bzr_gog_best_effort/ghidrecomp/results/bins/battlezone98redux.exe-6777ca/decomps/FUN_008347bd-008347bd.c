
undefined4 FUN_008347bd(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  FUN_0082bbb2(param_1,1,5);
  iVar1 = FUN_0082cb3b(param_1,1);
  iVar2 = FUN_0082c1fd(param_1,2,iVar1);
  if ((iVar2 < 1) || (iVar1 < iVar2)) {
    uVar3 = 0;
  }
  else {
    FUN_0082ce9d(param_1,1,iVar2);
    while (iVar2 < iVar1) {
      FUN_0082ce9d(param_1,1,iVar2 + 1);
      FUN_0082cf37(param_1,1,iVar2);
      iVar2 = iVar2 + 1;
    }
    FUN_0082cd45(param_1);
    FUN_0082cf37(param_1,1,iVar1);
    uVar3 = 1;
  }
  return uVar3;
}

