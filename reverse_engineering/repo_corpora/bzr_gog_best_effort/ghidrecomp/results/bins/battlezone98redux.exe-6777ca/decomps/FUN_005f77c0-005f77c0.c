
void __fastcall FUN_005f77c0(int param_1)

{
  char cVar1;
  
  cVar1 = (**(code **)(**(int **)(param_1 + 0x38) + 0x18))();
  if (cVar1 == '\0') {
    (**(code **)(**(int **)(param_1 + 0x38) + 0x1c))();
  }
  else {
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x18,*(undefined4 *)(param_1 + 0x3c));
    if (*(int *)(*(int *)(param_1 + 0x34) + 0xac) == 4) {
      FUN_004dbc00();
    }
    *(undefined4 *)(param_1 + 0x20) = 3;
  }
  return;
}

