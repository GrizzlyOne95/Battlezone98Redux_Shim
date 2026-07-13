
void __fastcall FUN_0078c7f0(undefined4 param_1)

{
  char cVar1;
  int *piVar2;
  
  piVar2 = (int *)FUN_007647b0(param_1);
  if (piVar2 != (int *)0x0) {
    cVar1 = (**(code **)(*piVar2 + 8))();
    if (cVar1 != '\0') {
      FUN_0078df10();
    }
  }
  return;
}

