
void * FUN_0042adc0(void *param_1,int param_2,void *param_3)

{
  int iVar1;
  
  iVar1 = param_2 - (int)param_1 >> 2;
  memmove(param_3,param_1,iVar1 << 2);
  return (void *)((int)param_3 + iVar1 * 4);
}

