
void FUN_00457650(float param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_38 [4];
  undefined4 local_34;
  undefined4 *local_30;
  undefined4 local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  float local_20;
  undefined1 local_1c [4];
  int local_18;
  uint local_14;
  int local_10;
  undefined4 *local_c;
  uint local_8;
  
  FUN_00447e20(local_1c);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_38);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_28 = (undefined4 *)FUN_00447e70();
    local_c = local_28;
    FUN_00447e90();
    if (local_c[0x1d] != 0) {
      local_10 = *(int *)local_c[0x1c];
      *(float *)(local_10 + 0x40) =
           param_1 * *(float *)(local_18 + 0x178) + *(float *)(local_10 + 0x40);
      local_20 = *(float *)(local_10 + 0x40);
      local_14 = 0;
      for (local_8 = 1; local_8 < (uint)local_c[0x1d]; local_8 = local_8 + 1) {
        local_10 = *(int *)(local_c[0x1c] + local_8 * 4);
        *(float *)(local_10 + 0x40) =
             param_1 * *(float *)(local_18 + 0x178) + *(float *)(local_10 + 0x40);
        if ((local_20 <= 1.0) || (*(float *)(local_10 + 0x40) <= 1.0)) {
          local_20 = *(float *)(local_10 + 0x40);
        }
        else {
          local_20 = *(float *)(local_10 + 0x40);
          local_14 = local_14 + 1;
        }
      }
      if (local_14 != 0) {
        for (local_8 = 0; local_8 < local_14; local_8 = local_8 + 1) {
          local_2c = *(undefined4 *)(local_c[0x1c] + local_8 * 4);
          FUN_00456f20(local_2c);
        }
        for (local_8 = 0; local_8 < local_c[0x1d] - local_14; local_8 = local_8 + 1) {
          *(undefined4 *)(local_c[0x1c] + local_8 * 4) =
               *(undefined4 *)(local_c[0x1c] + (local_8 + local_14) * 4);
        }
        local_c[0x1d] = local_c[0x1d] - local_14;
      }
    }
    if ((*(char *)(local_c + 7) == '\0') || (param_1 <= 0.0)) {
      if ((uint)local_c[0x1d] < 2) {
        local_30 = local_c;
        local_24 = local_c;
        if (local_c == (undefined4 *)0x0) {
          local_34 = 0;
        }
        else {
          local_34 = (**(code **)*local_c)(1);
        }
      }
    }
    else {
      FUN_004584c0(local_c);
    }
  }
  return;
}

