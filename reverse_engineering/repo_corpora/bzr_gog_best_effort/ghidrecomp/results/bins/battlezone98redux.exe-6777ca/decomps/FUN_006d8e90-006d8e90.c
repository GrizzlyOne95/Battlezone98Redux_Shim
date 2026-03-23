
int FUN_006d8e90(undefined4 param_1,SOCKET param_2,sockaddr *param_3,int *param_4)

{
  int iVar1;
  int local_8;
  
  local_8 = *param_4;
  iVar1 = getpeername(param_2,param_3,&local_8);
  *param_4 = local_8;
  return iVar1;
}

