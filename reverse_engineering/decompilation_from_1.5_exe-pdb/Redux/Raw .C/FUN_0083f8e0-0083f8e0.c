
undefined4 * __thiscall FUN_0083f8e0(undefined4 *param_1,undefined4 *param_2)

{
  param_1[5] = 7;
  param_1[4] = 0;
  *(undefined2 *)param_1 = 0;
  if (param_1 != param_2) {
    if (7 < (uint)param_1[5]) {
      operator_delete((void *)*param_1);
    }
    param_1[5] = 7;
    param_1[4] = 0;
    *(undefined2 *)param_1 = 0;
    FID_conflict__Assign_rv(param_2);
  }
  return param_1;
}

