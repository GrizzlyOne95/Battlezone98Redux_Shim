
undefined4 FUN_00690f50(undefined2 param_1,undefined2 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  cVar1 = FUN_006a05c0(param_1);
  if ((cVar1 != '\0') && (cVar1 = FUN_006a05c0(param_2), cVar1 != '\0')) {
    iVar2 = FUN_006a0670(param_1);
    iVar3 = FUN_006a0670(param_2);
    if (iVar2 == *(int *)(iVar3 + 4)) {
      return 1;
    }
  }
  return 0;
}

