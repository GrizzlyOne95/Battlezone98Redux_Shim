
void __thiscall FUN_005e61c0(int param_1,int param_2)

{
  float *pfVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  float *pfVar5;
  float10 fVar6;
  undefined1 local_284 [64];
  undefined1 local_244 [12];
  undefined1 local_238 [12];
  undefined1 local_22c [12];
  undefined1 local_220 [12];
  undefined1 local_214 [12];
  undefined1 local_208 [12];
  undefined1 local_1fc [12];
  undefined1 local_1f0 [12];
  undefined4 local_1e4;
  int local_1e0;
  float local_1dc;
  float local_1d8;
  int local_1d4;
  float local_1d0;
  float local_1cc;
  float local_1c8;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  float local_1b4;
  float local_1b0;
  float local_1ac;
  float local_1a8;
  float local_1a4;
  undefined4 local_1a0 [16];
  float local_160 [16];
  float local_120 [4];
  float local_110;
  float local_10c;
  float local_108;
  float local_104;
  float local_100;
  double local_f8;
  double local_f0;
  double local_e8;
  float local_e0;
  float local_dc;
  float local_d8;
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
  float local_74;
  float local_70;
  float local_6c;
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
  local_1e0 = *(int *)(*(int *)(param_1 + 0xc) + 0x78);
  local_1d4 = param_1;
  if (0 < local_1e0) {
    local_1d8 = *(float *)(*(int *)(param_1 + 0xc) + 0x88);
    local_1dc = *(float *)(*(int *)(param_1 + 0xc) + 0x84);
    if ((local_1d8 != 0.0) && (local_1dc != 0.0)) {
      if (*(float *)(param_1 + 0x100) <= local_1dc && local_1dc != *(float *)(param_1 + 0x100)) {
        local_1dc = *(float *)(param_1 + 0x100);
      }
      puVar2 = (undefined4 *)(*(int *)(param_1 + 0x14) + 0x20);
      puVar4 = local_1a0;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      pfVar1 = (float *)FUN_0081fe60(local_284,*(int *)(param_1 + 0x14) + 0x20,param_2 + 0x40);
      pfVar5 = local_160;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *pfVar5 = *pfVar1;
        pfVar1 = pfVar1 + 1;
        pfVar5 = pfVar5 + 1;
      }
      pfVar1 = local_160;
      pfVar5 = local_120;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *pfVar5 = *pfVar1;
        pfVar1 = pfVar1 + 1;
        pfVar5 = pfVar5 + 1;
      }
      local_74 = -local_1dc * local_108;
      local_70 = -local_1dc * local_104;
      local_6c = -local_1dc * local_100;
      local_1ac = (float)local_f8;
      local_1a8 = (float)local_f0;
      local_1a4 = (float)local_e8;
      local_1b8 = local_1ac + local_74;
      local_1b4 = local_1a8 + local_70;
      local_1b0 = local_1a4 + local_6c;
      local_e0 = local_74 * 0.5 + local_1ac;
      local_dc = local_70 * 0.5 + local_1a8;
      local_d8 = local_6c * 0.5 + local_1a4;
      iVar3 = FUN_006895d0(param_2,&local_e0,*(float *)(*(int *)(local_1d4 + 0xc) + 0x84) * 0.5);
      if (iVar3 < 1) {
        local_1c4 = local_1d8 * local_120[0];
        local_1c0 = local_1d8 * local_120[1];
        local_1bc = local_1d8 * local_120[2];
        local_1d0 = local_1d8 * local_120[3];
        local_1cc = local_1d8 * local_110;
        local_1c8 = local_1d8 * local_10c;
        local_1e4 = DAT_00920ef4;
        fVar6 = (float10)FUN_00456080(local_1a4,local_1b0);
        DAT_00920ef4 = (float)fVar6;
        puVar2 = (undefined4 *)
                 FUN_00440130(local_208,local_1ac,local_1a8,local_1a4,local_1c4,local_1c0,local_1bc)
        ;
        local_c8 = *puVar2;
        local_c4 = puVar2[1];
        local_c0 = puVar2[2];
        local_38 = local_c8;
        local_34 = local_c4;
        local_30 = local_c0;
        puVar2 = (undefined4 *)
                 FUN_00440130(local_244,local_1b8,local_1b4,local_1b0,local_1c4,local_1c0,local_1bc)
        ;
        local_b0 = *puVar2;
        local_ac = puVar2[1];
        local_a8 = puVar2[2];
        local_2c = local_b0;
        local_28 = local_ac;
        local_24 = local_a8;
        puVar2 = (undefined4 *)
                 FUN_004401a0(local_1fc,local_1b8,local_1b4,local_1b0,local_1c4,local_1c0,local_1bc)
        ;
        local_8c = *puVar2;
        local_88 = puVar2[1];
        local_84 = puVar2[2];
        local_20 = local_8c;
        local_1c = local_88;
        local_18 = local_84;
        puVar2 = (undefined4 *)
                 FUN_004401a0(local_1f0,local_1ac,local_1a8,local_1a4,local_1c4,local_1c0,local_1bc)
        ;
        local_a4 = *puVar2;
        local_a0 = puVar2[1];
        local_9c = puVar2[2];
        local_14 = local_a4;
        local_10 = local_a0;
        local_c = local_9c;
        FUN_0068d2f0(param_2,local_1e0,&local_38,4);
        puVar2 = (undefined4 *)
                 FUN_00440130(local_220,local_1ac,local_1a8,local_1a4,local_1d0,local_1cc,local_1c8)
        ;
        local_bc = *puVar2;
        local_b8 = puVar2[1];
        local_b4 = puVar2[2];
        local_68 = local_bc;
        local_64 = local_b8;
        local_60 = local_b4;
        puVar2 = (undefined4 *)
                 FUN_00440130(local_238,local_1b8,local_1b4,local_1b0,local_1d0,local_1cc,local_1c8)
        ;
        local_d4 = *puVar2;
        local_d0 = puVar2[1];
        local_cc = puVar2[2];
        local_5c = local_d4;
        local_58 = local_d0;
        local_54 = local_cc;
        puVar2 = (undefined4 *)
                 FUN_004401a0(local_22c,local_1b8,local_1b4,local_1b0,local_1d0,local_1cc,local_1c8)
        ;
        local_80 = *puVar2;
        local_7c = puVar2[1];
        local_78 = puVar2[2];
        local_50 = local_80;
        local_4c = local_7c;
        local_48 = local_78;
        puVar2 = (undefined4 *)
                 FUN_004401a0(local_214,local_1ac,local_1a8,local_1a4,local_1d0,local_1cc,local_1c8)
        ;
        local_98 = *puVar2;
        local_94 = puVar2[1];
        local_90 = puVar2[2];
        local_44 = local_98;
        local_40 = local_94;
        local_3c = local_90;
        FUN_0068d2f0(param_2,local_1e0,&local_68,4);
        DAT_00920ef4 = (float)local_1e4;
      }
    }
  }
  FUN_0083e885();
  return;
}

