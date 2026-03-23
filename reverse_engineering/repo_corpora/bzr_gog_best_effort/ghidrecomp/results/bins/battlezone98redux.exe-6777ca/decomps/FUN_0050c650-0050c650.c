
void __thiscall FUN_0050c650(int param_1,float param_2)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  float *pfVar5;
  float10 fVar6;
  float fVar7;
  undefined1 local_100 [4];
  undefined1 local_fc [8];
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_dc;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  undefined1 local_b4 [16];
  undefined4 local_a4;
  undefined1 local_88 [4];
  undefined4 local_84;
  undefined4 local_7c;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar7 = *(float *)(*(int *)(param_1 + 0xf8) + 0x160) - *(float *)(param_1 + 0x238);
  pfVar5 = (float *)(*(int *)(param_1 + 0xf8) + 0x168);
  local_b8 = param_1;
  if (*pfVar5 <= fVar7 && fVar7 != *pfVar5) {
    if ((*(int *)(param_1 + 0x230) == 0) && (*(char *)(*(int *)(param_1 + 0xf8) + 0x150) != '\0')) {
      FUN_0043a990();
      local_a4 = 0x1001;
      FUN_0043a9e0();
      local_7c = 1;
      local_84 = 10;
      uVar2 = FUN_0043aa30(*(int *)(local_b8 + 0xf8) + 0x150,*(undefined4 *)(local_b8 + 0xf4),
                           local_b4,local_88);
      *(undefined4 *)(local_b8 + 0x230) = uVar2;
    }
    local_18 = *(float *)(local_b8 + 0x108);
    local_14 = *(float *)(local_b8 + 0x10c);
    local_10 = *(float *)(local_b8 + 0x110);
    local_c = *(float *)(*(int *)(local_b8 + 0xf8) + 0x16c);
    local_6c = local_18 - local_c;
    local_68 = local_14 - local_c;
    local_64 = local_10 - local_c;
    local_60 = local_18 + local_c;
    local_5c = local_14 + local_c;
    local_58 = local_10 + local_c;
    FID_conflict_begin();
    while( true ) {
      FID_conflict_end();
      cVar1 = FID_conflict_operator__();
      if (cVar1 == '\0') break;
      FUN_0046b260(local_fc,0);
      piVar3 = (int *)FUN_00421ec0();
      local_c0 = *piVar3;
      if ((local_c0 != local_b8) &&
         (iVar4 = (**(code **)(*(int *)(local_c0 + 0x18) + 0x2c))(), iVar4 != 0)) {
        (**(code **)(*(int *)(local_c0 + 0x18) + 0x2c))();
        iVar4 = FUN_00442fd0(&local_6c);
        if (iVar4 != 0) {
          FUN_004c0af0();
          local_24 = local_24 - local_18;
          local_20 = local_20 - local_14;
          local_1c = local_1c - local_10;
          pfVar5 = (float *)FUN_004624b0();
          local_48 = *pfVar5;
          local_44 = pfVar5[1];
          local_40 = pfVar5[2];
          local_e4 = local_24 * local_24 + local_20 * local_20 + local_1c * local_1c;
          if (local_e4 < local_c * local_c) {
            fVar6 = (float10)FUN_00820570((double)(local_e4 + 0.0001));
            local_f4 = (float)fVar6;
            local_d0 = (local_f4 * *(float *)(*(int *)(local_b8 + 0xf8) + 0x170) +
                       *(float *)(*(int *)(local_b8 + 0xf8) + 0x174)) * param_2;
            local_c8 = param_2 * *(float *)(*(int *)(local_b8 + 0xf8) + 0x178);
            local_54 = local_24 * local_d0 - local_48 * local_c8;
            local_50 = local_20 * local_d0 - local_44 * local_c8;
            local_4c = local_1c * local_d0 - local_40 * local_c8;
            local_f0 = local_f4;
            FUN_004a75b0();
          }
        }
      }
    }
    FUN_0042d8c0();
    while( true ) {
      FID_conflict_begin();
      cVar1 = FUN_00420f10();
      if (cVar1 == '\0') break;
      FUN_00438c10(local_100,0);
      piVar3 = (int *)FUN_0042de50();
      local_bc = *piVar3;
      local_30 = (float)(*(double *)(*(int *)(local_bc + 0x14) + 0x48) - (double)local_18);
      local_2c = (float)(*(double *)(*(int *)(local_bc + 0x14) + 0x50) - (double)local_14);
      local_28 = (float)(*(double *)(*(int *)(local_bc + 0x14) + 0x58) - (double)local_10);
      local_3c = *(float *)(local_bc + 0x30);
      local_38 = *(float *)(local_bc + 0x34);
      local_34 = *(float *)(local_bc + 0x38);
      local_d4 = local_30 * local_30 + local_2c * local_2c + local_28 * local_28;
      if (local_d4 < local_c * local_c) {
        fVar6 = (float10)FUN_00820570((double)(local_d4 + 0.0001));
        local_ec = (float)fVar6;
        local_c4 = (local_ec * *(float *)(*(int *)(local_b8 + 0xf8) + 0x17c) +
                   *(float *)(*(int *)(local_b8 + 0xf8) + 0x180)) * param_2;
        local_cc = param_2 * *(float *)(*(int *)(local_b8 + 0xf8) + 0x184);
        *(float *)(local_bc + 0x30) =
             (local_30 * local_c4 - local_3c * local_cc) + *(float *)(local_bc + 0x30);
        *(float *)(local_bc + 0x34) =
             (local_2c * local_c4 - local_38 * local_cc) + *(float *)(local_bc + 0x34);
        *(float *)(local_bc + 0x38) =
             (local_28 * local_c4 - local_34 * local_cc) + *(float *)(local_bc + 0x38);
        local_e8 = local_ec;
        fVar6 = (float10)FUN_0045c420(*(undefined4 *)(local_bc + 0x30),
                                      *(undefined4 *)(local_bc + 0x34));
        *(float *)(local_bc + 0x20) = (float)fVar6;
        if (*(float *)(local_bc + 0x20) <= 0.0) {
          local_dc = 1e+30;
        }
        else {
          local_dc = 1.0 / *(float *)(local_bc + 0x20);
        }
        *(float *)(local_bc + 0x24) = local_dc;
      }
    }
  }
  FUN_00511460();
  FUN_0083e885();
  return;
}

