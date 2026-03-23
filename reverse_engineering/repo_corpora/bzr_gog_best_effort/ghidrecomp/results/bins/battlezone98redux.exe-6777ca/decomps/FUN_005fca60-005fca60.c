
void __fastcall FUN_005fca60(int param_1)

{
  char cVar1;
  int iVar2;
  
  if (((*(int *)(param_1 + 0x38) != 0) &&
      (cVar1 = (**(code **)(**(int **)(param_1 + 0x38) + 0x18))(), cVar1 != '\0')) &&
     (iVar2 = FUN_00473940(), iVar2 != 0)) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0x24))();
  }
  if ((*(int *)(param_1 + 0x38) != 0) &&
     (cVar1 = (**(code **)(**(int **)(param_1 + 0x38) + 0x18))(), cVar1 == '\0')) {
    (**(code **)(**(int **)(param_1 + 0x38) + 0x1c))();
    return;
  }
  if (*(int *)(*(int *)(param_1 + 0x34) + 0xac) == 0x12) {
    FUN_004dbc00();
  }
  *(undefined4 *)(param_1 + 0x20) = 3;
  return;
}

