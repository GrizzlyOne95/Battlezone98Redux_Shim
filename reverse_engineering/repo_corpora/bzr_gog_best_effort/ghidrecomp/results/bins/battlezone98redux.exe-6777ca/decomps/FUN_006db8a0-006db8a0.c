
int * FUN_006db8a0(int *param_1,undefined4 *param_2)

{
  int local_8;
  
  if (param_1 == (int *)0x0) {
    local_8 = 0;
  }
  else {
    local_8 = (int)param_1 + *(int *)(*param_1 + 4);
  }
  (*(code *)*param_2)(local_8,param_2[2],param_2[3]);
  return param_1;
}

