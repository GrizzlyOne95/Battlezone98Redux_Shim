
undefined4
FUN_00787a30(char *param_1,char *param_2,char *param_3,char *param_4,size_t param_5,char *param_6)

{
  int iVar1;
  
  if (param_4 != param_3) {
    strncpy(param_4,param_3,param_5);
  }
  param_4[param_5 - 1] = '\0';
  if (((*param_6 != '\0') && (*param_1 != '\0')) && (*param_2 != '\0')) {
    iVar1 = FUN_00787370(param_6);
    if (iVar1 != 0) {
      FUN_00787660(param_1,param_2,param_4,param_5);
    }
  }
  return 0;
}

