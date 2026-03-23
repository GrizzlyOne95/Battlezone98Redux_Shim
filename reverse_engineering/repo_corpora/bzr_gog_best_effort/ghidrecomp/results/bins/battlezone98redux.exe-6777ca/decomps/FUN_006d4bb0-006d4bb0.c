
int __fastcall FUN_006d4bb0(int *param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_006d67d0();
  if (cVar1 == '\0') {
    iVar2 = *param_1;
  }
  else {
    iVar2 = -(*param_1 + 1);
  }
  return iVar2;
}

