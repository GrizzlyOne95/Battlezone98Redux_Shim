
void FUN_00694830(int param_1,int *param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  int local_18;
  int local_10;
  int local_8;
  
  *param_2 = 0;
  *param_3 = 1;
  local_8 = 0;
  do {
    if (*(int *)(param_1 + 4) <= local_8) {
      return;
    }
    piVar1 = *(int **)(param_1 + 8 + local_8 * 4);
    for (local_10 = 0; local_10 < *piVar1; local_10 = local_10 + 1) {
      piVar2 = (int *)piVar1[local_10 + 1];
      if (piVar2 != (int *)0x0) {
        if (*piVar2 < 0) {
          local_18 = -*piVar2;
        }
        else {
          local_18 = *piVar2;
        }
        *param_2 = local_18;
        *param_3 = piVar2[1];
        return;
      }
    }
    local_8 = local_8 + 1;
  } while( true );
}

