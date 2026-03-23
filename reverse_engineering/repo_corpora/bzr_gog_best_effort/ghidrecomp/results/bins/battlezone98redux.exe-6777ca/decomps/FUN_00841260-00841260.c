
int * __fastcall FUN_00841260(int *param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00840e80();
  if ((uint)param_1[4] < uVar1) {
                    /* WARNING: Subroutine does not return */
    std::_Xout_of_range("invalid string position");
  }
  param_1[4] = uVar1;
  if (7 < (uint)param_1[5]) {
    *(undefined2 *)(*param_1 + uVar1 * 2) = 0;
    return param_1;
  }
  *(undefined2 *)((int)param_1 + uVar1 * 2) = 0;
  return param_1;
}

