
void __thiscall FUN_006b1570(int param_1,int param_2)

{
  FUN_006b1f00(param_2);
  FUN_006c8ce0(param_1 + 0x10);
  if (*(int *)(param_1 + 0x28) == param_2) {
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_2 + 0x14);
  }
  if (*(int *)(param_2 + 0x18) != 0) {
    *(undefined4 *)(*(int *)(param_2 + 0x18) + 0x14) = *(undefined4 *)(param_2 + 0x14);
  }
  if (*(int *)(param_2 + 0x14) != 0) {
    *(undefined4 *)(*(int *)(param_2 + 0x14) + 0x18) = *(undefined4 *)(param_2 + 0x18);
  }
  *(undefined4 *)(param_2 + 0x14) = 0;
  *(undefined4 *)(param_2 + 0x18) = 0;
  FUN_006c8d50();
  return;
}

