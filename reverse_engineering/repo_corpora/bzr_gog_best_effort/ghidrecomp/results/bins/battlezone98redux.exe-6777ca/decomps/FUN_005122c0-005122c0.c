
void __fastcall FUN_005122c0(int param_1)

{
  char cVar1;
  
  cVar1 = (**(code **)(**(int **)(param_1 + 0x38) + 0x18))();
  if (cVar1 == '\0') {
    (**(code **)(**(int **)(param_1 + 0x38) + 0x1c))();
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = 3;
    if (*(int *)(*(int *)(param_1 + 0x34) + 0xac) == 0x1a) {
      FUN_004dbc00();
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x14,0);
    }
  }
  return;
}

