
int __thiscall FUN_00592c00(int param_1,int param_2)

{
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (*(int *)(param_1 + 4) <= local_8) {
      return -1;
    }
    if (*(int *)(*(int *)(param_1 + 0x10) + 0xc + local_8 * 8) == param_2) break;
    local_8 = local_8 + 1;
  }
  return local_8;
}

