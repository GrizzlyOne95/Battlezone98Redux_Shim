
void __thiscall FUN_004ea300(int param_1,float param_2)

{
  int iVar1;
  undefined4 *puVar2;
  float *pfVar3;
  double *pdVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined1 local_b04 [384];
  undefined1 local_984 [64];
  undefined1 local_944 [128];
  undefined1 local_8c4 [128];
  undefined1 local_844 [64];
  undefined1 local_804 [64];
  undefined1 local_7c4 [48];
  undefined1 local_794 [24];
  undefined1 local_77c [24];
  undefined1 local_764 [12];
  undefined1 local_758 [24];
  float local_740;
  float local_73c;
  float local_738;
  float local_734;
  float local_730;
  float local_72c;
  float local_728;
  float local_724;
  float local_720;
  float local_71c;
  float local_718;
  float local_714;
  float local_710;
  float local_70c;
  float local_708;
  float local_704;
  uint local_700;
  int local_6fc;
  float local_6f8;
  int local_6f4;
  float local_6f0;
  float local_6ec;
  float local_6e8;
  uint local_6e4;
  float local_6e0;
  float local_6dc;
  float local_6d8;
  float local_6d4;
  float local_6d0;
  float local_6cc;
  float local_6c8;
  float local_6c4;
  int local_6c0;
  int local_6bc;
  int local_6b8;
  int local_6b4;
  float local_6b0;
  int local_6ac;
  float local_6a8;
  undefined1 local_6a2;
  byte local_6a1;
  int local_6a0;
  int local_69c;
  undefined4 local_698;
  undefined4 local_694;
  undefined4 local_690;
  undefined4 local_68c;
  undefined4 local_688;
  undefined4 local_684;
  float local_680;
  undefined4 local_67c;
  float local_678;
  undefined4 local_674 [16];
  undefined4 local_634 [16];
  undefined4 local_5f4 [16];
  undefined4 local_5b4 [16];
  undefined4 local_574 [16];
  undefined4 local_534 [16];
  undefined4 local_4f4 [16];
  undefined4 local_4b4 [16];
  undefined4 local_474 [16];
  undefined4 local_434 [16];
  undefined4 local_3f4 [16];
  undefined4 local_3b4 [16];
  undefined4 local_374 [16];
  undefined4 local_334 [16];
  undefined4 local_2f4 [16];
  undefined4 local_2b4 [16];
  undefined4 local_274 [16];
  undefined4 local_234 [16];
  undefined4 local_1f4 [10];
  double local_1cc;
  double local_1c4;
  double local_1bc;
  undefined4 local_1b4 [16];
  undefined4 local_174 [10];
  double local_14c;
  double local_144;
  double local_13c;
  undefined1 local_134 [12];
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
  float local_ec;
  float local_e8;
  float local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  double local_a4;
  double local_9c;
  double local_94;
  undefined4 local_8c;
  undefined4 uStack_88;
  undefined4 local_84;
  undefined4 uStack_80;
  undefined4 local_7c;
  undefined4 uStack_78;
  float local_74;
  float local_70;
  float local_6c;
  int aiStack_68 [16];
  int aiStack_28 [8];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_6c4 = *(float *)(*(int *)(param_1 + 0x230) + 0xc4);
  local_6a2 = *(int *)(*(int *)(param_1 + 0x230) + 0xd4) != 0;
  local_6e4 = (uint)(byte)local_6a2;
  if ((bool)local_6a2) {
    local_6dc = 1.5;
  }
  else {
    local_6dc = *(float *)(*(int *)(param_1 + 0x230) + 0xd0);
  }
  local_6c8 = local_6dc;
  local_704 = *(float *)(*(int *)(param_1 + 0x230) + 0xcc);
  local_6a1 = *(int *)(*(int *)(param_1 + 0x230) + 0xd8) != 0;
  local_700 = (uint)local_6a1;
  local_70c = *(float *)(*(int *)(param_1 + 0xf8) + 0x374 + local_700 * 4);
  local_720 = *(float *)(*(int *)(param_1 + 0xf8) + 0x37c + local_700 * 4);
  local_708 = *(float *)(*(int *)(param_1 + 0xf8) + 900 + local_700 * 4);
  local_6ec = *(float *)(*(int *)(param_1 + 0xf8) + 0x38c + local_700 * 4);
  local_6f8 = *(float *)(*(int *)(param_1 + 0xf8) + 0x394 + local_700 * 4);
  local_6bc = 0;
  local_6ac = 0;
  local_6a0 = *(int *)(param_1 + 0xf4);
  local_69c = param_1;
  do {
    while( true ) {
      local_6c0 = *(int *)(local_6a0 + 0x84) + -0x42;
      switch(*(int *)(local_6a0 + 0x84)) {
      case 0x42:
        local_71c = -*(float *)(local_6a0 + 0x24) - local_70c * local_704;
        puVar2 = (undefined4 *)FUN_0081ecd0(local_8c4,local_71c * 3.0 * param_2);
        puVar5 = local_3b4;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar5 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar5 = puVar5 + 1;
        }
        puVar2 = local_3b4;
        puVar5 = local_234;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar5 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar5 = puVar5 + 1;
        }
        puVar2 = (undefined4 *)FUN_0081fe60();
        puVar5 = local_434;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar5 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar5 = puVar5 + 1;
        }
        puVar2 = local_434;
        puVar5 = (undefined4 *)(local_6a0 + 0x20);
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar5 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar5 = puVar5 + 1;
        }
        FUN_00681a00(local_6a0,local_6a0 + 0x20);
        break;
      case 0x43:
        if (0.0 < *(double *)(local_6a0 + 0x48) || *(double *)(local_6a0 + 0x48) == 0.0) {
          fVar6 = (float10)FUN_0046e0a0(*(undefined4 *)(local_6a0 + 0x3c),
                                        *(undefined4 *)(local_6a0 + 0x40));
          local_734 = (float)fVar6;
          local_710 = local_734 + local_708 + local_6ec * local_6c8 + local_6f8 * local_6c4;
          puVar2 = (undefined4 *)FUN_0081ec40(local_944,local_710 * 3.0 * param_2);
          puVar5 = local_2b4;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar2 = local_2b4;
          puVar5 = local_2f4;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar2 = (undefined4 *)FUN_0081fe60();
          puVar5 = local_374;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar2 = local_374;
          puVar5 = (undefined4 *)(local_6a0 + 0x20);
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar5 = puVar5 + 1;
          }
          FUN_00681a00(local_6a0,local_6a0 + 0x20);
        }
        else {
          fVar6 = (float10)FUN_0046e0a0(*(undefined4 *)(local_6a0 + 0x3c),
                                        *(undefined4 *)(local_6a0 + 0x40));
          local_73c = (float)fVar6;
          local_724 = (local_73c + local_708 + local_6ec * local_6c8) - local_6f8 * local_6c4;
          puVar2 = (undefined4 *)FUN_0081ec40(local_804,local_724 * 3.0 * param_2);
          puVar5 = local_634;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar2 = local_634;
          puVar5 = local_4b4;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar2 = (undefined4 *)FUN_0081fe60();
          puVar5 = local_274;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar2 = local_274;
          puVar5 = (undefined4 *)(local_6a0 + 0x20);
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar5 = puVar5 + 1;
          }
          FUN_00681a00(local_6a0,local_6a0 + 0x20);
        }
        break;
      case 0x44:
        local_728 = -*(float *)(local_6a0 + 0x24) - local_720 * local_6c4;
        puVar2 = (undefined4 *)FUN_0081ecd0(local_844,local_728 * 3.0 * param_2);
        puVar5 = local_3f4;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar5 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar5 = puVar5 + 1;
        }
        puVar2 = local_3f4;
        puVar5 = local_474;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar5 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar5 = puVar5 + 1;
        }
        puVar2 = (undefined4 *)FUN_0081fe60();
        puVar5 = local_4f4;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar5 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar5 = puVar5 + 1;
        }
        puVar2 = local_4f4;
        puVar5 = (undefined4 *)(local_6a0 + 0x20);
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar5 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar5 = puVar5 + 1;
        }
        FUN_00681a00(local_6a0,local_6a0 + 0x20);
        break;
      case 0x4b:
        aiStack_68[local_6bc] = local_6a0;
        local_6bc = local_6bc + 1;
        break;
      case 0x4d:
        aiStack_28[local_6ac] = local_6a0;
        local_6ac = local_6ac + 1;
      }
      if (*(int *)(local_6a0 + 0x80) == 0) break;
      local_6a0 = *(int *)(local_6a0 + 0x80);
    }
    do {
      if (*(int *)(local_6a0 + 0x7c) != 0) break;
      local_6a0 = *(int *)(local_6a0 + 0x78);
    } while (local_6a0 != 0);
    if (local_6a0 == 0) {
      if (((0.1 < *(float *)(local_69c + 0x2b4)) &&
          ((*(uint *)(*(int *)(local_69c + 0xf4) + 0x14) & 0x200) == 0)) &&
         (iVar1 = FUN_00451de0(), iVar1 == 0)) {
        if (*(float *)(*(int *)(local_69c + 0xf4) + 0xd0) <= 0.999) {
          for (local_6b4 = 0; local_6b4 < local_6bc; local_6b4 = local_6b4 + 1) {
            local_6fc = aiStack_68[local_6b4];
            puVar2 = (undefined4 *)FUN_0062e070();
            puVar5 = local_574;
            for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
              *puVar5 = *puVar2;
              puVar2 = puVar2 + 1;
              puVar5 = puVar5 + 1;
            }
            puVar2 = local_574;
            puVar5 = local_1b4;
            for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
              *puVar5 = *puVar2;
              puVar2 = puVar2 + 1;
              puVar5 = puVar5 + 1;
            }
            local_6f4 = FUN_00618b60(local_6fc);
            if ((local_6f4 == 0) || (*(int *)(local_6f4 + 0x84) != 0x43)) {
              if (*(int *)(*(int *)(local_69c + 0x230) + 0xd4) == 0) {
                local_6d0 = 0.0;
              }
              else {
                local_6d0 = 0.2;
              }
              local_6a8 = local_6d0;
            }
            else {
              puVar2 = (undefined4 *)FUN_004560b0(local_764,local_1b4);
              local_104 = *puVar2;
              local_100 = puVar2[1];
              local_fc = puVar2[2];
              puVar2 = (undefined4 *)
                       FUN_00440000(local_758,local_704 * -1.0,(float)local_6a1 * -2.0,
                                    local_6c8 * -1.5);
              local_11c = *puVar2;
              local_118 = puVar2[1];
              local_114 = puVar2[2];
              puVar2 = (undefined4 *)FUN_00440210();
              local_128 = *puVar2;
              local_124 = puVar2[1];
              local_120 = puVar2[2];
              local_730 = *(float *)(local_69c + 0x2b4) * 0.2;
              FUN_004428b0(&local_128,&local_104,0,0x3f800000);
              fVar6 = (float10)FUN_00447ed0();
              local_738 = (float)fVar6;
              local_6a8 = local_730 * local_738;
            }
            if (0.0001 <= local_6a8) {
              fVar6 = (float10)FUN_004588c0(0x40c90fdb);
              puVar2 = (undefined4 *)FUN_0081ecd0(local_984,(float)fVar6);
              puVar5 = local_5f4;
              for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
                *puVar5 = *puVar2;
                puVar2 = puVar2 + 1;
                puVar5 = puVar5 + 1;
              }
              puVar2 = local_5f4;
              puVar5 = local_674;
              for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
                *puVar5 = *puVar2;
                puVar2 = puVar2 + 1;
                puVar5 = puVar5 + 1;
              }
              puVar2 = (undefined4 *)FUN_0081fe60();
              puVar5 = local_334;
              for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
                *puVar5 = *puVar2;
                puVar2 = puVar2 + 1;
                puVar5 = puVar5 + 1;
              }
              puVar2 = local_334;
              puVar5 = local_1b4;
              for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
                *puVar5 = *puVar2;
                puVar2 = puVar2 + 1;
                puVar5 = puVar5 + 1;
              }
              local_740 = local_6a8 * 0.1;
              fVar6 = (float10)FUN_004464c0();
              local_72c = (float)fVar6;
              FUN_004c8800(local_1b4,local_740 * local_72c + local_6a8);
              if (DAT_009b5104 != 0) {
                puVar2 = (undefined4 *)FUN_00447f60(local_7c4,local_1b4);
                local_c8 = *puVar2;
                local_c4 = puVar2[1];
                local_c0 = puVar2[2];
                local_bc = puVar2[3];
                local_b8 = puVar2[4];
                local_b4 = puVar2[5];
                local_8c = local_c8;
                uStack_88 = local_c4;
                local_84 = local_c0;
                uStack_80 = local_bc;
                local_7c = local_b8;
                uStack_78 = local_b4;
                puVar2 = (undefined4 *)FUN_004560b0(local_77c,local_1b4);
                local_68c = *puVar2;
                local_688 = puVar2[1];
                local_684 = puVar2[2];
                pfVar3 = (float *)FUN_004462d0();
                local_ec = *pfVar3;
                local_e8 = pfVar3[1];
                local_e4 = pfVar3[2];
                local_6b0 = 1.0;
                local_74 = local_ec;
                local_70 = local_e8;
                local_6c = local_e4;
                iVar1 = FUN_00784620(local_8c,uStack_88,local_84,uStack_80,local_7c,uStack_78,
                                     local_ec,local_e8,local_e4,&local_6b0,local_134);
                if (iVar1 != 0) {
                  puVar2 = (undefined4 *)FUN_0081f920();
                  puVar5 = local_534;
                  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
                    *puVar5 = *puVar2;
                    puVar2 = puVar2 + 1;
                    puVar5 = puVar5 + 1;
                  }
                  puVar2 = local_534;
                  puVar5 = local_1f4;
                  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
                    *puVar5 = *puVar2;
                    puVar2 = puVar2 + 1;
                    puVar5 = puVar5 + 1;
                  }
                  local_1cc = (double)(local_6b0 * local_74) + (double)CONCAT44(uStack_88,local_8c);
                  local_1c4 = (double)(local_6b0 * local_70) + (double)CONCAT44(uStack_80,local_84);
                  local_1bc = (double)(local_6b0 * local_6c) + (double)CONCAT44(uStack_78,local_7c);
                  FUN_004c8800(local_1f4,local_6b0);
                }
              }
            }
          }
        }
        if ((0 < local_6ac) &&
           (*(float *)(local_69c + 0x2b8) <= 0.8 && *(float *)(local_69c + 0x2b8) != 0.8)) {
          local_6e8 = *(float *)(local_69c + 0x2b8) * 1.25;
          local_6cc = (1.0 - local_6e8) * *(float *)(local_69c + 0x2b4);
          *(float *)(local_69c + 0x2ac) = param_2 * local_6cc + *(float *)(local_69c + 0x2ac);
          while (0.0 < *(float *)(local_69c + 0x2ac)) {
            puVar2 = (undefined4 *)
                     FUN_00444d50(local_b04,*(int *)(local_69c + 0xf4) + 0x20,
                                  *(undefined4 *)(local_69c + 0x138),
                                  *(undefined4 *)(local_69c + 0x13c),
                                  *(undefined4 *)(local_69c + 0x140),
                                  *(uint *)(local_69c + 0x2ac) ^ 0x80000000);
            puVar5 = local_5b4;
            for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
              *puVar5 = *puVar2;
              puVar2 = puVar2 + 1;
              puVar5 = puVar5 + 1;
            }
            puVar2 = local_5b4;
            puVar5 = local_174;
            for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
              *puVar5 = *puVar2;
              puVar2 = puVar2 + 1;
              puVar5 = puVar5 + 1;
            }
            local_14c = local_14c -
                        (double)(*(float *)(local_69c + 300) * *(float *)(local_69c + 0x2ac));
            local_144 = local_144 -
                        (double)(*(float *)(local_69c + 0x130) * *(float *)(local_69c + 0x2ac));
            local_13c = local_13c -
                        (double)(*(float *)(local_69c + 0x134) * *(float *)(local_69c + 0x2ac));
            for (local_6b8 = 0; local_6b8 < local_6ac; local_6b8 = local_6b8 + 1) {
              puVar2 = (undefined4 *)FUN_0062e1b0();
              local_110 = *puVar2;
              local_10c = puVar2[1];
              local_108 = puVar2[2];
              local_f8 = local_110;
              local_f4 = local_10c;
              local_f0 = local_108;
              pdVar4 = (double *)FUN_0081fd40();
              local_e0 = *(undefined4 *)pdVar4;
              local_dc = *(undefined4 *)((int)pdVar4 + 4);
              local_a4 = *pdVar4;
              local_d8 = *(undefined4 *)(pdVar4 + 1);
              local_d4 = *(undefined4 *)((int)pdVar4 + 0xc);
              local_9c = pdVar4[1];
              local_d0 = *(undefined4 *)(pdVar4 + 2);
              local_cc = *(undefined4 *)((int)pdVar4 + 0x14);
              local_94 = pdVar4[2];
              fVar6 = (float10)FUN_004464c0();
              local_6d4 = (float)fVar6;
              fVar6 = (float10)FUN_004464c0();
              local_6e0 = (float)fVar6;
              local_6f0 = local_6e8 * 3.0 + 2.0;
              local_a4 = (double)(local_6f0 * local_6d4) + local_a4;
              local_94 = (double)(local_6f0 * local_6e0) + local_94;
              FUN_00785730(local_a4,local_94,&local_714,&local_698);
              local_9c = (double)local_714;
              local_6d8 = local_6cc * 2.0 * local_6cc;
              local_680 = *(float *)(local_69c + 300) * 0.25 + local_6d8 * local_6d4;
              local_67c = 0;
              local_678 = *(float *)(local_69c + 0x134) * 0.25 + local_6d8 * local_6e0;
              uVar8 = local_694;
              uVar9 = local_690;
              uVar7 = local_698;
              fVar6 = (float10)FUN_004428b0();
              local_718 = (float)fVar6;
              puVar2 = (undefined4 *)
                       FUN_00439d00(local_794,local_680,local_67c,local_678,-local_718,uVar7,uVar8,
                                    uVar9);
              local_680 = (float)*puVar2;
              local_67c = puVar2[1];
              local_678 = (float)puVar2[2];
              local_b0 = local_680;
              local_ac = local_67c;
              local_a8 = local_678;
              FUN_004c0930();
            }
            *(float *)(local_69c + 0x2ac) = *(float *)(local_69c + 0x2ac) - 0.04;
          }
        }
      }
      FUN_0083e885();
      return;
    }
    local_6a0 = *(int *)(local_6a0 + 0x7c);
  } while( true );
}

