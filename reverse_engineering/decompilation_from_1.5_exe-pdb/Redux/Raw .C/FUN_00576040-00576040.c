
uint __thiscall FUN_00576040(int param_1,int *param_2)

{
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_10 = 1;
  local_14 = 0;
  if (0 < *(int *)(param_1 + 0x94)) {
    local_14 = *(uint *)(param_1 + 0xa4);
    local_10 = *(int *)(param_1 + 0xa8);
    for (local_c = 1; local_c < *(int *)(param_1 + 0x94); local_c = local_c + 1) {
      if ((((local_10 == 0) && (*(int *)(param_1 + 0xa8 + local_c * 0x1c) == 1)) ||
          ((local_10 == 1 &&
           ((*(int *)(param_1 + 0xa8 + local_c * 0x1c) == 1 &&
            (local_14 < *(uint *)(param_1 + 0xa4 + local_c * 0x1c))))))) ||
         ((local_10 == 0 &&
          ((*(int *)(param_1 + 0xa8 + local_c * 0x1c) == 0 &&
           (*(uint *)(param_1 + 0xa4 + local_c * 0x1c) < local_14)))))) {
        local_14 = *(uint *)(param_1 + 0xa4 + local_c * 0x1c);
        local_10 = *(int *)(param_1 + 0xa8 + local_c * 0x1c);
      }
    }
  }
  *param_2 = local_10;
  return local_14;
}

