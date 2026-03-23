
void __thiscall FUN_004aa630(int *param_1,int param_2)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  undefined1 local_188 [12];
  undefined1 local_17c [24];
  undefined1 local_164 [48];
  undefined1 local_134 [12];
  undefined1 local_128 [12];
  float local_11c;
  int local_118;
  float local_114;
  uint local_110;
  int local_10c;
  float local_108;
  int local_104;
  float local_100;
  int *local_fc;
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
  undefined4 local_c8;
  undefined4 local_c4;
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
  int local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_fc = param_1;
  if ((param_2 != 0) && ((*(uint *)(DAT_0094672c + 0x30) & 1) == 0)) {
    FUN_004dc130();
    FUN_004dc2f0();
    fVar6 = (float10)FUN_0047e990();
    local_100 = (float)fVar6;
    if (0.0 < local_100) {
      if (local_fc + -6 == DAT_00917afc) {
        FUN_0049b430(local_100 * 0.002,0x40a00000);
      }
      local_104 = *(int *)(param_2 + 4);
      if ((local_104 != 0) &&
         ((*(int *)(local_104 + 0x84) == 0x33 || (*(int *)(local_104 + 0x84) == 0x34)))) {
        fVar6 = (float10)FUN_00447ed0();
        local_108 = (float)fVar6;
        puVar2 = (undefined4 *)FUN_00439de0();
        local_f8 = *puVar2;
        local_f4 = puVar2[1];
        local_f0 = puVar2[2];
        puVar2 = (undefined4 *)(**(code **)(*local_fc + 0xc))();
        puVar2 = (undefined4 *)FUN_004401a0(local_17c,*puVar2,puVar2[1],puVar2[2]);
        local_44 = *puVar2;
        local_40 = puVar2[1];
        local_3c = puVar2[2];
        local_14 = local_44;
        local_10 = local_40;
        local_c = local_3c;
        if (*(int *)(local_104 + 0x84) == 0x33) {
          if (local_fc[0x84] != 2) {
            puVar2 = (undefined4 *)FUN_004560b0();
            local_d4 = *puVar2;
            local_d0 = puVar2[1];
            local_cc = puVar2[2];
            local_68 = local_d4;
            local_64 = local_d0;
            local_60 = local_cc;
            puVar2 = (undefined4 *)FUN_004462d0(local_128,local_108 * 10.0);
            local_8c = *puVar2;
            local_88 = puVar2[1];
            local_84 = puVar2[2];
            FUN_004a75b0();
            if (*(float *)(local_fc[0x36] + 0x14) <= 5.0) {
              local_114 = local_108;
            }
            else {
              local_114 = (local_108 * 5.0) / *(float *)(local_fc[0x36] + 0x14);
            }
            local_11c = local_114;
            puVar2 = (undefined4 *)FUN_004440d0();
            local_c8 = *puVar2;
            local_c4 = puVar2[1];
            local_c0 = puVar2[2];
            local_5c = local_c8;
            local_58 = local_c4;
            local_54 = local_c0;
            puVar2 = (undefined4 *)FUN_00440300();
            local_c8 = *puVar2;
            local_c4 = puVar2[1];
            local_c0 = puVar2[2];
            local_2c = local_c8;
            local_28 = local_c4;
            local_24 = local_c0;
            piVar3 = (int *)FUN_00439d00(local_188,local_fc[0x48],local_fc[0x49],local_fc[0x4a],
                                         local_11c);
            local_20 = *piVar3;
            local_1c = piVar3[1];
            local_18 = piVar3[2];
            local_fc[0x48] = local_20;
            local_fc[0x49] = local_1c;
            local_fc[0x4a] = local_18;
          }
          local_118 = FUN_0047fed0();
          if (0 < local_118) {
            puVar2 = (undefined4 *)FUN_00447f60();
            local_bc = *puVar2;
            local_b8 = puVar2[1];
            local_b4 = puVar2[2];
            local_b0 = puVar2[3];
            local_ac = puVar2[4];
            local_a8 = puVar2[5];
            local_80 = local_bc;
            local_7c = local_b8;
            local_78 = local_b4;
            local_74 = local_b0;
            local_70 = local_ac;
            local_6c = local_a8;
            puVar2 = (undefined4 *)FUN_004621a0();
            local_e0 = *puVar2;
            local_dc = puVar2[1];
            local_d8 = puVar2[2];
            puVar2 = (undefined4 *)
                     FUN_00439d00(local_134,local_fc[0x45],local_fc[0x46],local_fc[0x47],0xc0a00000)
            ;
            local_98 = *puVar2;
            local_94 = puVar2[1];
            local_90 = puVar2[2];
            local_38 = local_98;
            local_34 = local_94;
            local_30 = local_90;
            for (local_10c = 0; local_10c < local_118; local_10c = local_10c + 1) {
              FUN_004927d0();
            }
          }
        }
        else if (local_fc[0x84] != 2) {
          puVar2 = (undefined4 *)FUN_004621a0();
          local_ec = *puVar2;
          local_e8 = puVar2[1];
          local_e4 = puVar2[2];
          local_50 = local_ec;
          local_4c = local_e8;
          local_48 = local_e4;
          puVar2 = (undefined4 *)FUN_004462d0(local_164,local_108 * 20.0);
          local_a4 = *puVar2;
          local_a0 = puVar2[1];
          local_9c = puVar2[2];
          FUN_004a75b0();
        }
      }
      cVar1 = FUN_004b9830();
      if (cVar1 == '\0') {
        cVar1 = FUN_004b9860();
        if ((cVar1 != '\0') && ((*(ushort *)(param_2 + 8) >> 5 & 1) != 0)) {
          local_100 = (local_100 * 7.0) / 6.0;
        }
        (**(code **)(*local_fc + 0x28))();
        if (((float)local_fc[0x7a] <= 0.0 && (float)local_fc[0x7a] != 0.0) &&
           ((*(uint *)(local_fc[0x37] + 0x14) & 0x200) == 0)) {
          *(uint *)(local_fc[0x37] + 0x14) = *(uint *)(local_fc[0x37] + 0x14) | 0x200;
          iVar4 = FUN_00572a70();
          if ((iVar4 != 0) && (iVar4 = (**(code **)(*local_fc + 4))(), iVar4 != 0)) {
            FUN_004b9ba0();
            local_110 = (uint)(local_fc + -6 == DAT_00917afc);
            uVar5 = (**(code **)(*local_fc + 4))();
            FUN_00626470(uVar5);
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

