
void __fastcall FUN_00843850(undefined4 *param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  *param_1 = 0;
  piVar2 = (int *)param_1[1];
  param_1[1] = 0;
  if (piVar2 != (int *)0x0) {
    LOCK();
    iVar3 = piVar2[1] + -1;
    piVar2[1] = iVar3;
    UNLOCK();
    if (iVar3 == 0) {
      (**(code **)(*piVar2 + 4))();
      piVar1 = piVar2 + 2;
      LOCK();
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 == 1) {
                    /* WARNING: Could not recover jumptable at 0x0084388b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (**(code **)(*piVar2 + 8))();
        return;
      }
    }
  }
  return;
}

