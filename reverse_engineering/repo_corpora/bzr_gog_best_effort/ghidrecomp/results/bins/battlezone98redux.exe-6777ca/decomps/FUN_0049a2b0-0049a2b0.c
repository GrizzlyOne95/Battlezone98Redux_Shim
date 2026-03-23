
void __fastcall FUN_0049a2b0(int param_1)

{
  int iVar1;
  float10 fVar2;
  float local_10;
  
  if (*(char *)(param_1 + 0x29) != '\0') {
    iVar1 = FUN_00572a70();
    if (((iVar1 == 0) || (DAT_00917f48 == 0)) || (*(char *)(DAT_00917f48 + 0x864) == '\0')) {
      if (iVar1 == 0) {
        fVar2 = (float10)FUN_00822d60();
      }
      else {
        fVar2 = (float10)FUN_00822d70();
      }
      local_10 = (float)fVar2;
      *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x18) - local_10;
      while (*(float *)(param_1 + 0x18) <= 0.0 && *(float *)(param_1 + 0x18) != 0.0) {
        *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x18) + 1.0;
        if (*(char *)(param_1 + 0x28) == '\0') {
          *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
        }
        else {
          *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + -1;
          if (*(int *)(param_1 + 0x1c) == 0) {
            *(undefined1 *)(param_1 + 0x29) = 0;
          }
        }
      }
    }
  }
  return;
}

