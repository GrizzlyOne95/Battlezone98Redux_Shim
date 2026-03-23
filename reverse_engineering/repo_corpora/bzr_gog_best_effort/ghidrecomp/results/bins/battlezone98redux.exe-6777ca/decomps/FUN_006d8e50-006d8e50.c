
int FUN_006d8e50(undefined4 param_1,SOCKET param_2,int param_3,int param_4,char *param_5,
                int *param_6)

{
  int iVar1;
  int local_8;
  
  local_8 = *param_6;
  iVar1 = getsockopt(param_2,param_3,param_4,param_5,&local_8);
  *param_6 = local_8;
  return iVar1;
}

