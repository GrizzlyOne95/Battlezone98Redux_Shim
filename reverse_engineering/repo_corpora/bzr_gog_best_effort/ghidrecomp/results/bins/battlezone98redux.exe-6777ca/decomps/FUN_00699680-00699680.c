
void FUN_00699680(int param_1,int param_2)

{
  *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(param_1 + 0xc);
  *(int *)(param_1 + 0xc) = param_2;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
  return;
}

