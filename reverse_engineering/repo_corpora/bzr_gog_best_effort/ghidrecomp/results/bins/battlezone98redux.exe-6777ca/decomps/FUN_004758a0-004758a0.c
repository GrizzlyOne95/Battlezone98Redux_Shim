
void __fastcall FUN_004758a0(int param_1)

{
  float10 fVar1;
  
  if ((*(int *)(param_1 + 0x1c) == 7) || (*(int *)(param_1 + 0x1c) == 0xf)) {
    fVar1 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x7c) = (float)fVar1 + 30.0;
  }
  FUN_00582e50();
  return;
}

