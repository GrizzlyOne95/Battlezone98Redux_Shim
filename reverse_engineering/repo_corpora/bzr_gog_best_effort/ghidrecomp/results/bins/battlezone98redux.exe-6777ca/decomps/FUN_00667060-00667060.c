
void __fastcall FUN_00667060(int *param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = param_1 + 1;
  LOCK();
  iVar1 = *piVar2;
  *piVar2 = *piVar2 + -1;
  UNLOCK();
  if (iVar1 == 1) {
    (**(code **)(*param_1 + 4))();
    Decwref();
  }
  return;
}

