
void __fastcall FUN_0047f330(int *param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  char cVar5;
  undefined8 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  float10 fVar10;
  undefined1 local_110 [12];
  undefined1 local_104 [12];
  float local_f8;
  int local_f4;
  int local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  undefined4 local_d4;
  int local_d0;
  int local_cc;
  int *local_c8;
  undefined4 local_c4;
  undefined4 uStack_c0;
  undefined4 local_bc;
  undefined4 uStack_b8;
  undefined4 local_b4;
  undefined4 uStack_b0;
  undefined4 local_ac [10];
  undefined8 local_84;
  double local_7c;
  undefined8 local_74;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
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
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_c8 = param_1;
  FUN_0062de40(param_1[0x37],0x200);
  FUN_0047c2b0();
  if (local_c8[0x37] == local_c8[0x84]) {
    puVar6 = (undefined8 *)FUN_0081fd40();
    local_c4 = *(undefined4 *)puVar6;
    uStack_c0 = *(undefined4 *)((int)puVar6 + 4);
    uVar4 = *puVar6;
    uVar2 = *puVar6;
    local_84 = *puVar6;
    local_bc = *(undefined4 *)(puVar6 + 1);
    uStack_b8 = *(undefined4 *)((int)puVar6 + 0xc);
    local_7c = (double)puVar6[1];
    puVar1 = puVar6 + 2;
    local_b4 = *(undefined4 *)puVar1;
    uStack_b0 = *(undefined4 *)((int)puVar6 + 0x14);
    uVar3 = *puVar1;
    local_74 = *puVar1;
    puVar7 = (undefined4 *)(local_c8[0x37] + 0x20);
    puVar9 = local_ac;
    local_48 = local_c4;
    local_44 = uStack_c0;
    local_40 = local_bc;
    local_3c = uStack_b8;
    local_38 = local_b4;
    local_34 = uStack_b0;
    for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar9 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar9 = puVar9 + 1;
    }
    if (5.0 < *(float *)(local_c8[0x36] + 0x14)) {
      if ((DAT_00917a50 != 0) && (*(int *)(local_c8[0x38] + 0x1c) == 2)) {
        puVar7 = &DAT_008fe1e0;
        puVar9 = local_ac;
        for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar9 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar9 = puVar9 + 1;
        }
        local_84 = uVar2;
        fVar10 = (float10)FUN_007855e0(uVar4,uVar3);
        local_7c = (double)fVar10;
        local_74 = CONCAT44(uStack_b0,local_b4);
        FUN_004cb7b0(local_ac,0);
      }
      local_d4 = FUN_00439e60();
      iVar8 = local_c8[0x36];
      local_18 = *(undefined4 *)(iVar8 + 8);
      local_14 = *(undefined4 *)(iVar8 + 0xc);
      local_10 = *(float *)(iVar8 + 0x10);
      local_c = *(float *)(iVar8 + 0x14);
      puVar7 = (undefined4 *)
               FUN_006897e0(local_110,local_d4,CONCAT44(uStack_c0,local_c4),
                            CONCAT44(uStack_b8,local_bc),CONCAT44(uStack_b0,local_b4));
      local_24 = *puVar7;
      local_20 = puVar7[1];
      local_1c = (float)puVar7[2];
      local_18 = local_24;
      local_14 = local_20;
      local_10 = local_1c;
      iVar8 = FUN_006895d0();
      if ((double)iVar8 <= 0.0) {
        local_d8 = (local_c * 3.0) / local_10;
        FUN_0049b4c0();
      }
    }
    if (*(int *)(local_c8[0x38] + 0x144) == 0) {
      if (*(float *)(local_c8[0x36] + 0x14) <= 5.0) {
        if (*(float *)(local_c8[0x36] + 0x14) <= 2.0) {
          FUN_004cb7b0(local_ac,0);
        }
        else {
          FUN_004cb7b0(local_ac,0);
        }
      }
      else {
        FUN_004cb7b0(local_ac,0);
      }
    }
    else {
      FUN_004cb7b0(local_ac,0);
    }
    local_cc = (int)(*(float *)(local_c8[0x36] + 0x14) * 10.0);
    while( true ) {
      local_f0 = local_cc;
      if (local_cc == 0) break;
      local_cc = local_cc + -1;
      fVar10 = (float10)FUN_004464c0();
      local_f8 = (float)fVar10;
      local_54 = local_f8 * 20.0 + (float)local_c8[0x45];
      fVar10 = (float10)FUN_004464c0();
      local_e4 = (float)fVar10;
      local_50 = local_e4 * 15.0 + (float)local_c8[0x46] + 5.0;
      fVar10 = (float10)FUN_004464c0();
      local_e0 = (float)fVar10;
      local_4c = local_e0 * 20.0 + (float)local_c8[0x47];
      FUN_0058b650(&local_c4,&local_54);
    }
    local_cc = (int)*(float *)(local_c8[0x36] + 0x14);
    while( true ) {
      local_f4 = local_cc;
      iVar8 = local_cc + -1;
      if (local_cc == 0) break;
      local_cc = iVar8;
      fVar10 = (float10)FUN_004464c0();
      local_ec = (float)fVar10;
      local_60 = local_ec * 40.0 + (float)local_c8[0x45];
      fVar10 = (float10)FUN_004464c0();
      local_e8 = (float)fVar10;
      local_5c = local_e8 * 30.0 + (float)local_c8[0x46] + 10.0;
      fVar10 = (float10)FUN_004464c0();
      local_dc = (float)fVar10;
      local_58 = local_dc * 40.0 + (float)local_c8[0x47];
      FUN_004d10b0(&local_c4,&local_60);
    }
    local_cc = iVar8;
    if ((*(uint *)(local_c8[0x37] + 0x14) & 0x800) != 0) {
      FUN_0068a2d0();
    }
    FUN_00492640();
    puVar7 = (undefined4 *)FUN_00439de0(local_104,local_c8[0x37] + 0x20);
    local_6c = *puVar7;
    local_68 = puVar7[1];
    local_64 = puVar7[2];
    local_d0 = 0;
    local_30 = local_6c;
    local_2c = local_68;
    local_28 = local_64;
    if ((*(uint *)(local_c8[0x37] + 0x14) & 0x80) == 0) {
      iVar8 = FUN_00572a70();
      if (iVar8 == 0) {
        local_d0 = *(int *)(local_c8[0x38] + 0x4c);
      }
      else {
        cVar5 = FUN_00571c50();
        if ((cVar5 == '\0') && (cVar5 = FUN_004b9860(), cVar5 != '\0')) {
          local_d0 = FUN_0046b550(*(undefined4 *)(local_c8[0x38] + 0x4c),
                                  (*(int *)(local_c8[0x38] + 0x48) + 2) / 2);
        }
      }
    }
    (**(code **)(*local_c8 + 0x10))();
    if (0 < local_d0) {
      FUN_005c65a0(&local_6c,local_d0);
    }
  }
  FUN_0083e885();
  return;
}

