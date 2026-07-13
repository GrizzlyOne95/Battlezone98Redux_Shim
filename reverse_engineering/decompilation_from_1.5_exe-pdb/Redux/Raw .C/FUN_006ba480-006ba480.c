
int __thiscall FUN_006ba480(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_006ba4c0(param_2,param_1);
  iVar2 = iVar2 + 2;
  cVar1 = FUN_006ba440(param_2);
  if (cVar1 != '\0') {
    iVar2 = iVar2 + 4;
  }
  return iVar2;
}

