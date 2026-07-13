
undefined4 __thiscall FUN_007d2810(int param_1,float param_2,float param_3)

{
  undefined4 uVar1;
  
  if ((((param_2 < *(float *)(param_1 + 4)) ||
       (*(float *)(param_1 + 4) + *(float *)(param_1 + 0xc) < param_2)) ||
      (param_3 < *(float *)(param_1 + 8))) ||
     (*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10) < param_3)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

