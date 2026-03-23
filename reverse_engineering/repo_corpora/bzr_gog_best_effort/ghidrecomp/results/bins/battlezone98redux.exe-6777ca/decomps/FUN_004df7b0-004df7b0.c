
void FUN_004df7b0(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = FUN_00479f30(param_1);
  if (iVar1 != 0) {
    piVar2 = (int *)FUN_0045bdf0();
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 0x1c))();
    }
  }
  return;
}

