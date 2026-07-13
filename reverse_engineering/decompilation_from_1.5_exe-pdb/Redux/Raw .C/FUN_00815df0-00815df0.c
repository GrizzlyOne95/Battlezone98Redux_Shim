
undefined4
FUN_00815df0(undefined4 param_1,int *param_2,int *param_3,undefined4 param_4,undefined4 param_5,
            char *param_6,int *param_7)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  int *piVar5;
  undefined4 local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  int local_c;
  undefined1 local_5;
  
  if ((*param_3 != *param_2) && (cVar1 = FUN_006fbb10(param_4,param_3), cVar1 == '\0')) {
LAB_00815f19:
    pcVar3 = param_6;
    pcVar4 = param_6;
    piVar5 = param_7;
    FUN_006f21a0(&param_5);
    FUN_0070bd90(param_1,param_2,param_4,pcVar3,pcVar4,piVar5);
    return param_1;
  }
  local_c = *param_3;
  iVar2 = FUN_006d4930(param_2);
  if (*param_3 != iVar2) {
    local_c = FUN_00815fa0(param_3);
    cVar1 = FUN_00717280(&local_c,param_4);
    if (cVar1 == '\0') goto LAB_00815f19;
  }
  cVar1 = __Current_set(param_2);
  if ((cVar1 == '\0') && (iVar2 = FUN_006d6720(param_3), iVar2 != 0)) {
    local_10 = 0;
  }
  else {
    local_10 = 1;
  }
  *param_6 = (char)local_10;
  if (*param_6 == '\0') {
    local_14 = local_c;
  }
  else {
    local_14 = *param_3;
  }
  *(int *)(param_6 + 4) = local_14;
  if (param_7 != (int *)0x0) {
    if (*(int *)(param_6 + 4) == *param_2) {
      local_18 = 0;
    }
    else {
      local_18 = FUN_00815f50(*(undefined4 *)(param_6 + 4));
      local_18 = local_18 + 1;
    }
    *param_7 = local_18;
  }
  local_5 = 1;
  local_1c = 0;
  FUN_007172c0(&local_1c,&local_5);
  return param_1;
}

