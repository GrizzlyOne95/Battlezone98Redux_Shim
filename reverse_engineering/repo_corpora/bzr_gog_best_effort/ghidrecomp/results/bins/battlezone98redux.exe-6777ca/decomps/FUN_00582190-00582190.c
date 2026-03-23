
void __thiscall FUN_00582190(int param_1,float param_2)

{
  int iVar1;
  undefined4 *puVar2;
  float *pfVar3;
  uint *puVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  uint *puVar7;
  float10 fVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined1 local_290 [64];
  undefined1 local_250 [64];
  undefined1 local_210 [12];
  undefined1 local_204 [12];
  undefined1 local_1f8 [12];
  undefined1 local_1ec [12];
  undefined1 local_1e0 [12];
  undefined1 local_1d4 [12];
  undefined1 local_1c8 [12];
  undefined1 local_1bc [12];
  float local_1b0;
  float local_1ac;
  undefined4 local_1a8;
  int local_1a4;
  int local_1a0;
  int *local_19c;
  float local_198;
  int *local_194;
  int local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  uint local_168 [16];
  undefined4 local_128 [16];
  uint local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  uint local_d0;
  uint local_cc;
  uint local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  uint local_a8 [4];
  uint local_98;
  uint local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined8 local_80;
  undefined8 local_78;
  undefined8 local_70;
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
  float local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(float *)(param_1 + 0xc0) = *(float *)(param_1 + 0xc0) + param_2;
  local_190 = param_1;
  if (*(char *)(param_1 + 0xd0) == '\0') {
    if (0.0 < *(float *)(param_1 + 0xc0)) {
      *(undefined4 *)(param_1 + 0xc0) = 0;
    }
    goto LAB_0058288e;
  }
  if ((*(int *)(param_1 + 200) != 0) && (0.0 < *(float *)(param_1 + 0xc0))) {
    local_1a4 = *(int *)(*(int *)(param_1 + 0xcc) + 0x13c);
    local_1a0 = *(int *)(*(int *)(param_1 + 0xcc) + 0x140);
    local_1a8 = FUN_00462590();
    if ((local_1a4 != -1) && (local_1a0 != -1)) {
      iVar1 = FUN_005e0f90(local_1a4,local_1a0);
      if (iVar1 < 0) goto LAB_00582852;
    }
    puVar2 = (undefined4 *)FUN_00439de0(local_1bc,local_190 + 0x28);
    local_180 = *puVar2;
    local_17c = puVar2[1];
    local_178 = puVar2[2];
    puVar2 = *(undefined4 **)(local_190 + 200);
    pfVar3 = (float *)FUN_004401a0(local_210,*puVar2,puVar2[1],puVar2[2],local_180,local_17c,
                                   local_178);
    local_38 = *pfVar3;
    local_34 = pfVar3[1];
    local_30 = pfVar3[2];
    local_14 = local_38;
    local_10 = local_34;
    local_c = local_30;
    fVar8 = (float10)FUN_00417910(local_38 * local_38 + local_34 * local_34 + local_30 * local_30);
    local_1ac = (float)fVar8;
    fVar8 = (float10)FUN_00417910(local_1ac * 9.8);
    local_1b0 = (float)fVar8;
    local_198 = local_1b0 + 20.0;
    pfVar3 = (float *)(*(int *)(local_190 + 8) + 0x84);
    if (*pfVar3 <= local_198 && local_198 != *pfVar3) {
      local_198 = *(float *)(*(int *)(local_190 + 8) + 0x84);
    }
    puVar2 = (undefined4 *)FUN_00439de0(local_1c8,local_190 + 0x28);
    local_174 = *puVar2;
    local_170 = puVar2[1];
    local_16c = puVar2[2];
    puVar2 = *(undefined4 **)(local_190 + 200);
    puVar2 = (undefined4 *)
             FUN_00581f80(local_1e0,local_174,local_170,local_16c,*puVar2,puVar2[1],puVar2[2],
                          local_198);
    local_50 = *puVar2;
    local_4c = puVar2[1];
    local_48 = puVar2[2];
    local_20 = local_50;
    local_1c = local_4c;
    local_18 = local_48;
    puVar2 = (undefined4 *)FUN_00440300(local_1f8,&local_20,local_190 + 0x28);
    local_44 = *puVar2;
    local_40 = puVar2[1];
    local_3c = puVar2[2];
    local_20 = local_44;
    local_1c = local_40;
    local_18 = local_3c;
    puVar2 = (undefined4 *)FUN_00439de0(local_1d4,*(int *)(local_190 + 0x10) + 0x20);
    local_5c = *puVar2;
    local_58 = puVar2[1];
    local_54 = puVar2[2];
    local_2c = local_5c;
    local_28 = local_58;
    local_24 = local_54;
    puVar2 = (undefined4 *)FUN_0081fa10(local_250,&local_5c,&local_20);
    puVar6 = local_128;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar6 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar2 = local_128;
    puVar6 = (undefined4 *)(*(int *)(local_190 + 0x10) + 0x20);
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar6 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar6 = puVar6 + 1;
    }
    FUN_004376c0(*(int *)(local_190 + 8) + 0x58,*(undefined4 *)(local_190 + 0x10),0);
    puVar4 = (uint *)FUN_0081fe60(local_290,*(int *)(local_190 + 0x10) + 0x20,local_190 + 0x28);
    puVar7 = local_168;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar7 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar7 = puVar7 + 1;
    }
    puVar4 = local_168;
    puVar7 = local_a8;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar7 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar7 = puVar7 + 1;
    }
    local_e8 = local_a8[0];
    local_e4 = local_a8[1];
    local_e0 = local_a8[2];
    local_dc = local_90;
    local_d8 = local_8c;
    local_d4 = local_88;
    local_d0 = local_a8[3] ^ 0x80000000;
    local_cc = local_98 ^ 0x80000000;
    local_c8 = local_94 ^ 0x80000000;
    local_c0 = local_80;
    local_b8 = local_78;
    local_b0 = local_70;
    uVar11 = 0;
    uVar10 = 0xffffffff;
    uVar9 = 0;
    uVar5 = FUN_0047e9a0(*(undefined4 *)(local_190 + 0x18),0,0xffffffff,0);
    local_194 = (int *)FUN_004e1190(&local_e8,uVar5,uVar9,uVar10,uVar11);
    if (local_194 != (int *)0x0) {
      uVar5 = FUN_00479f30(*(undefined4 *)(local_190 + 0x18));
      FUN_0046fc40(uVar5);
      if (*(int *)(*(int *)(local_190 + 0xcc) + 0x1c) == 3) {
        *(uint *)(local_194[0x8a] + 0x114) = *(uint *)(local_194[0x8a] + 0x114) | 0xc;
        FUN_004dbe70(3,*(undefined4 *)(local_190 + 200),0,0);
      }
      iVar1 = FUN_00572a70();
      if (iVar1 != 0) {
        FUN_004b8460();
      }
      local_19c = (int *)FUN_0045ca50();
      (**(code **)(*local_19c + 0x1c))(local_194);
      puVar2 = (undefined4 *)FUN_004560b0(local_204,local_a8);
      local_18c = *puVar2;
      local_188 = puVar2[1];
      local_184 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004462d0(local_1ec,local_198,local_18c,local_188,local_184);
      local_68 = *puVar2;
      local_64 = puVar2[1];
      local_60 = puVar2[2];
      FUN_0046fb20(&local_68);
      (**(code **)(*local_194 + 0x3c))(*(undefined4 *)(local_190 + 0xc0));
    }
    *(float *)(local_190 + 0xc0) =
         *(float *)(local_190 + 0xc0) - *(float *)(*(int *)(local_190 + 8) + 0x80);
  }
LAB_00582852:
  *(undefined1 *)(local_190 + 0xd0) = 0;
LAB_0058288e:
  FUN_0083e885();
  return;
}

