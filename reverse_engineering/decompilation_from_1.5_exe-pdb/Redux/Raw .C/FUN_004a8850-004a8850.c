
bool FUN_004a8850(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  iVar2 = FUN_0062e050(param_1);
  iVar3 = FUN_00417e20(iVar2);
  if (iVar3 == 0) {
    bVar4 = false;
  }
  else {
    cVar1 = (**(code **)(**(int **)(iVar2 + 0x8c) + 0x6c))();
    bVar4 = cVar1 == '\0';
  }
  return bVar4;
}

