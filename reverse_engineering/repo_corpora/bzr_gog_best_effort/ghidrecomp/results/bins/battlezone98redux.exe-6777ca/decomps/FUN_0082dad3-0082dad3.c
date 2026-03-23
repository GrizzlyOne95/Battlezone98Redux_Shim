
int FUN_0082dad3(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_2 + 4);
  if ((piVar1[2] == 6) && (*(char *)(*piVar1 + 6) == '\0')) {
    if (param_2 == *(int *)(param_1 + 0x14)) {
      *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(param_1 + 0x18);
    }
    return (*(int *)(param_2 + 0xc) - *(int *)(*(int *)(*piVar1 + 0x10) + 0xc) >> 2) + -1;
  }
  return -1;
}

