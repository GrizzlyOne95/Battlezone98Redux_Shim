
float10 __fastcall FUN_0049ccf0(int param_1)

{
  float10 fVar1;
  undefined4 local_c;
  
  if (*(int *)(param_1 + 0x3bc) == 0) {
    fVar1 = (float10)FUN_005afa10();
    local_c = (float)fVar1;
  }
  else {
    local_c = 1.0 - *(float *)(param_1 + 0x304) / *(float *)(*(int *)(param_1 + 0x370) + 0x54);
  }
  return (float10)local_c;
}

