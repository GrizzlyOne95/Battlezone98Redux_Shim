
void FUN_006a8980(int param_1,int param_2)

{
  if ((param_1 != 0) && (param_2 != 0)) {
    if ((*(int *)(param_1 + 0x28) != 0) && (*(int *)(*(int *)(param_1 + 0x28) + 0x14) == param_1)) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x28) + 0x14) + 0x28) = 0;
      *(undefined4 *)(*(int *)(param_1 + 0x28) + 0x14) = 0;
    }
    *(int *)(param_1 + 0x28) = param_2;
    *(int *)(param_2 + 0x14) = param_1;
  }
  return;
}

