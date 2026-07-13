
int FUN_00834ff8(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint local_8;
  
  iVar1 = FUN_0082ba59(param_1,1,&local_8);
  uVar2 = FUN_0082c1fd(param_1,2,1,local_8);
  iVar3 = FUN_00835ff6(uVar2);
  uVar2 = FUN_0082c1fd(param_1,3,iVar3,local_8);
  uVar4 = FUN_00835ff6(uVar2);
  if (iVar3 < 1) {
    iVar3 = 1;
  }
  if (local_8 < uVar4) {
    uVar4 = local_8;
  }
  if ((int)uVar4 < iVar3) {
    iVar5 = 0;
  }
  else {
    iVar5 = (uVar4 - iVar3) + 1;
    if (iVar5 + iVar3 <= (int)uVar4) {
      FUN_0082bc39(param_1,"string slice too long");
    }
    FUN_0082bb89(param_1,iVar5,"string slice too long");
    iVar6 = 0;
    if (0 < iVar5) {
      do {
        FUN_0082ccca(param_1,*(undefined1 *)(iVar3 + iVar1 + -1 + iVar6));
        iVar6 = iVar6 + 1;
      } while (iVar6 < iVar5);
    }
  }
  return iVar5;
}

