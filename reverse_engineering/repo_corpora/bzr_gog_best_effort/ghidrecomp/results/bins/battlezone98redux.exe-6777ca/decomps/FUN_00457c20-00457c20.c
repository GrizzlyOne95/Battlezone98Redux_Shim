
void FUN_00457c20(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_434 [192];
  undefined1 local_374 [24];
  undefined1 local_35c [24];
  undefined1 local_344 [16];
  undefined1 local_334 [16];
  undefined1 local_324 [16];
  int local_314;
  float local_310;
  undefined4 local_30c;
  float local_308;
  int local_304;
  float local_300;
  int local_2fc;
  undefined4 local_2f4;
  uint local_2f0;
  float local_2ec;
  int local_2e8;
  uint local_2e4;
  int local_2e0;
  undefined4 local_2dc;
  int local_2d8;
  int local_2d4;
  uint local_2d0;
  int local_2cc;
  short local_2c8;
  short *local_2c4;
  undefined4 local_2c0 [16];
  undefined4 local_280 [16];
  undefined4 local_240 [16];
  undefined4 local_200 [16];
  undefined4 local_1c0 [16];
  undefined4 local_180 [16];
  undefined4 local_140 [16];
  undefined4 local_100 [16];
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00684ca0();
  if (iVar1 != 0) {
    fVar5 = (float10)FUN_00822da0();
    local_310 = (float)fVar5;
    fVar5 = (float10)FUN_00446290(local_310 * *(float *)(local_2d8 + 0x184));
    local_2ec = (float)fVar5;
    FUN_00447e20();
    while( true ) {
      iVar1 = FUN_00447e70();
      FUN_00447e50();
      iVar2 = FUN_00447e70();
      if (iVar1 == iVar2) break;
      local_314 = FUN_00447e70();
      local_2d4 = local_314;
      FUN_00447e90();
      local_2e4 = *(uint *)(local_2d4 + 0x74);
      if (1 < local_2e4) {
        local_2e8 = *(int *)(*(int *)(local_2d4 + 0x70) + -4 + *(int *)(local_2d4 + 0x74) * 4);
        puVar3 = (undefined4 *)
                 FUN_006897e0(local_324,param_1,*(undefined8 *)(local_2e8 + 0x28),
                              *(undefined8 *)(local_2e8 + 0x30),*(undefined8 *)(local_2e8 + 0x38));
        local_70 = *puVar3;
        local_6c = puVar3[1];
        local_68 = puVar3[2];
        local_4c = local_70;
        local_48 = local_6c;
        local_44 = local_68;
        FUN_006855e0(local_2d8 + 0x144,local_68);
        local_2fc = local_2e4 << 2;
        local_304 = (local_2e4 - 1) * 0xc;
        local_30c = FUN_00685670(local_2fc,local_304);
        local_2dc = FUN_006856a0();
        local_2c4 = (short *)FUN_006856c0();
        local_2cc = **(int **)(local_2d4 + 0x70);
        local_2d0 = 1;
        if (*(float *)(local_2cc + 0x40) <= 1.0) {
          puVar3 = (undefined4 *)FUN_0081fe60();
          puVar4 = local_140;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          puVar3 = local_140;
          puVar4 = local_180;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          local_2dc = FUN_004578a0();
        }
        else {
          local_2e0 = *(int *)(*(int *)(local_2d4 + 0x70) + 4);
          local_300 = (1.0 - *(float *)(local_2cc + 0x40)) /
                      (*(float *)(local_2e0 + 0x40) - *(float *)(local_2cc + 0x40));
          puVar3 = (undefined4 *)FUN_0081f1e0(local_334,local_2cc);
          local_90 = *puVar3;
          local_8c = puVar3[1];
          local_88 = puVar3[2];
          local_84 = puVar3[3];
          local_28 = local_90;
          local_24 = local_8c;
          local_20 = local_88;
          local_1c = local_84;
          puVar3 = (undefined4 *)FUN_00447f60(local_374,local_2cc);
          local_a8 = *puVar3;
          local_a4 = puVar3[1];
          local_a0 = puVar3[2];
          local_9c = puVar3[3];
          local_98 = puVar3[4];
          local_94 = puVar3[5];
          local_64 = local_a8;
          local_60 = local_a4;
          local_5c = local_a0;
          local_58 = local_9c;
          local_54 = local_98;
          local_50 = local_94;
          puVar3 = (undefined4 *)FUN_0081f1e0(local_344,local_2e0);
          local_80 = *puVar3;
          local_7c = puVar3[1];
          local_78 = puVar3[2];
          local_74 = puVar3[3];
          local_18 = local_80;
          local_14 = local_7c;
          local_10 = local_78;
          local_c = local_74;
          puVar3 = (undefined4 *)FUN_00447f60(local_35c,local_2e0);
          local_c0 = *puVar3;
          local_bc = puVar3[1];
          local_b8 = puVar3[2];
          local_b4 = puVar3[3];
          local_b0 = puVar3[4];
          local_ac = puVar3[5];
          local_40 = local_c0;
          local_3c = local_bc;
          local_38 = local_b8;
          local_34 = local_b4;
          local_30 = local_b0;
          local_2c = local_ac;
          puVar3 = (undefined4 *)
                   FUN_0044ba00(local_434,&local_90,&local_a8,&local_80,&local_c0,local_300);
          puVar4 = local_200;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          puVar3 = local_200;
          puVar4 = local_280;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          puVar3 = (undefined4 *)FUN_0081fe60();
          puVar4 = local_2c0;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          puVar3 = local_2c0;
          puVar4 = local_240;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          fVar5 = (float10)FUN_00448e60();
          local_308 = (float)fVar5;
          local_2dc = FUN_004578a0();
        }
        for (; local_2d0 < *(uint *)(local_2d4 + 0x74); local_2d0 = local_2d0 + 1) {
          local_2f4 = *(undefined4 *)(*(int *)(local_2d4 + 0x70) + local_2d0 * 4);
          puVar3 = (undefined4 *)FUN_0081fe60();
          puVar4 = local_1c0;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          puVar3 = local_1c0;
          puVar4 = local_100;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          local_2dc = FUN_004578a0();
        }
        local_2c8 = (short)local_30c;
        for (local_2f0 = 0; local_2f0 < local_2e4 - 1; local_2f0 = local_2f0 + 1) {
          *local_2c4 = local_2c8;
          local_2c4[1] = local_2c8 + 1;
          local_2c4[2] = local_2c8 + 4;
          local_2c4[3] = local_2c8 + 5;
          local_2c4[4] = local_2c8 + 4;
          local_2c4[5] = local_2c8 + 1;
          local_2c4[6] = local_2c8 + 2;
          local_2c4[7] = local_2c8 + 3;
          local_2c4[8] = local_2c8 + 6;
          local_2c4[9] = local_2c8 + 7;
          local_2c4[10] = local_2c8 + 6;
          local_2c4[0xb] = local_2c8 + 3;
          local_2c4 = local_2c4 + 0xc;
          local_2c8 = local_2c8 + 4;
        }
        FUN_006856e0();
      }
    }
  }
  FUN_0083e885();
  return;
}

