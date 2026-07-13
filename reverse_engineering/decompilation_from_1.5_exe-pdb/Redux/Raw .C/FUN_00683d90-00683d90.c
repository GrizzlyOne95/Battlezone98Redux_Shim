
int * __thiscall FUN_00683d90(int *param_1,int param_2,undefined4 param_3)

{
  int local_c;
  
  *param_1 = param_2;
  if (param_2 == 0) {
    local_c = 0;
  }
  else {
    local_c = FUN_00683e90(param_2,param_3);
  }
  param_1[1] = local_c;
  return param_1;
}

