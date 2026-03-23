
int * __thiscall FUN_0083f9c0(int *param_1,undefined2 param_2)

{
  int *piVar1;
  
  if (param_1[5] == 0) {
    FUN_004feb30(1,param_1[4]);
  }
  piVar1 = param_1;
  if (7 < (uint)param_1[5]) {
    piVar1 = (int *)*param_1;
  }
  *(undefined2 *)piVar1 = param_2;
  param_1[4] = 1;
  if ((uint)param_1[5] < 8) {
    *(undefined2 *)((int)param_1 + 2) = 0;
    return param_1;
  }
  *(undefined2 *)(*param_1 + 2) = 0;
  return param_1;
}

