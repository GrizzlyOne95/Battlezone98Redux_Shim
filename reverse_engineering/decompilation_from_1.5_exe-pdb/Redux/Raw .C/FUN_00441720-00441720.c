
void FUN_00441720(int param_1,int param_2,undefined4 param_3,int param_4,int *param_5,
                 undefined4 *param_6)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined1 local_308 [72];
  undefined1 local_2c0 [72];
  undefined1 local_278 [64];
  undefined1 local_238 [64];
  undefined1 local_1f8 [12];
  undefined1 local_1ec [12];
  undefined1 local_1e0 [12];
  undefined1 local_1d4 [12];
  undefined1 local_1c8 [12];
  undefined1 local_1bc [12];
  undefined1 local_1b0 [12];
  undefined1 local_1a4 [12];
  undefined1 local_198 [12];
  undefined1 local_18c [12];
  undefined1 local_180 [12];
  undefined4 local_174;
  int local_170;
  int local_16c;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  int local_144;
  int local_140;
  int local_13c;
  undefined4 local_138 [16];
  int local_f8;
  int local_f4;
  int local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8 [24];
  int local_68 [4];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_174 = *(undefined4 *)(param_2 + 0x9c);
  puVar1 = (undefined4 *)
           FUN_00440130(local_1b0,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),
                        *(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x2c),
                        *(undefined4 *)(param_1 + 0x30),*(undefined4 *)(param_1 + 0x34));
  puVar1 = (undefined4 *)FUN_004400d0(local_1d4,0x3f000000,*puVar1,puVar1[1],puVar1[2]);
  local_d4 = *puVar1;
  local_d0 = puVar1[1];
  local_cc = puVar1[2];
  local_68[0] = *(int *)(param_1 + 0x20);
  local_68[2] = *(undefined4 *)(param_1 + 0x28);
  uStack_54 = *(undefined4 *)(param_1 + 0x28);
  uStack_50 = *(undefined4 *)(param_1 + 0x2c);
  uStack_48 = *(undefined4 *)(param_1 + 0x28);
  uStack_44 = *(undefined4 *)(param_1 + 0x2c);
  uStack_38 = *(undefined4 *)(param_1 + 0x2c);
  uStack_30 = *(undefined4 *)(param_1 + 0x34);
  uStack_24 = *(undefined4 *)(param_1 + 0x34);
  uStack_20 = *(undefined4 *)(param_1 + 0x20);
  uStack_18 = *(undefined4 *)(param_1 + 0x34);
  uStack_14 = *(undefined4 *)(param_1 + 0x20);
  local_68[1] = local_d0;
  local_68[3] = local_d4;
  uStack_58 = local_d0;
  uStack_4c = local_d0;
  uStack_40 = local_d0;
  uStack_3c = local_cc;
  uStack_34 = local_d0;
  uStack_2c = local_d4;
  uStack_28 = local_d0;
  uStack_1c = local_d0;
  uStack_10 = local_d0;
  uStack_c = local_cc;
  puVar1 = (undefined4 *)FUN_008203f0(local_238,param_3);
  puVar5 = local_138;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar5 = puVar5 + 1;
  }
  puVar1 = (undefined4 *)FUN_0081fe60(local_278,param_1 + 0x38,local_138);
  puVar5 = local_138;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar5 = puVar5 + 1;
  }
  FUN_00820180(local_c8,local_68,8,local_138);
  puVar1 = (undefined4 *)FUN_00440000(local_18c,0,0,0,param_2);
  puVar1 = (undefined4 *)FUN_00444ba0(local_198,*puVar1,puVar1[1],puVar1[2]);
  local_150 = *puVar1;
  local_14c = puVar1[1];
  local_148 = puVar1[2];
  *param_5 = 0;
  param_5[0x14] = param_4;
  for (local_16c = 0; local_16c < 8; local_16c = local_16c + 1) {
    piVar2 = (int *)FUN_00444ba0(local_1f8,local_68[local_16c * 3],local_68[local_16c * 3 + 1],
                                 local_68[local_16c * 3 + 2],*(undefined4 *)(param_1 + 0x1c));
    local_144 = *piVar2;
    local_140 = piVar2[1];
    local_13c = piVar2[2];
    piVar2 = (int *)FUN_004401a0(local_1bc,local_144,local_140,local_13c,local_150,local_14c,
                                 local_148);
    local_144 = *piVar2;
    local_140 = piVar2[1];
    local_13c = piVar2[2];
    puVar1 = (undefined4 *)FUN_00440300(local_180,&local_144,param_3);
    local_e0 = *puVar1;
    local_dc = puVar1[1];
    local_d8 = puVar1[2];
    local_ec = local_c8[local_16c * 3];
    local_e8 = local_c8[local_16c * 3 + 1];
    local_e4 = local_c8[local_16c * 3 + 2];
    iVar3 = FUN_00444580(local_ec,local_e8,local_e4,local_e0,local_dc,local_d8,local_174,
                         param_5[0x14],&local_170,&local_f8);
    if (iVar3 != 0) {
      *param_5 = 1;
      param_5[0x15] = local_68[local_16c * 3];
      param_5[0x16] = local_68[local_16c * 3 + 1];
      param_5[0x17] = local_68[local_16c * 3 + 2];
      param_5[0x18] = local_144;
      param_5[0x19] = local_140;
      param_5[0x1a] = local_13c;
      param_5[0x14] = local_170;
      param_5[0x1b] = local_f8;
      param_5[0x1c] = local_f4;
      param_5[0x1d] = local_f0;
      local_168 = local_ec;
      local_164 = local_e8;
      local_160 = local_e4;
      local_15c = local_e0;
      local_158 = local_dc;
      local_154 = local_d8;
    }
  }
  if (*param_5 != 0) {
    param_5[1] = param_2;
    piVar2 = (int *)FUN_0062bf70(local_308,param_2);
    piVar4 = param_5 + 2;
    for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar4 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar4 = piVar4 + 1;
    }
    *param_6 = 1;
    param_6[1] = *(undefined4 *)(param_1 + 0x1c);
    puVar1 = (undefined4 *)FUN_0062bf70(local_2c0,*(undefined4 *)(param_1 + 0x1c));
    puVar5 = param_6 + 2;
    for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar5 = puVar5 + 1;
    }
    param_6[0x14] = param_5[0x14];
    puVar1 = (undefined4 *)
             FUN_00439d00(local_1a4,local_168,local_164,local_160,param_6[0x14],local_15c,local_158,
                          local_154);
    param_6[0x15] = *puVar1;
    param_6[0x16] = puVar1[1];
    param_6[0x17] = puVar1[2];
    param_6[0x18] = param_5[0x18];
    param_6[0x19] = param_5[0x19];
    param_6[0x1a] = param_5[0x1a];
    piVar2 = (int *)FUN_00440060(local_1c8,param_5[0x18],param_5[0x19],param_5[0x1a]);
    param_5[0x18] = *piVar2;
    param_5[0x19] = piVar2[1];
    param_5[0x1a] = piVar2[2];
    piVar2 = (int *)FUN_00440210(local_1e0,param_5 + 0x1b,param_3);
    param_5[0x1b] = *piVar2;
    param_5[0x1c] = piVar2[1];
    param_5[0x1d] = piVar2[2];
    puVar1 = (undefined4 *)FUN_00440060(local_1ec,param_5[0x1b],param_5[0x1c],param_5[0x1d]);
    param_6[0x1b] = *puVar1;
    param_6[0x1c] = puVar1[1];
    param_6[0x1d] = puVar1[2];
  }
  FUN_0083e885();
  return;
}

