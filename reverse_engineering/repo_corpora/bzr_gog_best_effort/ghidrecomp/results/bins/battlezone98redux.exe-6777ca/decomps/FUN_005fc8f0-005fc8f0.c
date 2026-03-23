
void __fastcall FUN_005fc8f0(int param_1)

{
  char cVar1;
  
  cVar1 = (**(code **)(**(int **)(param_1 + 0x38) + 0x18))();
  if (cVar1 == '\0') {
    (**(code **)(**(int **)(param_1 + 0x38) + 0x1c))();
  }
  else {
    if (*(int *)(*(int *)(param_1 + 0x34) + 0xac) == 0x11) {
      FUN_004dbc00();
    }
    *(undefined4 *)(param_1 + 0x20) = 3;
  }
  return;
}

