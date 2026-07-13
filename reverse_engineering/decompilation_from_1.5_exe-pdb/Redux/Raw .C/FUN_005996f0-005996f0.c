
undefined4 FUN_005996f0(int *param_1)

{
  undefined4 uVar1;
  
  if ((*param_1 < DAT_02a13ccc) || (DAT_02a13cd4 < *param_1)) {
    uVar1 = 0;
  }
  else if ((param_1[1] < DAT_02a13cd0) || (DAT_02a13cc8 < param_1[1])) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

