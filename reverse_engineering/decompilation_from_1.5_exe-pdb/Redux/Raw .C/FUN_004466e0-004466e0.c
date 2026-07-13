
void __fastcall FUN_004466e0(undefined4 *param_1)

{
  uint local_c;
  
  *param_1 = BoltRender::vftable;
  if (param_1[0x1c] != 0) {
    for (local_c = 0; local_c < (uint)param_1[0x1d]; local_c = local_c + 1) {
      operator_delete(*(void **)(param_1[0x1c] + local_c * 4));
    }
    param_1[0x1d] = 0;
    operator_delete__((void *)param_1[0x1c]);
    param_1[0x1c] = 0;
  }
  FUN_00448f70();
  return;
}

