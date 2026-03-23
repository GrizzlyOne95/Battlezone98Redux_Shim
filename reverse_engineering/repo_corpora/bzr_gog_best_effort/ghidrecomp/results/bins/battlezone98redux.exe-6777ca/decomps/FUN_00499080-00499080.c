
void FUN_00499080(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  float10 fVar6;
  undefined8 uVar7;
  undefined1 *apuStack_134 [4];
  undefined8 uStack_124;
  undefined8 uStack_11c;
  undefined8 uStack_114;
  undefined1 local_10c [12];
  undefined1 local_100 [12];
  undefined1 local_f4 [12];
  undefined1 local_e8 [4];
  undefined1 local_e4 [4];
  undefined1 local_e0 [4];
  undefined1 local_dc [8];
  undefined1 local_d4 [4];
  float local_d0;
  undefined8 local_cc;
  undefined4 local_c4;
  undefined8 local_c0;
  uint local_b8;
  undefined8 local_b4;
  undefined8 local_ac;
  int local_a4;
  int local_a0;
  int local_9c;
  float *local_98;
  int local_94;
  undefined4 local_90;
  int local_8c;
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
  undefined4 local_40 [4];
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
  local_40[0] = DAT_00917590;
  local_40[1] = DAT_0091757c;
  local_40[2] = DAT_0091759c;
  local_40[3] = DAT_00917560;
  local_30 = DAT_00917598;
  local_2c = DAT_009175b0;
  local_28 = DAT_009175ac;
  local_24 = DAT_00917558;
  local_20 = DAT_009175a8;
  local_1c = DAT_00917578;
  uStack_114 = 4.174447162282717e-306;
  local_18 = FUN_0068bed0();
  uStack_114 = 4.174414568427378e-306;
  local_14 = FUN_0068bed0();
  uStack_114 = 4.17433851609824e-306;
  local_10 = FUN_0068bed0();
  uStack_114 = 4.174305922242901e-306;
  local_c = FUN_0068bed0();
  uStack_114 = (double)CONCAT44(0x49913a,(undefined4)uStack_114);
  FUN_00422170();
  uStack_114 = (double)CONCAT44(local_e8,0x49914b);
  puVar2 = (undefined4 *)FID_conflict_begin();
  local_90 = *puVar2;
  while( true ) {
    uStack_114 = (double)CONCAT44(local_e0,0x49917a);
    uVar3 = FID_conflict_end();
    uStack_114 = (double)CONCAT44(uVar3,0x499186);
    cVar1 = FID_conflict_operator__();
    if (cVar1 == '\0') break;
    uStack_114 = (double)CONCAT44(0x49919c,(undefined4)uStack_114);
    piVar4 = (int *)FUN_00421ec0();
    local_94 = *piVar4;
    uStack_114 = (double)CONCAT44(0x4991bb,(undefined4)uStack_114);
    local_98 = (float *)(**(code **)(*(int *)(local_94 + 0x18) + 0xc))();
    uStack_114 = (double)local_98[2];
    uStack_11c = (double)local_98[1];
    uStack_124 = (double)*local_98;
    apuStack_134[3] = (undefined1 *)DAT_00917594;
    apuStack_134[2] = local_f4;
    apuStack_134[1] = (undefined1 *)0x49920b;
    puVar2 = (undefined4 *)FUN_006897e0();
    local_64 = *puVar2;
    local_60 = puVar2[1];
    local_5c = puVar2[2];
    uStack_114 = (double)CONCAT44(0x49923c,(undefined4)uStack_114);
    local_4c = local_64;
    local_48 = local_60;
    local_44 = local_5c;
    iVar5 = FUN_00462400();
    local_c4 = *(undefined4 *)(iVar5 + 0xc);
    uStack_114 = (double)CONCAT44(local_c4,&local_4c);
    uStack_11c = (double)CONCAT44(DAT_00917594,0x499267);
    iVar5 = FUN_006895d0();
    if (iVar5 < 1) {
      uStack_114 = (double)CONCAT44(&local_4c,&local_4c);
      uStack_11c = (double)CONCAT44(0x499280,(undefined4)uStack_11c);
      fVar6 = (float10)FUN_004428b0();
      local_d0 = (float)fVar6;
      if (local_d0 <= 10000.0) {
        uStack_114 = (double)CONCAT44(0x4992aa,(undefined4)uStack_114);
        piVar4 = (int *)FUN_00421ec0();
        local_a4 = *(int *)(*(int *)(*piVar4 + 0x230) + 0xfc);
        if (local_a4 != 0) {
          uStack_114 = (double)CONCAT44(local_a4,local_100);
          uStack_11c = (double)CONCAT44(0x4992de,(undefined4)uStack_11c);
          puVar2 = (undefined4 *)FUN_0062e120();
          local_7c = *puVar2;
          local_78 = puVar2[1];
          local_74 = puVar2[2];
          uStack_114 = (double)CONCAT44(local_e4,DAT_00917594);
          uStack_11c = (double)CONCAT44(&local_7c,0x49931b);
          local_70 = local_7c;
          local_6c = local_78;
          local_68 = local_74;
          uVar7 = FUN_00497780();
          uStack_114 = (double)CONCAT44(DAT_0091755c,0x49934d);
          local_cc = uVar7;
          local_ac = uVar7;
          FUN_00417990();
          uStack_114 = 2.47032822920623e-323;
          uStack_11c = (double)local_cc;
          uStack_124 = 4.1743711099539704e-306;
          uVar3 = FUN_0068bed0();
          uStack_124 = (double)CONCAT44(uVar3,DAT_00917580);
          apuStack_134[3] = (undefined1 *)0x499383;
          FUN_0068c560();
        }
        uStack_114 = (double)CONCAT44(0x499391,(undefined4)uStack_114);
        local_9c = FUN_00417ca0();
        if (local_9c != 0) {
          uStack_114 = (double)CONCAT44(0x4993af,(undefined4)uStack_114);
          local_b8 = FUN_00417f90();
          for (local_8c = 0; local_8c < 5; local_8c = local_8c + 1) {
            uStack_114 = (double)CONCAT44(local_8c,0x4993ef);
            local_a0 = FUN_00417f40();
            if (local_a0 != 0) {
              uStack_114 = (double)CONCAT44(local_a0,local_10c);
              uStack_11c = (double)CONCAT44(0x499415,(undefined4)uStack_11c);
              puVar2 = (undefined4 *)FUN_0062e120();
              local_88 = *puVar2;
              local_84 = puVar2[1];
              local_80 = puVar2[2];
              uStack_114 = (double)CONCAT44(local_d4,DAT_00917594);
              uStack_11c = (double)CONCAT44(&local_88,0x499458);
              local_58 = local_88;
              local_54 = local_84;
              local_50 = local_80;
              uVar7 = FUN_00497780();
              local_c0 = uVar7;
              local_b4 = uVar7;
              uStack_114 = (double)CONCAT44(local_40[local_8c * 2 +
                                                     (local_b8 >> ((byte)local_8c & 0x1f) & 1)],
                                            0x4994a3);
              FUN_00417990();
              uStack_114 = 2.47032822920623e-323;
              uStack_11c = (double)local_b4;
              uStack_124 = (double)CONCAT44(apuStack_134[*(int *)(local_a0 + 0x84)],DAT_00917580);
              apuStack_134[3] = (undefined1 *)0x4994df;
              FUN_0068c560();
            }
          }
        }
      }
    }
    uStack_114 = (double)ZEXT48(local_dc);
    uStack_11c = (double)CONCAT44(0x499169,(undefined4)uStack_11c);
    FUN_0046b260();
  }
  uStack_114 = (double)CONCAT44(0x4994f6,(undefined4)uStack_114);
  FUN_0083e885();
  return;
}

