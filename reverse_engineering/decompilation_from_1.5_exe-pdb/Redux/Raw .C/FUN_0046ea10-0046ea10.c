
int * FUN_0046ea10(int *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  int *local_8;
  
  local_8 = param_1;
  while (param_1 = param_1 + 1, param_1 != param_2) {
    if (*param_1 != *param_3) {
      piVar1 = (int *)FUN_00417780(param_1);
      *local_8 = *piVar1;
      local_8 = local_8 + 1;
    }
  }
  return local_8;
}

