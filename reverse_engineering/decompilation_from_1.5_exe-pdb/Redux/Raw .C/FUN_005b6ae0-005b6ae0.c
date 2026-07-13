
void __fastcall FUN_005b6ae0(int param_1)

{
  char cVar1;
  
  if (*(int *)(param_1 + 0x30) != 0) {
    cVar1 = (**(code **)(**(int **)(param_1 + 0x30) + 0x18))();
    if (cVar1 == '\0') {
      (**(code **)(**(int **)(param_1 + 0x30) + 0x1c))();
    }
    else {
      cVar1 = FUN_005b5100();
      if (cVar1 == '\0') {
        *(undefined4 *)(param_1 + 0x4c) = 1;
      }
      else {
        *(undefined4 *)(param_1 + 0x4c) = 3;
      }
    }
  }
  return;
}

