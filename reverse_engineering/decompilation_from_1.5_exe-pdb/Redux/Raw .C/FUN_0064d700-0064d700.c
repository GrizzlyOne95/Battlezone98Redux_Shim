
void __fastcall FUN_0064d700(int param_1)

{
  float10 fVar1;
  int local_1c;
  int local_18;
  uint auStack_14 [4];
  
  auStack_14[3] = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = 0;
  for (local_1c = 0; local_1c < 3; local_1c = local_1c + 1) {
    fVar1 = (float10)FUN_005cced0(*(undefined4 *)(param_1 + 0xdc + local_1c * 4));
    if (0.0 < (double)fVar1) {
      auStack_14[local_18] = *(uint *)(param_1 + 0xdc + local_1c * 4);
      local_18 = local_18 + 1;
    }
  }
  if (local_18 != 0) {
    rand();
  }
  FUN_0083e885();
  return;
}

