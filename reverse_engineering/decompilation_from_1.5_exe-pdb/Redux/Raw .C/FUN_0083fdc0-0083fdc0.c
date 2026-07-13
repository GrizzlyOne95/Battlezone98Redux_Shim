
int * __thiscall FUN_0083fdc0(int *param_1,int *param_2,uint param_3)

{
  uint uVar1;
  int *piVar2;
  
  if (param_2 != (int *)0x0) {
    uVar1 = param_1[5];
    piVar2 = param_1;
    if (7 < uVar1) {
      piVar2 = (int *)*param_1;
    }
    if (piVar2 <= param_2) {
      piVar2 = param_1;
      if (7 < uVar1) {
        piVar2 = (int *)*param_1;
      }
      if (param_2 < (int *)((int)piVar2 + param_1[4] * 2)) {
        piVar2 = param_1;
        if (7 < uVar1) {
          piVar2 = (int *)*param_1;
        }
        piVar2 = (int *)FID_conflict_assign(param_1,(int)param_2 - (int)piVar2 >> 1,param_3);
        return piVar2;
      }
    }
  }
  if (0x7ffffffe < param_3) {
                    /* WARNING: Subroutine does not return */
    std::_Xlength_error("string too long");
  }
  if ((uint)param_1[5] < param_3) {
    FUN_004feb30(param_3,param_1[4]);
    if (param_3 == 0) {
      return param_1;
    }
  }
  else if (param_3 == 0) {
    param_1[4] = 0;
    if (7 < (uint)param_1[5]) {
      *(undefined2 *)*param_1 = 0;
      return param_1;
    }
    *(undefined2 *)param_1 = 0;
    return param_1;
  }
  piVar2 = param_1;
  if (7 < (uint)param_1[5]) {
    piVar2 = (int *)*param_1;
  }
  if (param_3 != 0) {
    memcpy(piVar2,param_2,param_3 * 2);
  }
  param_1[4] = param_3;
  if ((uint)param_1[5] < 8) {
    *(undefined2 *)((int)param_1 + param_3 * 2) = 0;
    return param_1;
  }
  *(undefined2 *)(*param_1 + param_3 * 2) = 0;
  return param_1;
}

