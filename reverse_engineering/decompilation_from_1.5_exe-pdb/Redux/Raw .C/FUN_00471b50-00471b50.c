
void __fastcall FUN_00471b50(int param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x3c));
  if ((iVar2 != 0) && (cVar1 = FUN_0046ff40(), cVar1 == '\0')) {
    (**(code **)(**(int **)(param_1 + 0x38) + 0x1c))();
    return;
  }
  if (*(int *)(*(int *)(param_1 + 0x34) + 0xac) == 0xb) {
    FUN_004dbc00();
  }
  *(undefined4 *)(param_1 + 0x20) = 3;
  return;
}

