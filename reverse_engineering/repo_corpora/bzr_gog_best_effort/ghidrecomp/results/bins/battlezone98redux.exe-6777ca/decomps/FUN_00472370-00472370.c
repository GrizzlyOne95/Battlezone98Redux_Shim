
int __thiscall FUN_00472370(int param_1,int param_2)

{
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (10 < local_8) {
      return -1;
    }
    if (*(int *)(param_1 + local_8 * 4) == param_2) break;
    local_8 = local_8 + 1;
  }
  return local_8;
}

