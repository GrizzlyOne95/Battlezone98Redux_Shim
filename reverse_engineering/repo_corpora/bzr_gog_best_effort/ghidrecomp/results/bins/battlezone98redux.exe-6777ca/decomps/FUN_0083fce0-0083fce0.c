
int * __thiscall FUN_0083fce0(int *param_1,int *param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  char cVar3;
  int *piVar4;
  
  if (param_2 != (int *)0x0) {
    uVar2 = param_1[5];
    piVar4 = param_1;
    if (7 < uVar2) {
      piVar4 = (int *)*param_1;
    }
    if (piVar4 <= param_2) {
      piVar4 = param_1;
      if (7 < uVar2) {
        piVar4 = (int *)*param_1;
      }
      if (param_2 < (int *)((int)piVar4 + param_1[4] * 2)) {
        piVar4 = param_1;
        if (7 < uVar2) {
          piVar4 = (int *)*param_1;
        }
        piVar4 = (int *)FUN_0083fb60(param_1,(int)param_2 - (int)piVar4 >> 1,param_3);
        return piVar4;
      }
    }
  }
  if (-param_1[4] - 1U <= param_3) {
                    /* WARNING: Subroutine does not return */
    std::_Xlength_error("string too long");
  }
  if (param_3 != 0) {
    iVar1 = param_1[4] + param_3;
    cVar3 = FID_conflict__Grow(iVar1,0);
    if (cVar3 != '\0') {
      piVar4 = param_1;
      if (7 < (uint)param_1[5]) {
        piVar4 = (int *)*param_1;
      }
      if (param_3 != 0) {
        memcpy((void *)((int)piVar4 + param_1[4] * 2),param_2,param_3 * 2);
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

