
void FUN_0074f140(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined1 local_38 [16];
  undefined1 local_28 [20];
  uint local_14;
  uint local_10;
  undefined4 local_c;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  FUN_0073a710(param_1);
  FUN_0073a710(param_2);
  if ((((param_3 == 2) || (param_3 == 4)) || (param_3 == 8)) || (param_3 == 0x10)) {
    local_c = 1;
  }
  else {
    local_c = 0;
  }
  local_7 = (undefined1)local_c;
  local_6 = param_3 == 8;
  local_10 = (uint)(byte)local_6;
  local_5 = param_3 == 0x10;
  local_14 = (uint)(byte)local_5;
  FUN_0073eeb0(local_38,local_28,param_3,local_c,local_10,local_14);
  return;
}

