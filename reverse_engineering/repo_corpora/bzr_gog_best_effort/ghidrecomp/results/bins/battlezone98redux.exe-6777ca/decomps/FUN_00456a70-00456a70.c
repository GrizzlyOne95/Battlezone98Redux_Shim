
void FUN_00456a70(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined1 local_d8 [16];
  int local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  float local_bc;
  undefined4 local_b4;
  int local_b0;
  int local_ac;
  undefined4 local_a8;
  short *local_a4;
  undefined4 local_a0 [16];
  undefined4 local_60 [6];
  float local_48;
  float local_44;
  float local_40;
  double local_38;
  double local_30;
  double local_28;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00447e20();
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50();
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_c8 = FUN_00447e70();
    local_ac = local_c8;
    FUN_00447e90();
    puVar3 = (undefined4 *)
             FUN_006897e0(local_d8,param_1,*(undefined8 *)(local_ac + 0x48),
                          *(undefined8 *)(local_ac + 0x50),*(undefined8 *)(local_ac + 0x58));
    local_20 = *puVar3;
    local_1c = puVar3[1];
    local_18 = puVar3[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    iVar1 = FUN_006895d0();
    if (iVar1 < 1) {
      local_c0 = 8;
      local_c4 = 0xc;
      FUN_006855e0(local_b0 + 0x144,local_18);
      local_a8 = FUN_00685670(local_c0,local_c4);
      local_b4 = FUN_006856a0();
      local_a4 = (short *)FUN_006856c0();
      puVar3 = (undefined4 *)FUN_0081fe60();
      puVar4 = local_a0;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar3 = local_a0;
      puVar4 = local_60;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      local_b4 = FUN_00456700();
      local_38 = local_38 - (double)(local_48 * *(float *)(local_ac + 0x7c));
      local_30 = local_30 - (double)(local_44 * *(float *)(local_ac + 0x7c));
      local_28 = local_28 - (double)(local_40 * *(float *)(local_ac + 0x7c));
      local_bc = *(float *)(local_ac + 0x7c) / *(float *)(local_b0 + 0x17c);
      local_b4 = FUN_00456700();
      *local_a4 = (short)local_a8;
      local_a4[1] = (short)local_a8 + 1;
      local_a4[2] = (short)local_a8 + 4;
      local_a4[3] = (short)local_a8 + 5;
      local_a4[4] = (short)local_a8 + 4;
      local_a4[5] = (short)local_a8 + 1;
      local_a4[6] = (short)local_a8 + 2;
      local_a4[7] = (short)local_a8 + 3;
      local_a4[8] = (short)local_a8 + 6;
      local_a4[9] = (short)local_a8 + 7;
      local_a4[10] = (short)local_a8 + 6;
      local_a4[0xb] = (short)local_a8 + 3;
      local_a4 = local_a4 + 0xc;
      FUN_006856e0();
    }
  }
  FUN_0083e885();
  return;
}

