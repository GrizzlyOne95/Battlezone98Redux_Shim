
void __fastcall FUN_004ad070(int *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_108 [12];
  int local_fc;
  int local_f8;
  int local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  int local_d4;
  int local_d0;
  int local_cc;
  int *local_c8;
  undefined4 local_c4 [10];
  double local_9c;
  double local_94;
  double local_8c;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  float local_78;
  float local_74;
  float local_70;
  int local_6c;
  float local_68;
  int local_64;
  float local_60;
  float local_5c;
  float local_58;
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
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_c8 = param_1;
  FUN_0062de40(param_1[0x37],0x200);
  if (*(int *)(local_c8[0x38] + 0x314) != 0) {
    puVar2 = (undefined4 *)(local_c8[0x37] + 0x20);
    puVar4 = local_c4;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    local_9c = (double)(float)local_c8[0x3c];
    local_94 = (double)(float)local_c8[0x3d];
    local_8c = (double)(float)local_c8[0x3e];
    FUN_004cb7b0(local_c4,0);
  }
  if (DAT_00917a50 != 0) {
    puVar2 = &DAT_008fe1e0;
    puVar4 = local_c4;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    local_9c = (double)(float)local_c8[0x3c];
    fVar5 = (float10)FUN_007855e0((double)(float)local_c8[0x3c],(double)(float)local_c8[0x3e]);
    local_94 = (double)fVar5;
    local_8c = (double)(float)local_c8[0x3e];
    FUN_004cb7b0(local_c4,0);
  }
  if (5.0 < *(float *)(local_c8[0x36] + 0x14)) {
    local_d4 = FUN_00439e60();
    iVar3 = local_c8[0x36];
    local_18 = *(undefined4 *)(iVar3 + 8);
    local_14 = *(undefined4 *)(iVar3 + 0xc);
    local_10 = *(float *)(iVar3 + 0x10);
    local_c = *(float *)(iVar3 + 0x14);
    FUN_00820180(&local_18,&local_18,1,local_c8[0x37] + 0x20);
    FUN_00820180(&local_18,&local_18,1,local_d4 + 0x40);
    iVar3 = FUN_006895d0();
    if ((double)iVar3 <= 0.0) {
      local_d8 = (local_c * 3.0) / local_10;
      FUN_0049b4c0();
    }
  }
  FUN_00492640();
  puVar2 = (undefined4 *)FUN_0081fd40();
  local_54 = *puVar2;
  local_50 = puVar2[1];
  local_4c = puVar2[2];
  local_48 = puVar2[3];
  local_44 = puVar2[4];
  local_40 = puVar2[5];
  local_cc = (int)(*(float *)(local_c8[0x36] + 0x14) * 10.0);
  local_3c = local_54;
  local_38 = local_50;
  local_34 = local_4c;
  local_30 = local_48;
  local_2c = local_44;
  local_28 = local_40;
  while( true ) {
    local_f4 = local_cc;
    if (local_cc == 0) break;
    local_cc = local_cc + -1;
    fVar5 = (float10)FUN_004464c0();
    local_f0 = (float)fVar5;
    local_60 = local_f0 * 20.0 + (float)local_c8[0x45];
    fVar5 = (float10)FUN_004464c0();
    local_e4 = (float)fVar5;
    local_5c = local_e4 * 15.0 + (float)local_c8[0x46] + 5.0;
    fVar5 = (float10)FUN_004464c0();
    local_e8 = (float)fVar5;
    local_58 = local_e8 * 20.0 + (float)local_c8[0x47];
    FUN_0058b650(&local_54,&local_60);
  }
  local_cc = (int)*(float *)(local_c8[0x36] + 0x14);
  while( true ) {
    local_f8 = local_cc;
    if (local_cc == 0) break;
    local_cc = local_cc + -1;
    fVar5 = (float10)FUN_004464c0();
    local_e0 = (float)fVar5;
    local_78 = local_e0 * 40.0 + (float)local_c8[0x45];
    fVar5 = (float10)FUN_004464c0();
    local_ec = (float)fVar5;
    local_74 = local_ec * 30.0 + (float)local_c8[0x46] + 10.0;
    fVar5 = (float10)FUN_004464c0();
    local_dc = (float)fVar5;
    local_70 = local_dc * 40.0 + (float)local_c8[0x47];
    FUN_004d10b0(&local_54,&local_78);
  }
  local_cc = (int)*(float *)(local_c8[0x36] + 0x14);
  while( true ) {
    local_fc = local_cc;
    if (local_cc == 0) break;
    local_6c = local_c8[0x45];
    local_68 = (float)local_c8[0x46] + 10.0;
    local_64 = local_c8[0x47];
    local_cc = local_cc + -1;
    FUN_004927d0();
  }
  local_cc = local_cc + -1;
  puVar2 = (undefined4 *)FUN_00439de0(local_108,local_c8[0x37] + 0x20);
  local_84 = *puVar2;
  local_80 = puVar2[1];
  local_7c = puVar2[2];
  local_d0 = 0;
  local_24 = local_84;
  local_20 = local_80;
  local_1c = local_7c;
  if ((*(uint *)(local_c8[0x37] + 0x14) & 0x80) == 0) {
    iVar3 = FUN_00572a70();
    if (iVar3 == 0) {
      local_d0 = *(int *)(local_c8[0x38] + 0x4c);
    }
    else {
      cVar1 = FUN_00571c50();
      if ((cVar1 == '\0') && (cVar1 = FUN_004b9860(), cVar1 != '\0')) {
        local_d0 = FUN_0046b550(*(undefined4 *)(local_c8[0x38] + 0x4c),
                                (*(int *)(local_c8[0x38] + 0x48) + 2) / 2);
      }
    }
  }
  local_c8[0xa0] = 0;
  (**(code **)(*local_c8 + 0x10))();
  if (0 < local_d0) {
    FUN_005c65a0(&local_84,local_d0);
  }
  FUN_0083e885();
  return;
}

