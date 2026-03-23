
int FUN_006130a0(int param_1,int param_2)

{
  int iVar1;
  int local_24;
  int local_20;
  int local_c;
  int local_8;
  
  if (param_1 == 0) {
    local_24 = -1;
  }
  else if (param_2 == 0) {
    local_24 = -1;
  }
  else {
    iVar1 = FUN_00417ca0();
    if (iVar1 == 0) {
      local_24 = -1;
    }
    else {
      local_20 = 0x7fffffff;
      local_24 = -1;
      for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
        iVar1 = FUN_00417f40(local_8);
        if ((iVar1 != 0) &&
           ((*(int *)(param_2 + 0x74) == 0x46 ||
            (*(int *)(param_2 + 0x74) == *(int *)(iVar1 + 0x84))))) {
          iVar1 = FUN_00417f60(local_8);
          if (iVar1 == 0) {
            local_c = -0x80000000;
          }
          else if (*(int *)(iVar1 + 8) == param_2) {
            local_c = 0x7fffffff;
          }
          else {
            local_c = *(int *)(*(int *)(iVar1 + 8) + 0x70);
          }
          if (local_c < local_20) {
            local_20 = local_c;
            local_24 = local_8;
          }
        }
      }
    }
  }
  return local_24;
}

