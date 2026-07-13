
void __thiscall FUN_005ac580(int param_1,float param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  float *pfVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_61c [128];
  undefined1 local_59c [200];
  undefined1 local_4d4 [12];
  undefined1 local_4c8 [12];
  undefined1 local_4bc [12];
  undefined1 local_4b0 [12];
  undefined1 local_4a4 [12];
  undefined1 local_498 [12];
  undefined1 local_48c [12];
  undefined1 local_480 [12];
  undefined1 local_474 [12];
  undefined1 local_468 [12];
  undefined1 local_45c [12];
  undefined1 local_450 [12];
  undefined1 local_444 [24];
  undefined1 local_42c [12];
  float local_420;
  float local_41c;
  float local_418;
  float local_414;
  float local_410;
  float local_40c;
  float local_408;
  float local_404;
  float local_400;
  float local_3fc;
  float local_3f8;
  float local_3f4;
  float local_3f0;
  float local_3ec;
  int *local_3e8;
  float local_3e4;
  float local_3e0;
  float local_3dc;
  float local_3d8;
  float local_3d4;
  undefined4 local_3d0;
  int local_3cc;
  float local_3c8;
  undefined4 local_3c4;
  float local_3c0;
  float local_3bc;
  float local_3b8;
  float local_3b4;
  undefined4 local_3b0;
  float local_3ac;
  float local_3a8;
  float local_3a4;
  float local_3a0;
  float local_39c;
  float local_398;
  int local_394;
  float local_390;
  float local_38c;
  int local_388;
  int local_384;
  undefined4 *local_380;
  char local_37a;
  undefined1 local_379;
  undefined4 *local_378;
  undefined4 *local_374;
  int local_370;
  float local_368;
  float local_35c;
  float local_354;
  float local_350;
  float local_34c;
  float local_348;
  float local_344;
  float local_340;
  undefined4 local_33c [16];
  undefined4 local_2fc [16];
  undefined4 local_2bc [16];
  undefined4 local_27c [16];
  undefined4 local_23c [16];
  undefined4 local_1fc [16];
  undefined4 local_1bc [20];
  undefined4 local_16c;
  undefined4 local_144;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
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
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_370 = param_1;
  if ((-1 < *(int *)(param_1 + 0x314)) &&
     ((iVar2 = FUN_0062a540(), iVar2 != 0 || (*local_3e8 != 1)))) {
    FUN_0062a5d0();
    *(undefined4 *)(local_370 + 0x314) = 0xffffffff;
    fVar7 = (float10)FUN_0062e590(*(undefined4 *)(local_370 + 0xf4));
    *(float *)(*(int *)(local_370 + 0xf0) + 0x14) = (float)fVar7;
    FUN_004db100();
  }
  if (((*(uint *)(*(int *)(local_370 + 0xf4) + 0x14) & 0x200) != 0) &&
     (cVar1 = FUN_004723d0(), cVar1 != '\0')) {
    FUN_005aed80();
  }
  FUN_005af7b0();
  if (*(int *)(local_370 + 0x228) == 0) {
LAB_005ac70a:
    local_3c4 = 0;
  }
  else {
    if ((*(int *)(local_370 + 0x228) == 3) || (*(int *)(*(int *)(local_370 + 0x230) + 0xe0) != 0)) {
      local_379 = 1;
    }
    else {
      local_379 = 0;
    }
    cVar1 = FUN_005ac270();
    if (cVar1 == '\0') goto LAB_005ac70a;
    local_3c4 = 1;
  }
  local_37a = (char)local_3c4;
  local_3b0 = *(undefined4 *)(local_370 + 0x228);
  switch(local_3b0) {
  case 0:
    if (*(int *)(*(int *)(local_370 + 0x230) + 0xe0) != 0) {
      *(undefined4 *)(local_370 + 0x228) = 1;
      *(undefined4 *)(*(int *)(local_370 + 0x230) + 0xe0) = 0;
      FUN_004376c0();
      FUN_0062a270();
      *(undefined4 *)(local_370 + 0x318) = *(undefined4 *)(*(int *)(local_370 + 0xf8) + 0x5f0);
      *(undefined4 *)(*(int *)(local_370 + 0x230) + 0xd0) = 0;
      *(undefined4 *)(*(int *)(local_370 + 0x230) + 0xc4) = 0;
      *(undefined4 *)(*(int *)(local_370 + 0x230) + 0xcc) = 0;
      *(undefined4 *)(*(int *)(local_370 + 0x230) + 200) = 0;
      if (*(int *)(local_370 + 0x310) != 0) {
        FUN_004e2e20();
        uVar3 = FUN_00462380();
        *(undefined4 *)(local_370 + 0x30c) = uVar3;
      }
    }
    FUN_004ebfd0();
    break;
  case 1:
    *(float *)(local_370 + 0x318) = *(float *)(local_370 + 0x318) - param_2;
    if (*(float *)(local_370 + 0x318) <= 0.0) {
      *(undefined4 *)(local_370 + 0x228) = 2;
      FUN_0062a270();
      if (*(int *)(local_370 + 0x30c) == 0) {
        if (*(char *)(local_370 + 0x308) != '\0') {
          *(undefined4 *)(*(int *)(local_370 + 0x230) + 0xe0) = 1;
        }
      }
      else {
        FUN_004e2d90();
        FUN_00468a70();
        FUN_00444ef0();
      }
    }
    fVar7 = (float10)FUN_004e9610();
    local_3a8 = (float)fVar7;
    local_3c0 = *(float *)(*(int *)(local_370 + 0xf8) + 0x35c) * local_3a8;
    local_398 = *(float *)(*(int *)(local_370 + 0xf8) + 0x360) * local_3a8;
    local_418 = *(float *)(*(int *)(local_370 + 0xf8) + 0x338) * local_3a8;
    local_378 = (undefined4 *)(*(int *)(local_370 + 0xf4) + 0x20);
    *(undefined4 *)(local_370 + 0x144) = 0;
    *(undefined4 *)(local_370 + 0x148) = 0xc11ccccd;
    *(undefined4 *)(local_370 + 0x14c) = 0;
    puVar4 = (undefined4 *)FUN_00447f60();
    local_11c = *puVar4;
    local_118 = puVar4[1];
    local_114 = puVar4[2];
    local_110 = puVar4[3];
    local_10c = puVar4[4];
    local_108 = puVar4[5];
    FUN_00444f70(*(undefined4 *)(local_370 + 0xf0),local_11c,local_118,local_114,local_110,local_10c
                 ,local_108);
    local_39c = (float)(*(double *)(local_378 + 0xc) - (double)local_39c);
    local_38c = 9.8 - local_368 * 19.6 * local_39c;
    local_3f0 = -6.86;
    fVar7 = (float10)FUN_004428b0();
    local_3f8 = (float)fVar7;
    local_400 = local_3f0 * local_3f8;
    local_38c = local_38c + local_400;
    if (0.0 < local_38c) {
      puVar4 = (undefined4 *)
               FUN_00439d00(local_450,*(undefined4 *)(local_370 + 0x144),
                            *(undefined4 *)(local_370 + 0x148),*(undefined4 *)(local_370 + 0x14c),
                            local_38c);
      local_5c = *puVar4;
      local_58 = puVar4[1];
      local_54 = puVar4[2];
      *(undefined4 *)(local_370 + 0x144) = local_5c;
      *(undefined4 *)(local_370 + 0x148) = local_58;
      *(undefined4 *)(local_370 + 0x14c) = local_54;
    }
    pfVar5 = (float *)FUN_00439d00(local_42c,*(undefined4 *)(local_370 + 300),
                                   *(undefined4 *)(local_370 + 0x130),
                                   *(undefined4 *)(local_370 + 0x134),param_2);
    local_354 = *pfVar5;
    local_28 = pfVar5[1];
    local_34c = pfVar5[2];
    local_350 = local_28 * 0.1;
    local_3bc = local_354 * local_354 + local_350 * local_350 + local_34c * local_34c;
    local_2c = local_354;
    local_24 = local_34c;
    if (0.0 < local_3bc) {
      fVar7 = (float10)FUN_00820570();
      local_410 = (float)fVar7;
      local_408 = local_410;
      fVar7 = (float10)FUN_0047b6f0();
      local_420 = (float)fVar7;
      puVar4 = (undefined4 *)
               FUN_00439d00(local_48c,*(undefined4 *)(local_370 + 0x144),
                            *(undefined4 *)(local_370 + 0x148),*(undefined4 *)(local_370 + 0x14c),
                            -local_420);
      local_38 = *puVar4;
      local_34 = puVar4[1];
      local_30 = puVar4[2];
      *(undefined4 *)(local_370 + 0x144) = local_38;
      *(undefined4 *)(local_370 + 0x148) = local_34;
      *(undefined4 *)(local_370 + 0x14c) = local_30;
    }
    *(float *)(local_370 + 0x150) = -local_398 * *(float *)(local_370 + 0x138);
    *(float *)(local_370 + 0x154) = -local_398 * *(float *)(local_370 + 0x13c);
    *(float *)(local_370 + 0x158) = -local_398 * *(float *)(local_370 + 0x140);
    fVar7 = (float10)FUN_004428b0();
    local_404 = (float)fVar7;
    *(float *)(local_370 + 0x150) = *(float *)(local_370 + 0x150) - local_404 * local_3c0;
    fVar7 = (float10)FUN_004428b0();
    local_3f4 = (float)fVar7;
    *(float *)(local_370 + 0x158) = local_3f4 * local_3c0 + *(float *)(local_370 + 0x158);
    puVar4 = (undefined4 *)
             FUN_00439d00(local_468,*(undefined4 *)(local_370 + 300),
                          *(undefined4 *)(local_370 + 0x130),*(undefined4 *)(local_370 + 0x134),
                          param_2 * 0.5);
    local_68 = *puVar4;
    local_64 = puVar4[1];
    local_60 = puVar4[2];
    *(undefined4 *)(local_370 + 300) = local_68;
    *(undefined4 *)(local_370 + 0x130) = local_64;
    *(undefined4 *)(local_370 + 0x134) = local_60;
    *(double *)(local_378 + 10) =
         (double)(*(float *)(local_370 + 300) * param_2) + *(double *)(local_378 + 10);
    *(double *)(local_378 + 0xc) =
         (double)(*(float *)(local_370 + 0x130) * param_2) + *(double *)(local_378 + 0xc);
    *(double *)(local_378 + 0xe) =
         (double)(*(float *)(local_370 + 0x134) * param_2) + *(double *)(local_378 + 0xe);
    puVar4 = (undefined4 *)
             FUN_00439d00(local_4a4,*(undefined4 *)(local_370 + 300),
                          *(undefined4 *)(local_370 + 0x130),*(undefined4 *)(local_370 + 0x134),
                          param_2 * 0.5);
    local_d4 = *puVar4;
    local_d0 = puVar4[1];
    local_cc = puVar4[2];
    *(undefined4 *)(local_370 + 300) = local_d4;
    *(undefined4 *)(local_370 + 0x130) = local_d0;
    *(undefined4 *)(local_370 + 0x134) = local_cc;
    fVar7 = (float10)FUN_0045c420();
    *(float *)(local_370 + 0x11c) = (float)fVar7;
    puVar4 = (undefined4 *)
             FUN_00439d00(local_498,*(undefined4 *)(local_370 + 0x138),
                          *(undefined4 *)(local_370 + 0x13c),*(undefined4 *)(local_370 + 0x140),
                          param_2 * 0.5);
    local_98 = *puVar4;
    local_94 = puVar4[1];
    local_90 = puVar4[2];
    *(undefined4 *)(local_370 + 0x138) = local_98;
    *(undefined4 *)(local_370 + 0x13c) = local_94;
    *(undefined4 *)(local_370 + 0x140) = local_90;
    puVar4 = (undefined4 *)FUN_00444d50(local_61c,local_378,*(undefined4 *)(local_370 + 0x138));
    puVar6 = local_1fc;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar4 = local_1fc;
    puVar6 = local_378;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar4 = (undefined4 *)
             FUN_00439d00(local_4c8,*(undefined4 *)(local_370 + 0x138),
                          *(undefined4 *)(local_370 + 0x13c),*(undefined4 *)(local_370 + 0x140),
                          param_2 * 0.5);
    local_f8 = *puVar4;
    local_f4 = puVar4[1];
    local_f0 = puVar4[2];
    *(undefined4 *)(local_370 + 0x138) = local_f8;
    *(undefined4 *)(local_370 + 0x13c) = local_f4;
    *(undefined4 *)(local_370 + 0x140) = local_f0;
    *(undefined4 *)(local_370 + 0x2b4) = 0xbf000000;
    FUN_004eea20();
    FUN_004ab380();
    break;
  case 2:
    if ((*(int *)(*(int *)(local_370 + 0x230) + 0xe0) != 0) && ((char)local_3c4 == '\0')) {
      *(undefined4 *)(local_370 + 0x228) = 3;
      *(undefined4 *)(*(int *)(local_370 + 0x230) + 0xe0) = 0;
      FUN_004376c0();
      if (-1 < *(int *)(local_370 + 0x314)) {
        FUN_0062a5d0();
        *(undefined4 *)(local_370 + 0x314) = 0xffffffff;
      }
      FUN_0062a270();
      *(undefined4 *)(local_370 + 0x318) = *(undefined4 *)(*(int *)(local_370 + 0xf8) + 0x5f4);
      if (*(int *)(local_370 + 0x30c) != 0) {
        if (*(int *)(local_370 + 0x310) != 0) {
          FUN_004e2ce0();
        }
        FUN_00468a70();
        FUN_00444f20();
      }
    }
    local_380 = (undefined4 *)(*(int *)(local_370 + 0xf4) + 0x20);
    puVar4 = (undefined4 *)FUN_004560b0();
    local_128 = *puVar4;
    local_124 = puVar4[1];
    local_120 = puVar4[2];
    local_b0 = local_128;
    local_ac = local_124;
    local_a8 = local_120;
    puVar4 = (undefined4 *)FUN_00447f60();
    local_ec = *puVar4;
    local_e8 = puVar4[1];
    local_e4 = puVar4[2];
    local_e0 = puVar4[3];
    local_dc = puVar4[4];
    local_d8 = puVar4[5];
    local_20 = local_ec;
    uStack_1c = local_e8;
    local_18 = local_e4;
    local_14 = local_e0;
    local_10 = local_dc;
    uStack_c = local_d8;
    FUN_00444f70(*(undefined4 *)(local_370 + 0xf0),local_ec,local_e8,local_e4,local_e0,local_dc,
                 local_d8);
    puVar4 = (undefined4 *)FUN_0081f920();
    puVar6 = local_23c;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar4 = local_23c;
    puVar6 = local_380;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar6 = puVar6 + 1;
    }
    *(ulonglong *)(local_380 + 10) = CONCAT44(uStack_1c,local_20);
    *(double *)(local_380 + 0xc) = (double)local_41c;
    *(ulonglong *)(local_380 + 0xe) = CONCAT44(uStack_c,local_10);
    *(undefined4 *)(local_370 + 0x11c) = 0;
    *(undefined4 *)(local_370 + 0x134) = 0;
    *(undefined4 *)(local_370 + 0x130) = 0;
    *(undefined4 *)(local_370 + 300) = 0;
    *(undefined4 *)(local_370 + 0x140) = 0;
    *(undefined4 *)(local_370 + 0x13c) = 0;
    *(undefined4 *)(local_370 + 0x138) = 0;
    cVar1 = FUN_004b9830();
    if ((cVar1 == '\0') && (*(int *)(local_370 + 0x310) != 0)) {
      fVar7 = (float10)FUN_00822da0();
      local_3b4 = (float)fVar7;
      if (*(float *)(local_370 + 0x31c) <= local_3b4 && local_3b4 != *(float *)(local_370 + 0x31c))
      {
        (**(code **)(*(int *)(local_370 + 0x18) + 0x28))();
        *(float *)(local_370 + 0x31c) = local_3b4 + *(float *)(*(int *)(local_370 + 0xf8) + 0x5f8);
      }
    }
    cVar1 = FUN_004723d0();
    if (cVar1 != '\0') {
      FUN_005aee30();
    }
    FUN_004ab380();
    break;
  case 3:
    *(float *)(local_370 + 0x318) = *(float *)(local_370 + 0x318) - param_2;
    if ((*(float *)(local_370 + 0x318) <= 0.0) &&
       (*(undefined4 *)(local_370 + 0x228) = 0, *(int *)(local_370 + 0x30c) != 0)) {
      FUN_004e2e40();
      *(undefined4 *)(local_370 + 0x30c) = 0;
    }
    fVar7 = (float10)FUN_004e9610();
    local_3a4 = (float)fVar7;
    local_3c8 = *(float *)(*(int *)(local_370 + 0xf8) + 0x35c) * local_3a4;
    local_3a0 = *(float *)(*(int *)(local_370 + 0xf8) + 0x360) * local_3a4;
    local_3ec = *(float *)(*(int *)(local_370 + 0xf8) + 0x338) * local_3a4;
    local_374 = (undefined4 *)(*(int *)(local_370 + 0xf4) + 0x20);
    *(undefined4 *)(local_370 + 0x144) = 0;
    *(undefined4 *)(local_370 + 0x148) = 0xc11ccccd;
    *(undefined4 *)(local_370 + 0x14c) = 0;
    puVar4 = (undefined4 *)FUN_00447f60();
    local_80 = *puVar4;
    local_7c = puVar4[1];
    local_78 = puVar4[2];
    local_74 = puVar4[3];
    local_70 = puVar4[4];
    local_6c = puVar4[5];
    FUN_00444f70(*(undefined4 *)(local_370 + 0xf0),local_80,local_7c,local_78,local_74,local_70,
                 local_6c);
    local_3ac = (float)((*(double *)(local_374 + 0xc) - (double)local_3ac) -
                       (double)*(float *)(*(int *)(local_370 + 0xf8) + 0x34c));
    local_390 = 9.8 - local_35c * 19.6 * local_3ac;
    local_3dc = -6.86;
    fVar7 = (float10)FUN_004428b0();
    local_3e4 = (float)fVar7;
    local_3fc = local_3dc * local_3e4;
    local_390 = local_390 + local_3fc;
    if (0.0 < local_390) {
      puVar4 = (undefined4 *)
               FUN_00439d00(local_444,*(undefined4 *)(local_370 + 0x144),
                            *(undefined4 *)(local_370 + 0x148),*(undefined4 *)(local_370 + 0x14c),
                            local_390);
      local_104 = *puVar4;
      local_100 = puVar4[1];
      local_fc = puVar4[2];
      *(undefined4 *)(local_370 + 0x144) = local_104;
      *(undefined4 *)(local_370 + 0x148) = local_100;
      *(undefined4 *)(local_370 + 0x14c) = local_fc;
    }
    pfVar5 = (float *)FUN_00439d00(local_45c,*(undefined4 *)(local_370 + 300),
                                   *(undefined4 *)(local_370 + 0x130),
                                   *(undefined4 *)(local_370 + 0x134),param_2);
    local_348 = *pfVar5;
    local_c4 = pfVar5[1];
    local_340 = pfVar5[2];
    local_344 = local_c4 * 0.1;
    local_3b8 = local_348 * local_348 + local_344 * local_344 + local_340 * local_340;
    local_c8 = local_348;
    local_c0 = local_340;
    if (0.0 < local_3b8) {
      fVar7 = (float10)FUN_00820570();
      local_3e0 = (float)fVar7;
      local_3d8 = local_3e0;
      fVar7 = (float10)FUN_0047b6f0();
      local_3d4 = (float)fVar7;
      puVar4 = (undefined4 *)
               FUN_00439d00(local_474,*(undefined4 *)(local_370 + 0x144),
                            *(undefined4 *)(local_370 + 0x148),*(undefined4 *)(local_370 + 0x14c),
                            -local_3d4);
      local_50 = *puVar4;
      local_4c = puVar4[1];
      local_48 = puVar4[2];
      *(undefined4 *)(local_370 + 0x144) = local_50;
      *(undefined4 *)(local_370 + 0x148) = local_4c;
      *(undefined4 *)(local_370 + 0x14c) = local_48;
    }
    *(float *)(local_370 + 0x150) = -local_3a0 * *(float *)(local_370 + 0x138);
    *(float *)(local_370 + 0x154) = -local_3a0 * *(float *)(local_370 + 0x13c);
    *(float *)(local_370 + 0x158) = -local_3a0 * *(float *)(local_370 + 0x140);
    fVar7 = (float10)FUN_004428b0();
    local_414 = (float)fVar7;
    *(float *)(local_370 + 0x150) = *(float *)(local_370 + 0x150) - local_414 * local_3c8;
    fVar7 = (float10)FUN_004428b0();
    local_40c = (float)fVar7;
    *(float *)(local_370 + 0x158) = local_40c * local_3c8 + *(float *)(local_370 + 0x158);
    puVar4 = (undefined4 *)
             FUN_00439d00(local_4bc,*(undefined4 *)(local_370 + 300),
                          *(undefined4 *)(local_370 + 0x130),*(undefined4 *)(local_370 + 0x134),
                          param_2 * 0.5);
    local_8c = *puVar4;
    local_88 = puVar4[1];
    local_84 = puVar4[2];
    *(undefined4 *)(local_370 + 300) = local_8c;
    *(undefined4 *)(local_370 + 0x130) = local_88;
    *(undefined4 *)(local_370 + 0x134) = local_84;
    *(double *)(local_374 + 10) =
         (double)(*(float *)(local_370 + 300) * param_2) + *(double *)(local_374 + 10);
    *(double *)(local_374 + 0xc) =
         (double)(*(float *)(local_370 + 0x130) * param_2) + *(double *)(local_374 + 0xc);
    *(double *)(local_374 + 0xe) =
         (double)(*(float *)(local_370 + 0x134) * param_2) + *(double *)(local_374 + 0xe);
    puVar4 = (undefined4 *)
             FUN_00439d00(local_4d4,*(undefined4 *)(local_370 + 300),
                          *(undefined4 *)(local_370 + 0x130),*(undefined4 *)(local_370 + 0x134),
                          param_2 * 0.5);
    local_44 = *puVar4;
    local_40 = puVar4[1];
    local_3c = puVar4[2];
    *(undefined4 *)(local_370 + 300) = local_44;
    *(undefined4 *)(local_370 + 0x130) = local_40;
    *(undefined4 *)(local_370 + 0x134) = local_3c;
    fVar7 = (float10)FUN_0045c420();
    *(float *)(local_370 + 0x11c) = (float)fVar7;
    puVar4 = (undefined4 *)
             FUN_00439d00(local_4b0,*(undefined4 *)(local_370 + 0x138),
                          *(undefined4 *)(local_370 + 0x13c),*(undefined4 *)(local_370 + 0x140),
                          param_2 * 0.5);
    local_a4 = *puVar4;
    local_a0 = puVar4[1];
    local_9c = puVar4[2];
    *(undefined4 *)(local_370 + 0x138) = local_a4;
    *(undefined4 *)(local_370 + 0x13c) = local_a0;
    *(undefined4 *)(local_370 + 0x140) = local_9c;
    puVar4 = (undefined4 *)FUN_00444d50(local_59c,local_374,*(undefined4 *)(local_370 + 0x138));
    puVar6 = local_27c;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar4 = local_27c;
    puVar6 = local_374;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar4 = (undefined4 *)
             FUN_00439d00(local_480,*(undefined4 *)(local_370 + 0x138),
                          *(undefined4 *)(local_370 + 0x13c),*(undefined4 *)(local_370 + 0x140),
                          param_2 * 0.5);
    local_bc = *puVar4;
    local_b8 = puVar4[1];
    local_b4 = puVar4[2];
    *(undefined4 *)(local_370 + 0x138) = local_bc;
    *(undefined4 *)(local_370 + 0x13c) = local_b8;
    *(undefined4 *)(local_370 + 0x140) = local_b4;
    *(undefined4 *)(local_370 + 0x2b4) = 0;
    FUN_004eea20();
    FUN_004ab380();
  }
  if (*(int *)(local_370 + 0x1a0) != 0) {
    if (*(int *)(local_370 + 0x228) == 2) {
      FUN_004d9950();
    }
    else {
      FUN_004d9950();
    }
  }
  if ((*(uint *)(*(int *)(local_370 + 0xf4) + 0x14) & 0x200) == 0) {
    local_3d0 = *(undefined4 *)(local_370 + 800);
    switch(local_3d0) {
    case 0:
      if ((*(int *)(local_370 + 0x228) != 2) || (*(int *)(local_370 + 0x300) == 0)) break;
      *(undefined4 *)(local_370 + 800) = 1;
    case 1:
      if (*(int *)(*(int *)(local_370 + 0xf8) + 0x62c) != 0) {
        for (local_388 = 0; local_388 < *(int *)(local_370 + 0x344); local_388 = local_388 + 1) {
          puVar4 = (undefined4 *)FUN_0062e070();
          puVar6 = local_2bc;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar6 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar6 = puVar6 + 1;
          }
          puVar4 = local_2bc;
          puVar6 = local_33c;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar6 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar6 = puVar6 + 1;
          }
          (**(code **)(**(int **)(*(int *)(local_370 + 0xf8) + 0x62c) + 8))();
        }
      }
      if (*(char *)(*(int *)(local_370 + 0xf8) + 0x630) != '\0') {
        FUN_0043a990();
        local_16c = 1;
        FUN_0043a9e0();
        local_144 = 1;
        FUN_0043aa30(*(int *)(local_370 + 0xf8) + 0x630);
      }
      *(undefined4 *)(local_370 + 800) = 2;
    case 2:
      if (*(int *)(*(int *)(local_370 + 0xf8) + 0x62c) != 0) {
        for (local_384 = 0; local_384 < *(int *)(local_370 + 0x344); local_384 = local_384 + 1) {
          puVar4 = (undefined4 *)FUN_0062e070();
          puVar6 = local_2fc;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar6 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar6 = puVar6 + 1;
          }
          puVar4 = local_2fc;
          puVar6 = local_1bc;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar6 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar6 = puVar6 + 1;
          }
          FUN_0044dca0();
        }
      }
      if (*(int *)(local_370 + 0x300) == 0) {
        *(undefined4 *)(local_370 + 800) = 3;
      }
      break;
    case 3:
      if ((*(char *)(*(int *)(local_370 + 0xf8) + 0x630) != '\0') &&
         (local_3cc = FUN_0043ac70(), local_3cc != 0)) {
        FUN_0043aaa0();
      }
      if (*(int *)(*(int *)(local_370 + 0xf8) + 0x62c) != 0) {
        for (local_394 = 0; local_394 < *(int *)(local_370 + 0x344); local_394 = local_394 + 1) {
          FUN_0044dc60();
        }
      }
      *(undefined4 *)(local_370 + 800) = 0;
    }
  }
  FUN_0083e885();
  return;
}

