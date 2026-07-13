
undefined4 __thiscall
FUN_00432bb0(undefined4 param_1,int *param_2,int *param_3,int param_4,char param_5)

{
  undefined1 *_Src;
  int iVar1;
  char cVar2;
  int local_18;
  undefined1 *local_14;
  undefined4 local_10;
  undefined1 *local_c;
  char local_5;
  
  local_c = (undefined1 *)*param_2;
  *param_3 = *param_2;
  local_5 = *(char *)*param_2;
  local_10 = param_1;
LAB_00432bd5:
  while ((param_4 != 0 || (cVar2 = FUN_00432410(*(undefined1 *)*param_2), cVar2 != '\0'))) {
    _Src = (undefined1 *)*param_2;
    while ((*(char *)*param_2 != '\0' &&
           (cVar2 = FUN_00432e00(*(undefined1 *)*param_2), cVar2 == '\0'))) {
      *param_2 = *param_2 + 1;
    }
    if (local_c < _Src) {
      iVar1 = *param_2;
      memmove(local_c,_Src,iVar1 - (int)_Src);
      local_c[iVar1 - (int)_Src] = 0;
    }
    local_5 = *(char *)*param_2;
    *(undefined1 *)*param_2 = 0;
    if (((param_4 != 0) && (cVar2 = FUN_004282a0(local_c,param_4), cVar2 == '\0')) &&
       (cVar2 = FUN_004282a0(param_4,local_c), cVar2 == '\0')) goto LAB_00432daa;
    if (local_5 == '\0') {
      return 1;
    }
    local_c = local_c + (*param_2 - (int)_Src);
    *(char *)*param_2 = local_5;
    FUN_00432450(param_2);
    *local_c = 10;
    local_c = local_c + 1;
  }
  if (param_5 != '\0') {
    local_14 = (undefined1 *)*param_2;
    local_18 = 0;
    while (cVar2 = FUN_004323c0(*local_14), cVar2 != '\0') {
      cVar2 = FUN_00432e00(*local_14);
      if (cVar2 == '\0') {
        local_14 = local_14 + 1;
      }
      else {
        local_18 = local_18 + 1;
        FUN_00432450(&local_14);
      }
    }
    cVar2 = FUN_00432410(*local_14);
    if (cVar2 != '\0') {
      for (; 0 < local_18; local_18 = local_18 + -1) {
        *local_c = 10;
        local_c = local_c + 1;
      }
      *param_2 = (int)local_14;
      goto LAB_00432bd5;
    }
  }
LAB_00432daa:
  if (*param_3 == *param_2) {
    *param_3 = 0;
    return 0;
  }
  local_c = local_c + -1;
  *local_c = 0;
  if ((param_4 != 0) && (local_5 != '\0')) {
    *(char *)*param_2 = local_5;
    FUN_00432450(param_2);
  }
  return 1;
}

