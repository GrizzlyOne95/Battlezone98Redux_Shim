
void FUN_0074f000(undefined4 param_1,int param_2)

{
  undefined1 local_24 [20];
  undefined4 local_10;
  int local_c;
  undefined1 local_5;
  
  FUN_0073a710(param_1);
  local_c = param_2;
  if (param_2 != 1) {
    if (param_2 == 2) {
      local_10 = 1;
      goto LAB_0074f048;
    }
    if (param_2 != 3) {
      local_10 = 2;
      goto LAB_0074f048;
    }
  }
  local_10 = 2;
LAB_0074f048:
  local_5 = param_2 == 0;
  FUN_0073e240(local_5,local_24,local_10);
  return;
}

