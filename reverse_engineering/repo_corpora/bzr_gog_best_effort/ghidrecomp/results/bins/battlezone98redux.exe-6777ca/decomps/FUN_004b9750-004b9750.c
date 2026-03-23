
undefined1 __thiscall FUN_004b9750(int param_1,float param_2)

{
  undefined1 uVar1;
  
  if (param_2 < *(float *)(param_1 + 0x6c)) {
    *(float *)(param_1 + 0x6c) = param_2;
  }
  if ((*(char *)(param_1 + 0x70) != '\0') || (*(float *)(param_1 + 0x6c) + 60.0 < param_2)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

