
bool FUN_006ab3b0(void *param_1,int param_2,void *param_3)

{
  int iVar1;
  
  iVar1 = memcmp(param_1,param_3,param_2 - (int)param_1);
  return iVar1 == 0;
}

