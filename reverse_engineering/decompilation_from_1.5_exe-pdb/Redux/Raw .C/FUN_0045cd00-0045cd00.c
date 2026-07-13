
void FUN_0045cd00(int param_1,float param_2)

{
  undefined8 uVar1;
  undefined4 *puVar2;
  int iVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  undefined1 local_130 [12];
  undefined1 local_124 [12];
  undefined1 local_118 [12];
  undefined1 local_10c [36];
  undefined1 local_e8 [12];
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  undefined8 local_cc;
  float local_c4;
  undefined4 *local_c0;
  int local_bc;
  undefined4 *local_b8;
  float local_b4;
  undefined8 local_b0;
  int local_a8;
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
  (**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_cc = FUN_0045c460();
  fVar5 = (float)((ulonglong)local_cc >> 0x20);
  local_b0 = local_cc;
  if (((((float)local_cc < DAT_0091738c) || (DAT_00917394 < (float)local_cc)) ||
      (fVar5 < DAT_00917390)) || (DAT_00917388 < fVar5)) {
    fVar4 = (float10)FUN_00447ed0();
    local_d8 = (float)fVar4;
    fVar4 = (float10)FUN_00447ed0();
    local_d4 = (float)fVar4;
    (**(code **)(*(int *)(param_1 + 0x18) + 0x30))();
    local_bc = FUN_0045c4f0();
    if ((local_bc == 0) || ((*(uint *)(local_bc + 0x114) & 4) == 0)) {
      iVar3 = FUN_0045c4d0();
      iVar3 = FUN_0045c4d0(*(undefined8 *)(iVar3 + 0x38));
      puVar2 = (undefined4 *)FUN_00785430(local_124,*(undefined8 *)(iVar3 + 0x28));
      local_98 = *puVar2;
      local_94 = puVar2[1];
      local_90 = puVar2[2];
      local_b8 = &local_98;
      local_50 = local_98;
      local_4c = local_94;
      local_48 = local_90;
      uVar1 = local_b0;
    }
    else {
      puVar2 = (undefined4 *)FUN_00440000(local_e8,0,0x3f800000,0);
      local_80 = *puVar2;
      local_7c = puVar2[1];
      local_78 = puVar2[2];
      local_b8 = &local_80;
      local_38 = local_80;
      local_34 = local_7c;
      local_30 = local_78;
      uVar1 = local_b0;
    }
    local_b0._4_4_ = (float)((ulonglong)uVar1 >> 0x20);
    local_b0._0_4_ = (float)uVar1;
    local_c0 = local_b8;
    local_68 = *local_b8;
    local_64 = local_b8[1];
    local_60 = local_b8[2];
    fVar5 = local_d4 - local_b0._4_4_;
    fVar6 = local_d8 - (float)local_b0;
    local_b0 = uVar1;
    puVar2 = (undefined4 *)FUN_00440000(local_10c,fVar6,0,fVar5);
    local_74 = *puVar2;
    local_70 = puVar2[1];
    local_6c = puVar2[2];
    local_44 = local_74;
    local_40 = local_70;
    local_3c = local_6c;
    puVar2 = (undefined4 *)FUN_004440d0();
    local_8c = *puVar2;
    local_88 = puVar2[1];
    local_84 = puVar2[2];
    local_14 = local_8c;
    local_10 = local_88;
    local_c = local_84;
    puVar2 = (undefined4 *)FUN_004440d0();
    local_a4 = *puVar2;
    local_a0 = puVar2[1];
    local_9c = puVar2[2];
    local_20 = local_a4;
    local_1c = local_a0;
    local_18 = local_9c;
    local_a8 = FUN_0045c490();
    local_dc = param_2 * -0.1;
    fVar4 = (float10)FUN_004428b0(&local_a4,local_a8 + 0x18,*(undefined4 *)(local_a8 + 0x18),
                                  *(undefined4 *)(local_a8 + 0x1c),*(undefined4 *)(local_a8 + 0x20))
    ;
    local_d0 = (float)fVar4;
    fVar4 = (float10)FUN_00453f80(local_d0 * *(float *)(local_a8 + 0xc));
    local_c4 = (float)fVar4;
    fVar4 = (float10)FUN_0045c400(local_dc * local_c4);
    puVar2 = (undefined4 *)FUN_004462d0(local_118,(float)fVar4);
    local_2c = *puVar2;
    local_28 = puVar2[1];
    local_24 = puVar2[2];
    *(undefined4 *)(local_a8 + 0x18) = local_2c;
    *(undefined4 *)(local_a8 + 0x1c) = local_28;
    *(undefined4 *)(local_a8 + 0x20) = local_24;
    puVar2 = (undefined4 *)
             FUN_00439d00(local_130,*(undefined4 *)(local_a8 + 0x18),
                          *(undefined4 *)(local_a8 + 0x1c),*(undefined4 *)(local_a8 + 0x20),
                          param_2 * 10.0,local_a4,local_a0,local_9c);
    local_5c = *puVar2;
    local_58 = puVar2[1];
    local_54 = puVar2[2];
    *(undefined4 *)(local_a8 + 0x18) = local_5c;
    *(undefined4 *)(local_a8 + 0x1c) = local_58;
    *(undefined4 *)(local_a8 + 0x20) = local_54;
    fVar4 = (float10)FUN_0045c420();
    *(float *)(local_a8 + 8) = (float)fVar4;
    if (*(float *)(local_a8 + 8) <= 0.0) {
      local_b4 = 1e+30;
    }
    else {
      local_b4 = 1.0 / *(float *)(local_a8 + 8);
    }
    *(float *)(local_a8 + 0xc) = local_b4;
  }
  FUN_0083e885();
  return;
}

