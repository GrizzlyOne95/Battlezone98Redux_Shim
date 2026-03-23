
void FUN_004c4fa0(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_218 [8];
  undefined4 local_210;
  undefined4 local_20c;
  int local_208;
  int local_204;
  int local_200;
  undefined1 local_1fc [300];
  undefined4 auStack_d0 [8];
  undefined4 auStack_b0 [32];
  undefined4 auStack_30 [10];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_20c = DAT_00920ef4;
  local_210 = 5;
  FUN_00783320(local_1fc,*param_1,param_1[2]);
  for (local_200 = 0; local_200 < 0x19; local_200 = local_200 + 1) {
    puVar2 = (undefined4 *)FUN_004c6f30(local_218,local_1fc + local_200 * 0xc,DAT_00917594);
    uVar1 = puVar2[1];
    auStack_d0[local_200 * 2] = *puVar2;
    auStack_d0[local_200 * 2 + 1] = uVar1;
  }
  DAT_00920ef4 = 0x3f000000;
  for (local_200 = 0; local_200 < 4; local_200 = local_200 + 1) {
    FUN_0068af40(DAT_00917580,auStack_d0[local_200 * 2],auStack_d0[local_200 * 2 + 1],
                 auStack_d0[local_200 * 2 + 2],auStack_d0[local_200 * 2 + 3],DAT_0091755c,0);
    FUN_0068af40(DAT_00917580,auStack_d0[local_200 * 10],auStack_d0[local_200 * 10 + 1],
                 auStack_d0[(local_200 + 1) * 10],auStack_d0[(local_200 + 1) * 10 + 1],DAT_0091755c,
                 0);
    FUN_0068af40(DAT_00917580,auStack_30[local_200 * 2],auStack_30[local_200 * 2 + 1],
                 auStack_30[local_200 * 2 + 2],auStack_30[local_200 * 2 + 3],DAT_0091755c,0);
    FUN_0068af40(DAT_00917580,auStack_b0[local_200 * 10],auStack_b0[local_200 * 10 + 1],
                 auStack_b0[(local_200 + 1) * 10],auStack_b0[(local_200 + 1) * 10 + 1],DAT_0091755c,
                 0);
  }
  for (local_204 = 1; local_204 < 4; local_204 = local_204 + 1) {
    for (local_200 = 0; local_200 < 4; local_200 = local_200 + 1) {
      FUN_0068af40(DAT_00917580,auStack_d0[(local_204 * 5 + local_200) * 2],
                   auStack_d0[(local_204 * 5 + local_200) * 2 + 1],
                   auStack_d0[(local_204 * 5 + 1 + local_200) * 2],
                   auStack_d0[(local_204 * 5 + 1 + local_200) * 2 + 1],DAT_00917588,0);
      FUN_0068af40(DAT_00917580,auStack_d0[(local_200 * 5 + local_204) * 2],
                   auStack_d0[(local_200 * 5 + local_204) * 2 + 1],
                   auStack_d0[((local_200 + 1) * 5 + local_204) * 2],
                   auStack_d0[((local_200 + 1) * 5 + local_204) * 2 + 1],DAT_00917588,0);
    }
  }
  for (local_204 = 0; local_204 < 4; local_204 = local_204 + 1) {
    for (local_200 = 0; local_200 < 4; local_200 = local_200 + 1) {
      FUN_0068af40(DAT_00917580,auStack_d0[(local_204 * 5 + local_200) * 2],
                   auStack_d0[(local_204 * 5 + local_200) * 2 + 1],
                   auStack_d0[((local_204 + 1) * 5 + 1 + local_200) * 2],
                   auStack_d0[((local_204 + 1) * 5 + 1 + local_200) * 2 + 1],
                   *(undefined4 *)(local_208 + 0x24),0);
    }
  }
  DAT_00920ef4 = local_20c;
  FUN_0083e885();
  return;
}

