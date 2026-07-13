
void __fastcall FUN_005b4740(int param_1)

{
  undefined4 uVar1;
  
  switch(*(undefined4 *)(param_1 + 0x1c)) {
  case 1:
    if (*(int *)(param_1 + 0x18) == 2) {
      (**(code **)(**(int **)(param_1 + 0x20) + 100))();
    }
    break;
  case 4:
    if (*(int *)(*(int *)(param_1 + 0x20) + 0xac) == 3) {
      *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(*(int *)(param_1 + 0x20) + 0xb4);
      *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(*(int *)(param_1 + 0x20) + 0xb0);
    }
    if (*(int *)(param_1 + 0x18) == 2) {
      (**(code **)(**(int **)(param_1 + 0x20) + 100))();
    }
    break;
  case 5:
    if (*(int *)(param_1 + 0x18) == 2) {
      (**(code **)(**(int **)(param_1 + 0x20) + 100))();
    }
    uVar1 = FUN_004dc010();
    uVar1 = FUN_00477590(uVar1);
    *(undefined4 *)(param_1 + 0x24) = uVar1;
    break;
  case 8:
    if (*(int *)(param_1 + 0x18) == 2) {
      (**(code **)(**(int **)(param_1 + 0x20) + 100))();
    }
  }
  return;
}

