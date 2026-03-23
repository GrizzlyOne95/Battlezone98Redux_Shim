
void __thiscall FUN_005889d0(int param_1,undefined4 param_2,undefined4 param_3)

{
  float10 fVar1;
  
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x4c) = param_3;
  fVar1 = (float10)FUN_007855e0((double)*(float *)(param_1 + 0x44),
                                (double)*(float *)(param_1 + 0x4c));
  *(float *)(param_1 + 0x48) = (float)fVar1;
  return;
}

