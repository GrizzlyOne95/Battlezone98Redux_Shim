
void __fastcall FUN_005d78f0(int param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_00822d80();
  if ((float)fVar1 < *(float *)(param_1 + 0x58) || (float)fVar1 == *(float *)(param_1 + 0x58)) {
    FUN_005fb450();
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = 0x10;
  }
  return;
}

