
void __fastcall FUN_004758f0(int param_1)

{
  float10 fVar1;
  
  if (*(char *)(param_1 + 0x50) == '\0') {
    fVar1 = (float10)FUN_004624d0();
    if (10.0 <= (float)fVar1) {
      *(undefined1 *)(param_1 + 0x50) = 1;
      fVar1 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x54) = (float)fVar1 + 10.0;
      goto LAB_00475959;
    }
  }
  (**(code **)(**(int **)(param_1 + 0x34) + 0x60))();
LAB_00475959:
  FUN_00583c80();
  return;
}

