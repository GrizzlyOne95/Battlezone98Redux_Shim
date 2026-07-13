
float10 __fastcall FUN_006976a0(int param_1)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = FUN_00417f90();
  if (iVar1 == 0) {
    if (*(int *)(*(int *)(param_1 + 0x3c) + 0x60) == 0) {
      *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x50);
    }
    else {
      *(float *)(param_1 + 0x20) = (float)*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x30)
      ;
    }
    fVar2 = (float10)*(float *)(param_1 + 0x20);
  }
  else {
    fVar2 = (float10)0;
  }
  return fVar2;
}

