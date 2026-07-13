
int __thiscall FUN_00825de0(undefined4 param_1,char *param_2,undefined4 param_3)

{
  int iVar1;
  
  while( true ) {
    iVar1 = FUN_00825e20(param_2,param_3,param_1);
    if (iVar1 != 0) {
      return iVar1;
    }
    param_2 = param_2 + 1;
    if (*param_2 == '\0') break;
    param_1 = 0;
  }
  return -1;
}

