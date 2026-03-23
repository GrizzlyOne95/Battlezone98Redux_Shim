
void __fastcall FUN_00491770(int param_1)

{
  int local_8;
  
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x8054); local_8 = local_8 + 1) {
    FUN_004e3510(*(undefined4 *)(*(int *)(param_1 + 0x8050) + local_8 * 4));
    FUN_0062d200(*(undefined4 *)(*(int *)(param_1 + 0x8050) + local_8 * 4),"fun3d\\ChunkEffect.cpp")
    ;
  }
  operator_delete__(*(void **)(param_1 + 0x8050));
  return;
}

