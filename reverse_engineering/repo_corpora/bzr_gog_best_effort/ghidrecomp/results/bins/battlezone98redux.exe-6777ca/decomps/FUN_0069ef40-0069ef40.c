
void * FUN_0069ef40(int param_1,int param_2,int param_3,int param_4)

{
  void *pvVar1;
  int local_c;
  int local_8;
  
  pvVar1 = malloc(((param_2 - param_1) + 1) * ((param_4 - param_3) + 1) * 8 + 4 +
                  (param_2 - param_1) * 4);
  if (pvVar1 == (void *)0x0) {
    FUN_0069ee50("allocation failure in NR_Imatrix()");
  }
  local_8 = (int)pvVar1 + (param_2 - param_1) * 4 + 4;
  pvVar1 = (void *)((int)pvVar1 + param_1 * -4);
  for (local_c = param_1; local_c <= param_2; local_c = local_c + 1) {
    *(int *)((int)pvVar1 + local_c * 4) = local_8;
    local_8 = local_8 + 4 + (param_4 - param_3) * 4;
    *(int *)((int)pvVar1 + local_c * 4) = *(int *)((int)pvVar1 + local_c * 4) + param_3 * -4;
  }
  return pvVar1;
}

