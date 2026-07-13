
SOCKET FUN_006d8d20(undefined4 param_1,SOCKET param_2,sockaddr *param_3,int *param_4)

{
  SOCKET SVar1;
  int local_10;
  int *local_c;
  int local_8;
  
  if (param_4 == (int *)0x0) {
    local_8 = 0;
  }
  else {
    local_8 = *param_4;
  }
  local_10 = local_8;
  if (param_4 == (int *)0x0) {
    local_c = (int *)0x0;
  }
  else {
    local_c = &local_10;
  }
  SVar1 = accept(param_2,param_3,local_c);
  if (param_4 != (int *)0x0) {
    *param_4 = local_10;
  }
  return SVar1;
}

