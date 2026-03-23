
void __fastcall FUN_006572b0(int param_1)

{
  float10 fVar1;
  uint local_20;
  undefined4 auStack_1c [5];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar1 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x90));
  if (0.0 < (float)fVar1) {
    auStack_1c[0] = *(undefined4 *)(param_1 + 0x90);
  }
  local_20 = (uint)(0.0 < (float)fVar1);
  fVar1 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x94));
  if (0.0 < (float)fVar1) {
    auStack_1c[local_20] = *(undefined4 *)(param_1 + 0x94);
    local_20 = local_20 + 1;
  }
  fVar1 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x98));
  if (0.0 < (float)fVar1) {
    auStack_1c[local_20] = *(undefined4 *)(param_1 + 0x98);
    local_20 = local_20 + 1;
  }
  fVar1 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x9c));
  if (0.0 < (float)fVar1) {
    auStack_1c[local_20] = *(undefined4 *)(param_1 + 0x9c);
    local_20 = local_20 + 1;
  }
  fVar1 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xa0));
  if (0.0 < (float)fVar1) {
    auStack_1c[local_20] = *(undefined4 *)(param_1 + 0xa0);
    local_20 = local_20 + 1;
  }
  if (local_20 != 0) {
    rand();
  }
  FUN_0083e885();
  return;
}

