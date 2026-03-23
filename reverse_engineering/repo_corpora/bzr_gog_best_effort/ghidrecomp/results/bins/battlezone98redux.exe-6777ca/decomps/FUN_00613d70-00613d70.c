
void __fastcall FUN_00613d70(int param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = (**(code **)(**(int **)(param_1 + 0x38) + 0x18))();
  if (((cVar1 != '\0') && (*(int *)(param_1 + 0x38) != 0)) && (iVar2 = FUN_004f1fd0(), iVar2 == 0))
  {
    *(undefined4 *)(param_1 + 0x10) = 0;
    if (*(int *)(*(int *)(param_1 + 0x34) + 0xac) == 3) {
      FUN_004dbc00();
    }
    *(undefined4 *)(param_1 + 0x20) = 3;
    return;
  }
  (**(code **)(**(int **)(param_1 + 0x38) + 0x1c))();
  return;
}

