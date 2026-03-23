
int FUN_00830d4e(int param_1,int param_2,int param_3)

{
  if ((double)CONCAT44(param_3,param_2) == 0.0) {
    return *(int *)(param_1 + 0x10);
  }
  return ((uint)(param_2 + param_3) % ((1 << (*(byte *)(param_1 + 7) & 0x1f)) - 1U | 1)) * 0x20 +
         *(int *)(param_1 + 0x10);
}

