
bool FUN_005cda90(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  int iVar2;
  float10 extraout_ST0;
  
  iVar2 = FUN_00462630(param_1);
  if (iVar2 == 0) {
    bVar1 = false;
  }
  else {
    iVar2 = FUN_00460fc0(param_2);
    if (iVar2 == 0) {
      FUN_007d6a70("Path not found %s",param_2);
      bVar1 = false;
    }
    else {
      FUN_005c9800(param_1,param_2,*(int *)(iVar2 + 4) + -1);
      bVar1 = (float)extraout_ST0 < 12.0;
    }
  }
  return bVar1;
}

