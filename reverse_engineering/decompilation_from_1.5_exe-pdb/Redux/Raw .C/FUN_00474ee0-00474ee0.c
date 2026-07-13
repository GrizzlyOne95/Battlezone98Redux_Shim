
void __fastcall FUN_00474ee0(int param_1)

{
  switch(*(undefined4 *)(param_1 + 0x1c)) {
  case 1:
    if (*(int *)(param_1 + 0x18) == 2) {
      (**(code **)(**(int **)(param_1 + 0x20) + 100))();
    }
    break;
  case 4:
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(*(int *)(param_1 + 0x20) + 0xb4);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(*(int *)(param_1 + 0x20) + 0xb0);
    if (*(int *)(param_1 + 0x18) == 2) {
      (**(code **)(**(int **)(param_1 + 0x20) + 100))();
    }
    break;
  case 5:
    if (*(int *)(param_1 + 0x18) == 2) {
      (**(code **)(**(int **)(param_1 + 0x20) + 100))();
    }
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(*(int *)(param_1 + 0x20) + 0xb0);
    break;
  case 6:
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(*(int *)(param_1 + 0x20) + 0xb4);
    break;
  case 8:
    if (*(int *)(param_1 + 0x18) == 2) {
      (**(code **)(**(int **)(param_1 + 0x20) + 100))();
    }
  }
  return;
}

