
void FUN_00696080(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_18 = (int)((param_2 - param_4) + (param_2 - param_4 >> 0x1f & 0xfU)) >> 4;
  if (local_18 < 0) {
    local_18 = 0;
  }
  local_1c = (int)(param_2 + param_4 + (param_2 + param_4 >> 0x1f & 0xfU)) >> 4;
  if (*(int *)(param_1 + 0x7c) <= local_1c) {
    local_1c = *(int *)(param_1 + 0x7c) + -1;
  }
  local_10 = (int)((param_3 - param_4) + (param_3 - param_4 >> 0x1f & 0xfU)) >> 4;
  if (local_10 < 0) {
    local_10 = 0;
  }
  local_14 = (int)(param_3 + param_4 + (param_3 + param_4 >> 0x1f & 0xfU)) >> 4;
  if (*(int *)(param_1 + 0x78) <= local_14) {
    local_14 = *(int *)(param_1 + 0x78) + -1;
  }
  for (local_8 = local_10; local_8 <= local_14; local_8 = local_8 + 1) {
    for (local_c = local_18; local_c <= local_1c; local_c = local_c + 1) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x90) + local_8 * 4) + local_c * 4) = 1;
    }
  }
  return;
}

