
void FUN_007519d0(undefined4 *param_1)

{
  undefined1 local_3c [16];
  undefined1 local_2c [16];
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_6;
  undefined1 local_5;
  
  FUN_0073a590(*param_1,param_1[1]);
  FUN_0073a6e0(&local_14);
  FUN_0073a590(param_1[2],param_1[3]);
  local_14 = local_1c;
  local_10 = local_18;
  FUN_0073a6e0(&local_14);
  local_6 = *(char *)(param_1 + 4) != '\0';
  local_5 = local_6;
  FUN_00741b20(local_3c,local_2c,local_6);
  return;
}

