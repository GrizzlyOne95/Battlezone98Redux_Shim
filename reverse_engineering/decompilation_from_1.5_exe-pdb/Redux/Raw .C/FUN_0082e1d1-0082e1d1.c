
undefined4 FUN_0082e1d1(int param_1,int param_2,int param_3,undefined4 param_4)

{
  if ((param_2 == 0) || (param_3 == 0)) {
    param_2 = 0;
    param_3 = 0;
  }
  *(int *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x3c) = param_4;
  *(undefined4 *)(param_1 + 0x40) = param_4;
  *(char *)(param_1 + 0x38) = (char)param_3;
  return 1;
}

