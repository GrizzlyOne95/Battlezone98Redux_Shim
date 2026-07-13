
void __fastcall FUN_004c83e0(int param_1)

{
  float fVar1;
  int iVar2;
  char local_108 [256];
  uint local_8;
  
  fVar1 = DAT_00920ef4;
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar2 = (*(int *)(DAT_00917580 + 0x14) - *(int *)(param_1 + 0xd8)) + -4;
  sprintf(local_108,"[Y=%.1fm] [Width=%dm] [Depth=%dm] [Height=%.1fm] [Incr=%.1fm] (%d,%d)",
          (double)*(float *)(param_1 + 0xe8),(int)((float)*(int *)(param_1 + 0xec) * 5.0),
          (int)((float)*(int *)(param_1 + 0xf0) * 5.0),(double)*(float *)(param_1 + 0xf4),
          (double)*(float *)(param_1 + 0xf8),*(undefined4 *)(param_1 + 0x38),
          *(undefined4 *)(param_1 + 0x3c),iVar2);
  DAT_00920ef4 = fVar1 + 0.02;
  FUN_0068af70(DAT_00917580,*(undefined4 *)(DAT_00917580 + 8),iVar2,
               *(undefined4 *)(DAT_00917580 + 0x10),*(undefined4 *)(DAT_00917580 + 0x14),
               *(undefined4 *)(param_1 + 0xe4),0);
  std::_Init_atomic_counter(DAT_0091552c,*(ulong *)(param_1 + 0xe0));
  DAT_00920ef4 = fVar1 + 0.01;
  FUN_00689d10();
  DAT_00920ef4 = fVar1;
  FUN_0083e885();
  return;
}

