
void __thiscall FUN_006a8f90(undefined4 *param_1,int param_2,int param_3)

{
  void *pvVar1;
  
  param_1[3] = param_2 * param_3;
  param_1[1] = param_2;
  param_1[2] = param_3;
  pvVar1 = malloc(param_1[3]);
  *param_1 = pvVar1;
  return;
}

