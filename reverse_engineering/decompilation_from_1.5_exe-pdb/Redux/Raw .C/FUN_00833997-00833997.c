
undefined4 FUN_00833997(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  double dVar4;
  
  iVar1 = FUN_0082bae0(param_1,1,"collect",&PTR_DAT_0086f128);
  uVar2 = FUN_0082c1fd(param_1,2,0);
  iVar3 = FUN_0082c70b(param_1,*(undefined4 *)(&DAT_0086f148 + iVar1 * 4),uVar2);
  if (*(int *)(&DAT_0086f148 + iVar1 * 4) == 3) {
    iVar1 = FUN_0082c70b(param_1,4,0);
    dVar4 = (double)iVar1 * 0.0009765625 + (double)iVar3;
  }
  else {
    if (*(int *)(&DAT_0086f148 + iVar1 * 4) == 5) {
      FUN_0082cbf5(param_1,iVar3);
      return 1;
    }
    dVar4 = (double)iVar3;
  }
  FUN_0082cd58(param_1,dVar4);
  return 1;
}

