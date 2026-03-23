
void FUN_00823090(int param_1,int param_2)

{
  int iVar1;
  char *local_c;
  int local_8;
  
  local_8 = 0;
  for (local_c = (char *)(param_1 + 0x10 + *(int *)(param_1 + 0x114));
      local_c <= (char *)(param_1 + 0x10 + param_2); local_c = local_c + 1) {
    FUN_00689a20(DAT_0091552c,(short)*local_c);
    iVar1 = FUN_0083f040();
    if (*(uint *)(param_1 + 8) < (uint)(local_8 + iVar1)) {
      return;
    }
    local_8 = local_8 + iVar1;
  }
  while( true ) {
    if (*(int *)(param_1 + 0x114) == 0) {
      return;
    }
    iVar1 = *(int *)(param_1 + 0x114) + -1;
    *(int *)(param_1 + 0x114) = iVar1;
    FUN_00689a20(DAT_0091552c,(short)*(char *)(param_1 + iVar1 + 0x10));
    iVar1 = FUN_0083f040();
    if (*(uint *)(param_1 + 8) < (uint)(local_8 + iVar1)) break;
    local_8 = local_8 + iVar1;
  }
  *(int *)(param_1 + 0x114) = *(int *)(param_1 + 0x114) + 1;
  *(int *)(param_1 + 0x118) = *(int *)(param_1 + 8) - local_8;
  return;
}

