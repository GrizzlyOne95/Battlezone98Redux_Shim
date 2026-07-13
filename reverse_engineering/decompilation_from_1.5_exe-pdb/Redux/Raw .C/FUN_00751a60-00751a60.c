
void FUN_00751a60(undefined4 *param_1)

{
  undefined1 local_40 [16];
  undefined1 local_30 [16];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined1 local_a;
  undefined1 local_9;
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  FUN_0073a590(*param_1,param_1[1]);
  FUN_0073a6e0(&local_18);
  FUN_0073a590(param_1[2],param_1[3]);
  local_18 = local_20;
  local_14 = local_1c;
  FUN_0073a6e0(&local_18);
  local_a = (param_1[6] & 0x1e) != 0;
  local_9 = (param_1[6] & 8) != 0;
  local_8 = (param_1[6] & 0x10) != 0;
  local_7 = local_8;
  local_6 = local_9;
  local_5 = local_a;
  FUN_0073eeb0(local_40,local_30,param_1[6],local_a,local_9,local_8);
  return;
}

