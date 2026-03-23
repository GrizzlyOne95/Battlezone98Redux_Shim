
void FUN_006bd400(uint *param_1,void *param_2,uint param_3)

{
  uint uVar1;
  uint local_1c;
  void *local_c;
  uint local_8;
  
  local_c = param_2;
  local_8 = param_3;
  uVar1 = *param_1 >> 3 & 0x3f;
  if (param_3 != 0) {
    param_1[1] = (param_3 >> 0x1d) + param_1[1];
    *param_1 = *param_1 + param_3 * 8;
    if (*param_1 < param_3 * 8) {
      param_1[1] = param_1[1] + 1;
    }
    if (uVar1 != 0) {
      if (uVar1 + param_3 < 0x41) {
        local_1c = param_3;
      }
      else {
        local_1c = 0x40 - uVar1;
      }
      memcpy((void *)((int)param_1 + uVar1 + 0x18),param_2,local_1c);
      if ((int)(uVar1 + local_1c) < 0x40) {
        return;
      }
      local_c = (void *)((int)param_2 + local_1c);
      local_8 = param_3 - local_1c;
      FUN_006bc2e0(param_1,param_1 + 6);
    }
    for (; 0x3f < local_8; local_8 = local_8 - 0x40) {
      FUN_006bc2e0(param_1,local_c);
      local_c = (void *)((int)local_c + 0x40);
    }
    if (local_8 != 0) {
      memcpy(param_1 + 6,local_c,local_8);
    }
  }
  return;
}

