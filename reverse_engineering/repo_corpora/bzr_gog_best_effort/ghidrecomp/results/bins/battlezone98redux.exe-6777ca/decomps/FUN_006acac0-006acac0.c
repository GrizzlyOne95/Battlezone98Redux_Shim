
void __thiscall FUN_006acac0(int *param_1,int param_2)

{
  int local_8;
  
  if (*param_1 != 0) {
    if (param_2 == *param_1) {
      *param_1 = *(int *)(param_2 + 4);
      *(undefined4 *)(param_2 + 4) = 0;
    }
    else {
      for (local_8 = *param_1; *(int *)(local_8 + 4) != 0; local_8 = *(int *)(local_8 + 4)) {
        if (*(int *)(local_8 + 4) == param_2) {
          *(undefined4 *)(local_8 + 4) = *(undefined4 *)(param_2 + 4);
          *(undefined4 *)(param_2 + 4) = 0;
          return;
        }
      }
    }
  }
  return;
}

