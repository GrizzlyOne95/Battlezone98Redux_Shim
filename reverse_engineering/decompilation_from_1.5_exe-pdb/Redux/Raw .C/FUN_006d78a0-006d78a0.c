
bool __thiscall FUN_006d78a0(int param_1,int param_2)

{
  char cVar1;
  bool bVar2;
  
  cVar1 = FUN_006ab7d0();
  if ((cVar1 == '\0') && (cVar1 = FUN_006ab7d0(), cVar1 == '\0')) {
    bVar2 = true;
  }
  else {
    cVar1 = operator!=<>(param_1,param_2);
    if (cVar1 == '\0') {
      bVar2 = *(int *)(param_1 + 8) == *(int *)(param_2 + 8);
    }
    else {
      bVar2 = false;
    }
  }
  return bVar2;
}

