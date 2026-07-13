
void FUN_00750f90(undefined4 *param_1)

{
  undefined1 local_2c [16];
  undefined1 local_1c [12];
  undefined4 local_10;
  int local_c;
  undefined1 local_5;
  
  FUN_0073a590(*param_1,param_1[1]);
  FUN_0073a6e0(local_1c);
  local_c = param_1[4] + -4;
  switch(param_1[4]) {
  case 4:
    local_10 = 1;
    break;
  default:
    local_10 = 2;
    break;
  case 6:
  case 8:
  case 9:
  case 10:
  case 0xb:
    local_10 = 0;
  }
  local_5 = param_1[4] == 1;
  FUN_0073e240(local_5,local_2c,local_10);
  return;
}

