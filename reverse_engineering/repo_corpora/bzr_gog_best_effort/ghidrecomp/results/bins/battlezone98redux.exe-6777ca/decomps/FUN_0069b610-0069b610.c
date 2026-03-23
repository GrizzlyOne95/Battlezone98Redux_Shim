
int FUN_0069b610(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int local_8;
  
  bVar1 = false;
  local_8 = 1;
  while (!bVar1) {
    if (param_2 == param_3) {
      bVar1 = true;
    }
    else {
      if (*(char *)(param_1 + param_2) == '{') {
        local_8 = local_8 + 1;
      }
      if ((*(char *)(param_1 + param_2) == '}') && (local_8 = local_8 + -1, local_8 == 0)) {
        bVar1 = true;
      }
    }
    if (!bVar1) {
      param_2 = param_2 + 1;
    }
  }
  return param_2;
}

