
void FUN_004f4010(void)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined1 local_e8 [48];
  undefined4 *local_b8;
  float local_b4;
  int local_b0;
  float local_ac;
  int local_a8;
  float local_a4;
  float local_a0;
  int local_9c;
  float local_98;
  undefined4 local_94 [16];
  undefined4 local_54 [16];
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_b0 = FUN_00417c70();
  if (local_b0 != 0) {
    puVar2 = (undefined4 *)FUN_008203f0();
    puVar6 = local_94;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar2 = local_94;
    puVar6 = local_54;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar6 = puVar6 + 1;
    }
    local_a8 = 0;
    local_b4 = 0.0;
    FUN_005b28e0((double)(DAT_025ce710 * 100.0 * 0.5) + DAT_025ce720,
                 (double)(DAT_025ce718 * 100.0 * 0.5) + DAT_025ce730,0x4049000000000000,local_e8);
    while (cVar1 = FUN_00462710(&local_b8), cVar1 != '\0') {
      local_9c = FUN_004da060(*local_b8);
      if (((local_9c != 0) && (local_9c != local_b0)) &&
         (uVar3 = FUN_0045c4b0(), (uVar3 & 0x600) == 0)) {
        pfVar4 = (float *)(**(code **)(*(int *)(local_9c + 0x18) + 0xc))();
        local_14 = *pfVar4;
        local_10 = pfVar4[1];
        local_c = pfVar4[2];
        FUN_00820180();
        if ((0.0 <= local_c) && (local_c <= 100.0)) {
          iVar5 = FUN_00462400();
          local_a4 = *(float *)(iVar5 + 0xc) * 0.75;
          local_a4 = local_a4 * local_a4;
          local_a0 = local_14 * local_14 + local_10 * local_10;
          local_ac = local_c * local_c + local_a0;
          if (((local_a0 <= local_a4) || (local_a0 <= local_ac * 0.01)) &&
             (local_98 = 1.0 - local_a0 / local_ac, local_98 = local_98 * local_98,
             local_98 = local_98 * local_98, local_98 = local_98 * local_98,
             local_98 = local_98 * local_98, local_98 = local_98 * local_98, local_b4 < local_98)) {
            local_a8 = local_9c;
            local_b4 = local_98;
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

