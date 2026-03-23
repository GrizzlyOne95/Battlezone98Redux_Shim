
void FUN_0082c585(int param_1,int param_2,int param_3)

{
  FUN_0082f062(param_1,*(int *)(param_1 + 8) + (param_2 + 1) * -0x10,param_3);
  if (param_3 == -1) {
    if (*(uint *)(*(int *)(param_1 + 0x14) + 8) <= *(uint *)(param_1 + 8)) {
      *(uint *)(*(int *)(param_1 + 0x14) + 8) = *(uint *)(param_1 + 8);
    }
  }
  return;
}

