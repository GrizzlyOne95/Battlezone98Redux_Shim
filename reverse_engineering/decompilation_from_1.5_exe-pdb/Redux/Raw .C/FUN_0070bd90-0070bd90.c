
undefined4
FUN_0070bd90(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            char *param_5,int *param_6)

{
  char cVar1;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  char local_7;
  char local_6;
  char local_5;
  
  local_18 = 0;
  local_10 = FUN_00433f60(param_2);
  local_c = FUN_006d6700(&local_10);
  local_14 = 0;
  local_5 = '\x01';
  while (local_c != 0) {
    local_18 = local_18 + 1;
    local_10 = local_c;
    local_5 = FUN_006fbb10(param_3,&local_c);
    if (local_5 == '\0') {
      local_14 = local_10;
      local_1c = FUN_006d6730(&local_c);
    }
    else {
      local_1c = FUN_006d6720(&local_c);
    }
    local_c = local_1c;
  }
  if (param_6 != (int *)0x0) {
    *param_6 = local_18;
  }
  if (local_14 != 0) {
    cVar1 = FUN_00717280(&local_14,param_3);
    if (cVar1 == '\0') {
      local_6 = '\0';
      goto LAB_0070be5f;
    }
  }
  local_6 = '\x01';
LAB_0070be5f:
  local_7 = local_6;
  if (local_6 != '\0') {
    *param_5 = local_5;
    *(int *)(param_5 + 4) = local_10;
  }
  FUN_007172c0(&local_14,&local_7);
  return param_1;
}

