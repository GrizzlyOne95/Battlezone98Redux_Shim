
void FUN_004e3810(int param_1,int param_2)

{
  int local_34;
  int local_30;
  undefined4 *local_2c;
  int local_28;
  int local_24;
  uint local_20;
  int *local_1c;
  undefined1 local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = (int *)0x0;
  local_28 = 0;
  for (local_20 = 0; local_20 < 0x400; local_20 = local_20 + 1) {
    if (*(int *)(&DAT_02a0db30 + local_20 * 0x18) == 0) {
      local_1c = (int *)(&DAT_02a0db28 + local_20 * 0x18);
      if (local_28 == DAT_00917b04) break;
    }
    else {
      local_28 = local_28 + 1;
      local_30 = local_20 * 0x18;
      if ((*(int *)(&DAT_02a0db28 + local_30) == param_1) &&
         (*(int *)(&DAT_02a0db2c + local_30) == param_2)) {
        *(int *)(&DAT_02a0db34 + local_20 * 0x18) = *(int *)(&DAT_02a0db34 + local_20 * 0x18) + 1;
        goto LAB_004e397f;
      }
    }
  }
  if (local_1c == (int *)0x0) {
    local_1c = (int *)FUN_004e3750();
  }
  if (local_1c != (int *)0x0) {
    FUN_004e31a0(local_18,param_1,param_2,0x6f65672e);
    local_24 = FUN_00829130(local_18,&local_34);
    if (local_24 != 0) {
      local_2c = (undefined4 *)FUN_004e39b0(local_24);
      FUN_0062f240(local_24);
      *local_2c = local_1c;
      *local_1c = param_1;
      local_1c[1] = param_2;
      local_1c[2] = (int)local_2c;
      local_1c[3] = 1;
      local_1c[4] = local_34;
      DAT_00917b04 = DAT_00917b04 + 1;
    }
  }
LAB_004e397f:
  FUN_0083e885();
  return;
}

