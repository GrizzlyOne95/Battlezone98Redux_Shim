
void FUN_0046ee10(int param_1,int *param_2,undefined4 param_3)

{
  int local_c;
  int local_8;
  
  for (local_8 = param_2[1]; local_8 < param_2[3]; local_8 = local_8 + 1) {
    for (local_c = *param_2; local_c < param_2[2]; local_c = local_c + 1) {
      *(undefined4 *)(param_1 + (local_8 * DAT_0260d638 + local_c) * 4) = param_3;
    }
  }
  return;
}

