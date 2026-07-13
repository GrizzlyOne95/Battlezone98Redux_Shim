
void __fastcall FUN_0064d7b0(int param_1)

{
  float10 fVar1;
  uint local_1c;
  undefined4 auStack_18 [4];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar1 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xa4));
  if (0.0 < (double)fVar1) {
    auStack_18[0] = *(undefined4 *)(param_1 + 0xa4);
  }
  local_1c = (uint)(0.0 < (double)fVar1);
  fVar1 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xa0));
  if (0.0 < (double)fVar1) {
    auStack_18[local_1c] = *(undefined4 *)(param_1 + 0xa0);
    local_1c = local_1c + 1;
  }
  fVar1 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xac));
  if (0.0 < (double)fVar1) {
    auStack_18[local_1c] = *(undefined4 *)(param_1 + 0xac);
    local_1c = local_1c + 1;
  }
  fVar1 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xb0));
  if (0.0 < (double)fVar1) {
    auStack_18[local_1c] = *(undefined4 *)(param_1 + 0xb0);
    local_1c = local_1c + 1;
  }
  if (local_1c != 0) {
    rand();
  }
  FUN_0083e885();
  return;
}

