
float10 FUN_0058d510(int param_1)

{
  float10 fVar1;
  undefined4 local_8;
  
  if (*(char *)(param_1 + 0x1f) == '\0') {
    local_8 = DAT_02a13c94;
  }
  else {
    local_8 = DAT_02a13ca0;
  }
  fVar1 = (float10)FUN_0058d4c0(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x28),
                                *(undefined4 *)(local_8 + 0x24),*(undefined4 *)(local_8 + 0x28));
  return (float10)((float)fVar1 + 0.0001);
}

