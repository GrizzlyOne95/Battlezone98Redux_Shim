
void __fastcall FUN_00608aa0(int param_1)

{
  if ((-1 < *(int *)(param_1 + 0x38)) &&
     ((1 << ((byte)*(undefined4 *)(param_1 + 0x38) & 0x1f) & *(uint *)(param_1 + 0x34)) != 0)) {
    (**(code **)(**(int **)(param_1 + 0x18 + *(int *)(param_1 + 0x38) * 4) + 8))();
  }
  return;
}

