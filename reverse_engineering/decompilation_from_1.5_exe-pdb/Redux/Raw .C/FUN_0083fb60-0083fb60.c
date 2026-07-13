
int * __thiscall FUN_0083fb60(int *param_1,undefined4 *param_2,uint param_3,uint param_4)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  int *piVar4;
  
  if ((uint)param_2[4] < param_3) {
                    /* WARNING: Subroutine does not return */
    std::_Xout_of_range("invalid string position");
  }
  uVar3 = param_2[4] - param_3;
  if (uVar3 < param_4) {
    param_4 = uVar3;
  }
  if (param_4 < -param_1[4] - 1U) {
    if (param_4 != 0) {
      iVar1 = param_1[4] + param_4;
      cVar2 = FID_conflict__Grow(iVar1,0);
      if (cVar2 != '\0') {
        if (7 < (uint)param_2[5]) {
          param_2 = (undefined4 *)*param_2;
        }
        piVar4 = param_1;
        if (7 < (uint)param_1[5]) {
          piVar4 = (int *)*param_1;
        }
        if (param_4 != 0) {
          memcpy((void *)((int)piVar4 + param_1[4] * 2),(void *)((int)param_2 + param_3 * 2),
                 param_4 * 2);
        }
        param_1[4] = iVar1;
        if (7 < (uint)param_1[5]) {
          *(undefined2 *)(*param_1 + iVar1 * 2) = 0;
          return param_1;
        }
        *(undefined2 *)((int)param_1 + iVar1 * 2) = 0;
      }
    }
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  std::_Xlength_error("string too long");
}

