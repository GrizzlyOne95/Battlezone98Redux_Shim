
void __fastcall FUN_00653ac0(int param_1)

{
  float10 fVar1;
  uint local_18;
  uint auStack_14 [4];
  
  auStack_14[3] = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar1 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x100));
  if (0.0 < (float)fVar1) {
    auStack_14[0] = *(uint *)(param_1 + 0x100);
  }
  local_18 = (uint)(0.0 < (float)fVar1);
  fVar1 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0x104));
  if (0.0 < (float)fVar1) {
    auStack_14[local_18] = *(uint *)(param_1 + 0x104);
    local_18 = local_18 + 1;
  }
  if (local_18 != 0) {
    rand();
  }
  FUN_0083e885();
  return;
}

