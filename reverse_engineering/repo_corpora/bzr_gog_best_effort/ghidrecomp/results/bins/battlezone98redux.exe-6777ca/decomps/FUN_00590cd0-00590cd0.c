
void FUN_00590cd0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 int param_5)

{
  float fVar1;
  int local_34;
  int local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  int local_20;
  int local_1c;
  int local_18;
  uint local_14;
  ushort local_10;
  ushort local_c;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  FUN_00590eb0(param_1,param_2,param_3,param_4,&local_30,&local_34);
  for (local_18 = 0; fVar1 = DAT_00920ef4, local_18 < local_30; local_18 = local_18 + 1) {
    local_20 = *(int *)(local_34 + local_18 * 4);
    local_14 = *(uint *)(local_20 + 0x10) & 0xff;
    local_c = (ushort)((uint)*(undefined4 *)(local_20 + 0x10) >> 0x10);
    if (local_c != 0) {
      FUN_005e0bc0(1);
      local_10 = FUN_00462590();
      local_7 = (local_c & local_10) != 0;
      local_24 = (uint)(byte)local_7;
      local_6 = (local_c & ~local_10) != 0;
      local_28 = (uint)(byte)local_6;
      local_5 = local_14 == 1;
      local_2c = (uint)(byte)local_5;
      if ((bool)local_7 && (bool)local_6) {
        local_14 = local_2c + 0xc;
      }
      else if ((bool)local_6) {
        local_14 = local_2c + 10;
      }
      else {
        local_14 = local_2c + 8;
      }
    }
    FUN_00590bf0(local_20,1,*(undefined4 *)(param_5 + local_14 * 4));
  }
  DAT_00920ef4 = DAT_00920ef4 - 0.01;
  for (local_1c = 0; local_1c < local_30; local_1c = local_1c + 1) {
    FUN_00590bf0(*(undefined4 *)(local_34 + local_1c * 4),0,DAT_00917584);
  }
  DAT_00920ef4 = fVar1;
  return;
}

