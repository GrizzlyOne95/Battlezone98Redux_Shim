
void FUN_00695a70(int param_1,int param_2,int param_3,int param_4,float param_5)

{
  if ((((-1 < param_3) && (-1 < param_4)) && (param_3 < *(int *)(param_1 + 0x78))) &&
     ((param_4 < *(int *)(param_1 + 0x7c) &&
      (*(int *)(param_2 + 0x4c) =
            (int)(((float)*(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x80) + param_3 * 4) +
                                           param_4 * 4) + 0x48) *
                  *(float *)(*(int *)(param_1 + 0x60) + 0x7c)) / param_5) + *(int *)(param_2 + 0x4c)
      , *(int *)(param_1 + 100) < *(int *)(param_2 + 0x4c))))) {
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_2 + 0x4c);
  }
  return;
}

