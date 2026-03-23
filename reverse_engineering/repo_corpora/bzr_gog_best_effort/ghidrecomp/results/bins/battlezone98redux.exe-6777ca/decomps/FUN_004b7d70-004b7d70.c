
void __fastcall FUN_004b7d70(int param_1)

{
  float10 fVar1;
  int local_18;
  
  DAT_009175c0 = 0x4f50;
  fVar1 = (float10)FUN_00822d80();
  DAT_009175c2 = (float)fVar1;
  DAT_009175c6 = 6;
  local_18 = FUN_00417c70();
  if (local_18 == 0) {
    local_18 = 0;
  }
  else {
    local_18 = local_18 + 0x18;
  }
  DAT_009175c7 = (param_1 == local_18) << 7 | 2;
  DAT_009175c8 = *(undefined4 *)(param_1 + 100);
  FUN_00575890(&DAT_009175c0,0xc,1,0);
  return;
}

