
void FUN_00693230(void *param_1)

{
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 0x20; local_8 = local_8 + 1) {
    if (*(int *)((int)param_1 + local_8 * 4) != 0) {
      FUN_006931b0(*(undefined4 *)((int)param_1 + local_8 * 4));
      *(undefined4 *)((int)param_1 + local_8 * 4) = 0;
    }
  }
  free(param_1);
  return;
}

