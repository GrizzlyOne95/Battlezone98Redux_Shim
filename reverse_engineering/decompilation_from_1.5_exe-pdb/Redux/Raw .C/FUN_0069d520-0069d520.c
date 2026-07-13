
int FUN_0069d520(undefined4 *param_1,int param_2)

{
  int local_c;
  int *local_8;
  
  local_c = 0;
  local_8 = (int *)param_1[3];
  *param_1 = 0xfffffc19;
  param_1[1] = 0;
  while ((local_8 != (int *)0x0 && (local_c == 0))) {
    if (*local_8 == param_2) {
      local_c = 1;
    }
    else {
      local_8 = (int *)local_8[1];
    }
  }
  if (local_c != 0) {
    FUN_0069d440(param_1,local_8);
  }
  return local_c;
}

