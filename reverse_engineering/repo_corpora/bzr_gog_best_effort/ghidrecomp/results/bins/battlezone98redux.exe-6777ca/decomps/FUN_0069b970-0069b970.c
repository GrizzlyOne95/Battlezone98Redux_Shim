
int FUN_0069b970(int param_1,int *param_2,undefined1 *param_3)

{
  undefined1 *puVar1;
  int iVar2;
  uint local_c;
  int local_8;
  
  local_8 = 4;
  if (*(char *)(param_1 + *param_2) == ' ') {
    *param_2 = *param_2 + 1;
  }
  iVar2 = isdigit((int)*(char *)(param_1 + *param_2));
  if (iVar2 != 0) {
    local_8 = 1;
  }
  local_c = (uint)(iVar2 != 0);
  if (*(char *)(param_1 + *param_2) == '\"') {
    *param_3 = *(undefined1 *)(param_1 + *param_2);
    *param_2 = *param_2 + 1;
    puVar1 = param_3;
    while ((param_3 = puVar1 + 1, *(char *)(param_1 + *param_2) != '\0' &&
           (*(char *)(param_1 + *param_2) != '\"'))) {
      *param_3 = *(undefined1 *)(param_1 + *param_2);
      *param_2 = *param_2 + 1;
      puVar1 = param_3;
    }
    if (*(char *)(param_1 + *param_2) == '\"') {
      *param_3 = *(undefined1 *)(param_1 + *param_2);
      *param_2 = *param_2 + 1;
      param_3 = puVar1 + 2;
    }
  }
  else {
    while (iVar2 = FUN_006991d0(*(undefined1 *)(param_1 + *param_2)), iVar2 != 0) {
      iVar2 = isdigit((int)*(char *)(param_1 + *param_2));
      if ((iVar2 == 0) && (*(char *)(param_1 + *param_2) != '.')) {
        local_c = 0xffffffff;
        local_8 = 4;
      }
      if (local_c != 0xffffffff) {
        if ((local_8 == 3) && (*(char *)(param_1 + *param_2) == '.')) {
          local_c = 0xffffffff;
          local_8 = 4;
        }
        else if (*(char *)(param_1 + *param_2) == '.') {
          local_8 = 3;
        }
      }
      *param_3 = *(undefined1 *)(param_1 + *param_2);
      *param_2 = *param_2 + 1;
      param_3 = param_3 + 1;
    }
  }
  *param_3 = 0;
  if (*(char *)(param_1 + *param_2) != '\0') {
    *param_2 = *param_2 + 1;
  }
  return local_8;
}

