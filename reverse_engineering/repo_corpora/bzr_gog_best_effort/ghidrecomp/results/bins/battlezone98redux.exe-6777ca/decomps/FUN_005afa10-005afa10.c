
float10 __fastcall FUN_005afa10(int param_1)

{
  undefined4 local_c;
  
  if (*(int *)(param_1 + 0x300) == 0) {
    local_c = 0.0;
  }
  else {
    local_c = 1.0 - *(float *)(param_1 + 0x304) / *(float *)(*(int *)(param_1 + 0x300) + 0x54);
  }
  return (float10)local_c;
}

