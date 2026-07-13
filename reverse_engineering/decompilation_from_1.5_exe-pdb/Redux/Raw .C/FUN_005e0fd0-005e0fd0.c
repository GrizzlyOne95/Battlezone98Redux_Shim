
int __thiscall FUN_005e0fd0(int param_1,int param_2,int param_3)

{
  int local_8;
  
  local_8 = param_2;
  while( true ) {
    if (param_3 < local_8) {
      return -1;
    }
    if (*(int *)(param_1 + local_8 * 4) != 0) break;
    local_8 = local_8 + 1;
  }
  return local_8;
}

