
undefined4 FUN_006996c0(int param_1,int *param_2,int param_3,char *param_4)

{
  int iVar1;
  char local_5;
  
  local_5 = '\x14';
  do {
    iVar1 = FUN_006991d0(local_5);
    if (iVar1 != 0) {
      if (local_5 == '#') {
        *param_4 = '#';
        param_4 = param_4 + 1;
        local_5 = *(char *)(param_1 + *param_2);
        *param_2 = *param_2 + 1;
        if (param_3 < *param_2) {
          return 0xffffffff;
        }
      }
      if (local_5 == '{') {
        *param_4 = '{';
        param_4 = param_4 + 1;
        *param_2 = *param_2 + 1;
        if (param_3 < *param_2) {
          return 0xffffffff;
        }
      }
      else {
        while (iVar1 = FUN_006991d0(local_5), iVar1 == 1) {
          *param_4 = local_5;
          param_4 = param_4 + 1;
          local_5 = *(char *)(param_1 + *param_2);
          *param_2 = *param_2 + 1;
          if (param_3 < *param_2) {
            return 0xffffffff;
          }
        }
      }
      *param_2 = *param_2 + -1;
      *param_4 = '\0';
      return 1;
    }
    local_5 = *(char *)(param_1 + *param_2);
    *param_2 = *param_2 + 1;
  } while (*param_2 <= param_3);
  return 0xffffffff;
}

