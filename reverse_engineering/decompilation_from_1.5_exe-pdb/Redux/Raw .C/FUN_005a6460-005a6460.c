
void __fastcall FUN_005a6460(int param_1)

{
  short sVar1;
  char cVar2;
  short sVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int *piVar6;
  uint uVar7;
  float *pfVar8;
  int iVar9;
  undefined4 *puVar10;
  float10 fVar11;
  undefined1 local_184 [64];
  undefined1 local_144 [12];
  undefined1 local_138 [12];
  undefined1 local_12c [4];
  undefined1 local_128 [4];
  undefined1 local_124 [4];
  float local_120;
  float local_11c;
  float local_118;
  undefined4 local_114;
  undefined *local_110;
  float local_10c;
  int local_108;
  float local_104;
  int local_100;
  int local_fc;
  float local_f8;
  float local_f4;
  undefined4 local_f0;
  float local_ec;
  float local_e8;
  int local_e4;
  float local_e0;
  int local_dc;
  int local_d8;
  int local_d4;
  undefined4 local_d0 [16];
  undefined4 local_90 [16];
  float local_50;
  float local_4c;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
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
  local_d4 = param_1;
  if (*(float *)(param_1 + 0x34) <= 0.0 && *(float *)(param_1 + 0x34) != 0.0) {
    local_e4 = 0;
    local_e0 = *(float *)(*(int *)(param_1 + 0xc) + 0xd0);
    local_e0 = local_e0 * local_e0;
    puVar4 = (undefined4 *)FUN_00439de0(local_138,*(int *)(param_1 + 0x14) + 0x20);
    local_44 = *puVar4;
    local_40 = puVar4[1];
    local_3c = puVar4[2];
    local_38 = local_44;
    local_34 = local_40;
    local_30 = local_3c;
    uVar5 = FUN_0047e9a0(*(undefined4 *)(local_d4 + 0x14));
    local_114 = FUN_005e0bc0(uVar5);
    local_110 = &DAT_0094e2d4;
    FUN_00422170();
    puVar4 = (undefined4 *)FID_conflict_begin(local_128);
    local_f0 = *puVar4;
    while( true ) {
      uVar5 = FID_conflict_end(local_12c);
      cVar2 = FID_conflict_operator__(uVar5);
      if (cVar2 == '\0') break;
      piVar6 = (int *)FUN_00421ec0();
      local_dc = *piVar6;
      local_108 = (**(code **)(*(int *)(local_dc + 0x18) + 4))();
      if (((-1 < local_108) && (cVar2 = FUN_005e1350(local_108), cVar2 != '\0')) &&
         (uVar7 = FUN_0045c4b0(), (uVar7 & 0x200) == 0)) {
        puVar4 = (undefined4 *)
                 (**(code **)(*(int *)(local_dc + 0x18) + 0xc))(local_38,local_34,local_30);
        fVar11 = (float10)FUN_004620b0(*puVar4,puVar4[1],puVar4[2]);
        local_f8 = (float)fVar11;
        if (local_f8 < local_e0) {
          local_e4 = local_dc;
          local_e0 = local_f8;
        }
      }
      FUN_0046b260(local_124,0);
    }
    if (local_e4 != 0) {
      pfVar8 = (float *)(**(code **)(*(int *)(local_e4 + 0x18) + 0xc))();
      local_14 = *pfVar8;
      local_10 = pfVar8[1];
      local_c = pfVar8[2];
      pfVar8 = (float *)FUN_004624b0();
      local_20 = *pfVar8;
      local_1c = pfVar8[1];
      local_18 = pfVar8[2];
      pfVar8 = (float *)FUN_00439de0(local_144,*(int *)(local_d4 + 0x14) + 0x20);
      local_50 = *pfVar8;
      local_4c = pfVar8[1];
      local_48 = pfVar8[2];
      local_100 = *(int *)(*(int *)(local_d4 + 0xc) + 0xd8);
      local_10c = *(float *)(local_100 + 0x54);
      local_14 = local_14 - local_50;
      local_10 = local_10 - local_4c;
      local_c = local_c - local_48;
      local_f4 = (local_20 * local_20 + local_1c * local_1c + local_18 * local_18) -
                 local_10c * local_10c;
      local_ec = local_14 * local_20 + local_10 * local_1c + local_c * local_18;
      local_11c = local_14 * local_14 + local_10 * local_10 + local_c * local_c;
      local_104 = local_ec * local_ec - local_f4 * local_11c;
      local_2c = local_50;
      local_28 = local_4c;
      local_24 = local_48;
      if (0.0 < local_104) {
        local_118 = -local_ec;
        fVar11 = (float10)FUN_00417910(local_104);
        local_120 = (float)fVar11;
        local_e8 = (local_118 - local_120) / local_f4;
      }
      else {
        local_e8 = -local_ec / local_f4;
      }
      local_14 = local_e8 * local_20 + local_14;
      local_10 = local_e8 * local_1c + local_10;
      local_c = local_e8 * local_18 + local_c;
      puVar4 = (undefined4 *)FUN_0081fa10(local_184,&local_2c,&local_14);
      puVar10 = local_d0;
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar10 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar10 = puVar10 + 1;
      }
      puVar4 = local_d0;
      puVar10 = local_90;
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar10 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar10 = puVar10 + 1;
      }
      local_fc = *(int *)(*(int *)(local_d4 + 0xc) + 0xd4);
      if (local_fc != 0) {
        FUN_004cb7b0(local_90,*(undefined4 *)(local_d4 + 0xd8));
      }
      iVar9 = FUN_00572a70();
      if ((iVar9 == 0) ||
         (sVar1 = *(short *)(local_d4 + 0x7c), sVar3 = FUN_00572d90(), sVar1 == sVar3)) {
        local_d8 = FUN_00586ff0(local_90,*(undefined4 *)(local_d4 + 0xd8));
        *(ushort *)(local_d8 + 0x68) =
             *(ushort *)(local_d8 + 0x68) & 0xffef | (*(ushort *)(local_d4 + 0x68) >> 4 & 1) << 4;
        *(ushort *)(local_d8 + 0x68) =
             *(ushort *)(local_d8 + 0x68) & 0xffdf | (*(ushort *)(local_d4 + 0x68) >> 5 & 1) << 5;
        *(ushort *)(local_d8 + 0x68) =
             *(ushort *)(local_d8 + 0x68) & 0xfc3f | (*(ushort *)(local_d4 + 0x68) >> 6 & 0xf) << 6;
        *(undefined2 *)(local_d8 + 0x7c) = *(undefined2 *)(local_d4 + 0x7c);
        *(short *)(local_d8 + 0x7e) = *(short *)(local_d4 + 0x7e) + 1;
        *(undefined4 *)(local_d8 + 0x80) = 1;
      }
      *(uint *)(*(int *)(local_d4 + 0x14) + 0x14) =
           *(uint *)(*(int *)(local_d4 + 0x14) + 0x14) | 0x200;
    }
  }
  FUN_0083e885();
  return;
}

