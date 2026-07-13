
int __thiscall FUN_00430c50(int param_1,undefined4 param_2,char param_3)

{
  char cVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 8) == 0) {
    cVar1 = FUN_00432bb0(param_2,param_1 + 8,0,0);
    if (cVar1 == '\0') {
      iVar2 = 0;
    }
    else if ((param_3 == '\0') || (iVar2 = FUN_0042a7f0(param_1 + 8), -1 < iVar2)) {
      iVar2 = 0;
    }
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

