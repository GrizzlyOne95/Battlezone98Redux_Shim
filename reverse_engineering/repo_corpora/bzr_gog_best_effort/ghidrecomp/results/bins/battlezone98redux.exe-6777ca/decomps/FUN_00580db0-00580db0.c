
int FUN_00580db0(void *param_1,int param_2,void *param_3)

{
  void *pvVar1;
  
  pvVar1 = memmove(param_3,param_1,param_2 - (int)param_1);
  return (int)pvVar1 + (param_2 - (int)param_1);
}

