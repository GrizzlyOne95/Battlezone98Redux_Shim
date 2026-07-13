
void FUN_00695560(int param_1,undefined4 param_2)

{
  if (*(int *)(param_1 + 0x60) != 0) {
    FUN_00693140(param_1);
  }
  *(undefined4 *)(param_1 + 0x60) = param_2;
  if (*(int *)(param_1 + 0x60) != 0) {
    FUN_00692d70(param_1,*(undefined4 *)(*(int *)(param_1 + 0x60) + 0x90),
                 *(undefined4 *)(*(int *)(param_1 + 0x60) + 0x94));
    FUN_00693120(param_1,*(undefined4 *)(*(int *)(param_1 + 0x60) + 0x8c));
    FUN_00694950(param_1);
  }
  return;
}

