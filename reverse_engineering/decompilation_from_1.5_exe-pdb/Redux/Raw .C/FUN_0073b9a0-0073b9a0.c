
undefined1 __thiscall FUN_0073b9a0(int *param_1,int *param_2)

{
  undefined1 local_14;
  
  if (*param_2 < *param_1) {
LAB_0073b9f4:
    local_14 = 1;
  }
  else {
    if (*param_1 == *param_2) {
      if (((uint)param_2[3] < (uint)param_1[3]) ||
         (((uint)param_2[3] <= (uint)param_1[3] && ((uint)param_2[2] < (uint)param_1[2]))))
      goto LAB_0073b9f4;
    }
    local_14 = 0;
  }
  return local_14;
}

