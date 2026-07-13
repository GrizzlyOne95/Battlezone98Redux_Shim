
int __fastcall FUN_0069d8a0(int param_1)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = FUN_00698c10();
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x80) = 0xbf800000;
    iVar1 = 0;
  }
  else if (*(int *)(param_1 + 4) == 3) {
    if (*(float *)(param_1 + 0x80) == -1.0) {
      fVar2 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x80) = (float)fVar2;
    }
    fVar2 = (float10)FUN_00822d80();
    if ((float)fVar2 - *(float *)(param_1 + 0x80) < 180.0) {
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
    }
  }
  return iVar1;
}

