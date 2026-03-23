
void FUN_0079d3f0(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_c;
  int local_8;
  
  iVar1 = (param_2 - param_1) / 0x18;
  local_8 = (param_3 - param_1) / 0x18;
  local_14 = iVar1;
  while (local_14 != 0) {
    iVar2 = local_8 % local_14;
    local_8 = local_14;
    local_14 = iVar2;
  }
  if (local_8 < (param_3 - param_1) / 0x18) {
    for (; 0 < local_8; local_8 = local_8 + -1) {
      iVar2 = local_8 * 0x18 + param_1;
      if (iVar1 * 0x18 + iVar2 == param_3) {
        local_1c = param_1;
      }
      else {
        local_1c = iVar1 * 0x18 + iVar2;
      }
      local_c = local_1c;
      local_18 = iVar2;
      do {
        iter_swap<>(local_18,local_c);
        local_18 = local_c;
        if (iVar1 < (param_3 - local_c) / 0x18) {
          local_20 = iVar1 * 0x18 + local_c;
        }
        else {
          local_20 = (iVar1 - (param_3 - local_c) / 0x18) * 0x18 + param_1;
        }
        local_c = local_20;
      } while (local_20 != iVar2);
    }
  }
  return;
}

