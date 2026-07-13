
void __fastcall FUN_007d8c30(int *param_1)

{
  char cVar1;
  int *piVar2;
  
  if (*param_1 != 0) {
    cVar1 = FUN_007d7500();
    if (cVar1 == '\0') {
      piVar2 = param_1 + 2;
      FUN_007d9580(piVar2);
      FUN_007d95d0(piVar2);
    }
    *param_1 = 0;
  }
  return;
}

