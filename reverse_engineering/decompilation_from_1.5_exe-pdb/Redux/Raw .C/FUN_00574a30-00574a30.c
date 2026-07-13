
undefined1 __thiscall FUN_00574a30(int *param_1,int *param_2)

{
  undefined1 local_14;
  
  if (*param_1 < *param_2) {
LAB_00574a84:
    local_14 = 1;
  }
  else {
    if (*param_1 == *param_2) {
      if (((uint)param_1[3] < (uint)param_2[3]) ||
         ((param_1[3] == param_2[3] && ((uint)param_1[2] < (uint)param_2[2])))) goto LAB_00574a84;
    }
    local_14 = 0;
  }
  return local_14;
}

