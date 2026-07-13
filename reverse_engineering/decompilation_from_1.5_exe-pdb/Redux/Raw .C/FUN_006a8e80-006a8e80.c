
void FUN_006a8e80(void *param_1)

{
  undefined4 uVar1;
  int local_8;
  
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    if (*(int *)((int)param_1 + local_8 * 4 + 0x40) == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = FUN_006a8f10(1);
    }
    if (*(int *)((int)param_1 + local_8 * 4) != 0) {
      FUN_00695340(*(undefined4 *)((int)param_1 + local_8 * 4),uVar1);
      *(undefined4 *)((int)param_1 + local_8 * 4) = 0;
    }
  }
  free(param_1);
  return;
}

