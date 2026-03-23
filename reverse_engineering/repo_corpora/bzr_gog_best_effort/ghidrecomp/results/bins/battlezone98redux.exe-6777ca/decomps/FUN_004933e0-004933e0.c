
void __fastcall FUN_004933e0(int param_1)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  float *pfVar5;
  ushort *puVar6;
  float10 fVar7;
  undefined8 uVar8;
  undefined1 local_128 [12];
  undefined1 local_11c [12];
  undefined1 local_110 [24];
  uint local_f8;
  float local_f4;
  uint local_f0;
  undefined8 local_ec;
  float local_e4;
  float local_e0;
  undefined4 local_dc;
  int local_d8;
  int local_d4;
  int local_d0;
  float local_cc;
  float local_c8;
  int local_c4;
  float local_c0;
  int local_bc;
  float local_b8;
  undefined4 *local_b4;
  int local_b0;
  float local_ac;
  uint local_a8;
  uint local_a4;
  int local_a0;
  int local_9c;
  float local_98;
  float local_94;
  float local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  float local_80;
  float local_7c;
  float local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  float local_68;
  undefined4 local_64;
  float local_60;
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
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_02ceffe0 < 0x39) {
    if (DAT_02ceffe0 < 0x28) {
      *(undefined4 *)(param_1 + 0x20094) = 0;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x20094) = 200;
  }
  local_9c = param_1;
  iVar2 = FUN_00822e60();
  if (*(uint *)(local_9c + 0x20094) <= (uint)(iVar2 - *(int *)(local_9c + 0x20090))) {
    uVar3 = FUN_00822e60();
    *(undefined4 *)(local_9c + 0x20090) = uVar3;
    *(undefined4 *)(local_9c + 0x10) = **(undefined4 **)(local_9c + 8);
    *(float *)(local_9c + 0x14) = *(float *)(local_9c + 0x10) * *(float *)(local_9c + 0x10);
    uVar3 = (**(code **)(*(int *)(*(int *)(local_9c + 0xc) + 0x18) + 4))();
    *(undefined4 *)(local_9c + 0x1c) = uVar3;
    puVar4 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_9c + 0xc) + 0x18) + 0xc))();
    *(undefined4 *)(local_9c + 0x20) = *puVar4;
    *(undefined4 *)(local_9c + 0x24) = puVar4[1];
    *(undefined4 *)(local_9c + 0x28) = puVar4[2];
    uVar3 = FUN_00462610();
    *(undefined4 *)(local_9c + 0x2c) = uVar3;
    pfVar5 = (float *)FUN_00462490();
    local_14 = *pfVar5;
    local_10 = pfVar5[1];
    local_c = pfVar5[2];
    fVar7 = (float10)FUN_00820570();
    local_e0 = (float)fVar7;
    local_cc = local_14 * local_e0;
    local_c8 = local_c * local_e0;
    *(float *)(local_9c + 0x30) = local_c8;
    *(undefined4 *)(local_9c + 0x34) = 0;
    *(float *)(local_9c + 0x38) = -local_cc;
    *(float *)(local_9c + 0x3c) = DAT_0097829c * local_cc;
    *(float *)(local_9c + 0x40) = DAT_009581ec;
    *(float *)(local_9c + 0x44) = DAT_0097829c * local_c8;
    *(float *)(local_9c + 0x48) = DAT_009581ec * local_cc;
    *(float *)(local_9c + 0x4c) = -DAT_0097829c;
    *(float *)(local_9c + 0x50) = DAT_009581ec * local_c8;
    *(undefined8 *)(local_9c + 0x58) = 0;
    *(undefined8 *)(local_9c + 0x60) = 0;
    *(undefined8 *)(local_9c + 0x68) = 0;
    pfVar5 = (float *)(**(code **)(*(int *)(*(int *)(local_9c + 0xc) + 0x18) + 0xc))();
    fVar1 = DAT_02cc50e0;
    local_20 = *pfVar5;
    local_1c = pfVar5[1];
    local_18 = pfVar5[2];
    local_c0 = DAT_02cc50e4;
    local_b8 = DAT_02cc50e0;
    local_b0 = (int)(*(float *)(local_9c + 0x10) * DAT_02cc50e4);
    local_d0 = (int)(local_20 * DAT_02cc50e4);
    local_d4 = (int)(local_18 * DAT_02cc50e4);
    for (local_a0 = 2; local_a0 * 0x80 < local_b0 * 2 + local_a0; local_a0 = local_a0 << 1) {
    }
    local_a4 = local_d0 - local_b0 & ~(local_a0 - 1U);
    local_f8 = local_d0 + local_b0 & ~(local_a0 - 1U);
    local_a8 = local_d4 - local_b0 & ~(local_a0 - 1U);
    local_f0 = local_d4 + local_b0 & ~(local_a0 - 1U);
    *(int *)(local_9c + 0x20074) = (int)((local_f8 - local_a4) + local_a0) / local_a0;
    *(int *)(local_9c + 0x20078) = (int)((local_f0 - local_a8) + local_a0) / local_a0;
    *(uint *)(local_9c + 0x2007c) = local_a4;
    *(uint *)(local_9c + 0x20080) = local_a8;
    *(undefined4 *)(local_9c + 0x2008c) =
         *(undefined4 *)(&DAT_008e7844 + (int)*(float *)(local_9c + 0x70) * 0x10);
    local_ac = (float)local_a0 * fVar1;
    local_80 = local_ac * *(float *)(local_9c + 0x30);
    local_7c = local_ac * *(float *)(local_9c + 0x3c);
    local_78 = local_ac * *(float *)(local_9c + 0x48);
    local_8c = *(undefined4 *)(local_9c + 0x34);
    local_88 = *(undefined4 *)(local_9c + 0x40);
    local_84 = *(undefined4 *)(local_9c + 0x4c);
    local_98 = local_ac * *(float *)(local_9c + 0x38);
    local_94 = local_ac * *(float *)(local_9c + 0x44);
    local_90 = local_ac * *(float *)(local_9c + 0x50);
    local_68 = (float)(int)local_a4 * fVar1 - local_20;
    local_64 = 0;
    local_60 = (float)(int)local_a8 * fVar1 - local_18;
    puVar4 = (undefined4 *)FUN_00440300();
    local_68 = (float)*puVar4;
    local_64 = puVar4[1];
    local_60 = (float)puVar4[2];
    local_5c = local_68;
    local_58 = local_64;
    local_54 = local_60;
    memset((void *)(local_9c + 0x74),0,
           *(int *)(local_9c + 0x20074) * 8 * *(int *)(local_9c + 0x20078));
    local_b4 = (undefined4 *)(local_9c + 0x74);
    for (local_bc = *(int *)(local_9c + 0x20078); 0 < local_bc; local_bc = local_bc + -1) {
      local_74 = local_68;
      local_70 = local_64;
      local_6c = local_60;
      local_a4 = *(uint *)(local_9c + 0x2007c);
      for (local_c4 = *(int *)(local_9c + 0x20074); 0 < local_c4; local_c4 = local_c4 + -1) {
        puVar6 = (ushort *)FUN_00492d60();
        local_e4 = (float)(*puVar6 & 0xfff) * 0.1 - local_1c;
        puVar4 = (undefined4 *)FUN_00439d00(local_11c,local_74,local_70,local_6c,local_e4);
        local_50 = *puVar4;
        local_4c = puVar4[1];
        local_48 = puVar4[2];
        local_2c = local_50;
        local_28 = local_4c;
        local_24 = local_48;
        fVar7 = (float10)FUN_004428b0();
        local_f4 = (float)fVar7;
        uVar8 = local_ec;
        if (local_f4 < *(float *)(local_9c + 0x14)) {
          uVar8 = FUN_00493330();
          local_d8 = (int)((ulonglong)uVar8 >> 0x20);
          local_dc = (undefined4)uVar8;
          if (*(int *)(DAT_00917580 + 0x14) < local_d8) {
            local_d8 = *(int *)(DAT_00917580 + 0x14);
          }
          *local_b4 = local_dc;
          local_b4[1] = local_d8;
        }
        local_b4 = local_b4 + 2;
        local_ec = uVar8;
        puVar4 = (undefined4 *)FUN_00440130(local_110,local_74,local_70,local_6c);
        local_74 = *puVar4;
        local_70 = puVar4[1];
        local_6c = puVar4[2];
        local_a4 = local_a4 + local_a0;
        local_44 = local_74;
        local_40 = local_70;
        local_3c = local_6c;
      }
      puVar4 = (undefined4 *)FUN_00440130(local_128,local_68,local_64,local_60);
      local_68 = (float)*puVar4;
      local_64 = puVar4[1];
      local_60 = (float)puVar4[2];
      local_a8 = local_a8 + local_a0;
      local_38 = local_68;
      local_34 = local_64;
      local_30 = local_60;
    }
    if ((DAT_008e791c != DAT_008e7924) || (DAT_008e7920 != DAT_008e7928)) {
      DAT_008e791c = DAT_008e7924;
      DAT_008e7920 = DAT_008e7928;
    }
  }
  FUN_0083e885();
  return;
}

