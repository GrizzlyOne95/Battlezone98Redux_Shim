
int FUN_00833c96(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = FUN_0082c8f6(param_1);
  iVar2 = FUN_0082d490(param_1,1);
  if ((iVar2 == 4) && (pcVar3 = (char *)FUN_0082d377(param_1,1,0), *pcVar3 == '#')) {
    FUN_0082ccca(param_1,iVar1 + -1);
    return 1;
  }
  iVar2 = FUN_0082ba1c(param_1,1);
  if (iVar2 < 0) {
    iVar2 = iVar2 + iVar1;
  }
  else if (iVar1 < iVar2) {
    iVar2 = iVar1;
  }
  if (iVar2 < 1) {
    FUN_0082b8e4(param_1,1,"index out of range");
  }
  return iVar1 - iVar2;
}

