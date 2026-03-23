
undefined4 __thiscall
FUN_00430cc0(int param_1,uint *param_2,uint *param_3,uint *param_4,uint *param_5,undefined4 *param_6
            )

{
  undefined1 *puVar1;
  char cVar2;
  undefined4 uVar3;
  undefined1 *local_8;
  
  *param_6 = 0;
  do {
    while( true ) {
      while( true ) {
        if (*(char *)*param_2 == '\0') {
          return 0;
        }
        while ((*(char *)*param_2 != '\0' &&
               (cVar2 = FUN_004323c0(*(undefined1 *)*param_2), cVar2 != '\0'))) {
          *param_2 = *param_2 + 1;
        }
        if (*(char *)*param_2 == '\0') {
          return 0;
        }
        cVar2 = FUN_00432410(*(undefined1 *)*param_2);
        if (cVar2 == '\0') break;
        FUN_00432bb0(param_2,param_6,0,1);
      }
      if (*(char *)*param_2 == '[') break;
      *param_4 = *param_2;
      while (((*(char *)*param_2 != '\0' && (*(char *)*param_2 != '=')) &&
             (cVar2 = FUN_00432e00(*(undefined1 *)*param_2), cVar2 == '\0'))) {
        *param_2 = *param_2 + 1;
      }
      if (*(char *)*param_2 == '=') {
        if (*param_4 != *param_2) {
          local_8 = (undefined1 *)*param_2;
          goto LAB_00430f54;
        }
        while ((*(char *)*param_2 != '\0' &&
               (cVar2 = FUN_00432e00(*(undefined1 *)*param_2), cVar2 == '\0'))) {
          *param_2 = *param_2 + 1;
        }
      }
    }
    *param_2 = *param_2 + 1;
    while ((*(char *)*param_2 != '\0' &&
           (cVar2 = FUN_004323c0(*(undefined1 *)*param_2), cVar2 != '\0'))) {
      *param_2 = *param_2 + 1;
    }
    *param_3 = *param_2;
    while (((*(char *)*param_2 != '\0' && (*(char *)*param_2 != ']')) &&
           (cVar2 = FUN_00432e00(*(undefined1 *)*param_2), cVar2 == '\0'))) {
      *param_2 = *param_2 + 1;
    }
  } while (*(char *)*param_2 != ']');
  local_8 = (undefined1 *)*param_2;
  do {
    puVar1 = local_8;
    local_8 = puVar1 + -1;
    if (local_8 < (undefined1 *)*param_3) break;
    cVar2 = FUN_004323c0(*local_8);
  } while (cVar2 != '\0');
  *puVar1 = 0;
  *param_2 = *param_2 + 1;
  while ((*(char *)*param_2 != '\0' &&
         (cVar2 = FUN_00432e00(*(undefined1 *)*param_2), cVar2 == '\0'))) {
    *param_2 = *param_2 + 1;
  }
  *param_4 = 0;
  *param_5 = 0;
  return 1;
  while (cVar2 = FUN_004323c0(*local_8), cVar2 != '\0') {
LAB_00430f54:
    puVar1 = local_8;
    local_8 = puVar1 + -1;
    if (local_8 < (undefined1 *)*param_4) break;
  }
  *puVar1 = 0;
  *param_2 = *param_2 + 1;
  while (((*(char *)*param_2 != '\0' &&
          (cVar2 = FUN_00432e00(*(undefined1 *)*param_2), cVar2 == '\0')) &&
         (cVar2 = FUN_004323c0(*(undefined1 *)*param_2), cVar2 != '\0'))) {
    *param_2 = *param_2 + 1;
  }
  *param_5 = *param_2;
  while ((*(char *)*param_2 != '\0' &&
         (cVar2 = FUN_00432e00(*(undefined1 *)*param_2), cVar2 == '\0'))) {
    *param_2 = *param_2 + 1;
  }
  local_8 = (undefined1 *)(*param_2 - 1);
  if (*(char *)*param_2 != '\0') {
    FUN_00432450(param_2);
  }
  while (((undefined1 *)*param_5 <= local_8 && (cVar2 = FUN_004323c0(*local_8), cVar2 != '\0'))) {
    local_8 = local_8 + -1;
  }
  local_8[1] = 0;
  if ((*(char *)(param_1 + 0x1e) != '\0') && (cVar2 = FUN_00432b40(*param_5), cVar2 != '\0')) {
    uVar3 = FUN_00432bb0(param_2,param_5,*param_5 + 3,0);
    return uVar3;
  }
  return 1;
}

