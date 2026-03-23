
void __fastcall FUN_004391d0(undefined4 *param_1)

{
  uint local_c;
  
  *param_1 = CSound::vftable;
  for (local_c = 0; local_c < (uint)param_1[4]; local_c = local_c + 1) {
    if (*(int *)(param_1[1] + local_c * 4) != 0) {
      (**(code **)(**(int **)(param_1[1] + local_c * 4) + 8))
                (*(undefined4 *)(param_1[1] + local_c * 4));
      *(undefined4 *)(param_1[1] + local_c * 4) = 0;
    }
  }
  if (param_1[1] != 0) {
    operator_delete__((void *)param_1[1]);
    param_1[1] = 0;
  }
  if (param_1[3] != 0) {
    if (param_1[3] != 0) {
      FUN_00439080(1);
    }
    param_1[3] = 0;
  }
  return;
}

