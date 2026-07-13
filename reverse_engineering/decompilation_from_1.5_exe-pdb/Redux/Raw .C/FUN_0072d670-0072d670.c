
int FUN_0072d670(int *param_1)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  uint local_18;
  int local_14;
  int local_10;
  int local_c;
  char local_5;
  
  local_14 = FUN_006d6720(param_1);
  if (local_14 == *param_1) {
    local_14 = 0;
  }
  else {
    local_10 = FUN_006d6700(&local_14);
    local_c = FUN_006d6730(&local_14);
    local_5 = local_10 == *param_1;
    local_18 = (uint)(byte)local_5;
    if (local_c == 0) {
      if ((bool)local_5) {
        local_24 = 0;
        FUN_006d76c0(param_1,&local_24);
        FUN_006d76e0(param_1,param_1);
        FUN_006d7700(param_1,param_1);
      }
      else {
        local_28 = 0;
        FUN_006d76e0(&local_10,&local_28);
        FUN_006d76e0(param_1,&local_10);
      }
    }
    else {
      FUN_006d76c0(&local_c,&local_10);
      local_1c = FUN_006d66c0(local_c);
      FUN_006d76e0(param_1,&local_1c);
      if (local_5 == '\0') {
        local_20 = FUN_006d6700(param_1);
        FUN_006d76e0(&local_20,&local_c);
      }
      else {
        FUN_006d76c0(param_1,&local_c);
      }
    }
  }
  return local_14;
}

