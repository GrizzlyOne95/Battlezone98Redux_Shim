
void __fastcall FUN_005fb9a0(int param_1)

{
  int iVar1;
  float10 fVar2;
  
  fVar2 = (float10)FUN_00822d80();
  if ((float)fVar2 < *(float *)(*(int *)(param_1 + 0x34) + 0xb8)) {
    (**(code **)(**(int **)(param_1 + 0x38) + 0x1c))();
  }
  else {
    *(undefined4 *)(param_1 + 0x10) = 0;
    if (*(int *)(*(int *)(param_1 + 0x34) + 0xac) == 3) {
      FUN_004dbc00();
    }
    *(undefined4 *)(param_1 + 0x20) = 3;
    iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x3c));
    if (iVar1 != 0) {
      FUN_004dbd60(4,iVar1);
    }
  }
  return;
}

