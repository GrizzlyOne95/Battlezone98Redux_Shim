
void __thiscall FUN_0046e1e0(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_1a8 [64];
  undefined1 local_168 [12];
  uint local_15c;
  float local_158;
  uint local_154;
  undefined4 local_150;
  int local_14c;
  int local_148;
  undefined4 *local_144;
  short *local_140;
  undefined4 local_13c [40];
  undefined4 local_9c [16];
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
  local_148 = param_1;
  if (((*(uint *)(*(int *)(param_1 + 0x30) + 0x14) & 0x10) == 0) ||
     (iVar1 = ___scrt_is_user_matherr_present(), iVar1 != 0)) {
    DAT_02ceefc8 = *(undefined8 *)(*(int *)(local_148 + 0x30) + 0x48);
    DAT_02ceefd0 = *(undefined8 *)(*(int *)(local_148 + 0x30) + 0x50);
    DAT_02ceefd8 = *(undefined8 *)(*(int *)(local_148 + 0x30) + 0x58);
    puVar2 = (undefined4 *)FUN_0081fe60(local_1a8,&DAT_02ceefa0,param_2 + 0x40);
    puVar6 = local_13c;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar6 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar2 = local_13c;
    puVar6 = local_9c;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar6 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar6 = puVar6 + 1;
    }
    iVar1 = *(int *)(local_148 + 0x30);
    local_44 = *(undefined4 *)(iVar1 + 0xa0);
    local_40 = *(undefined4 *)(iVar1 + 0xa4);
    local_3c = *(undefined4 *)(iVar1 + 0xa8);
    FUN_00820180(&local_44,&local_44,1,local_9c);
    uVar3 = FUN_008445c0();
    uVar4 = FUN_008445c0();
    uVar5 = FUN_008445c0();
    local_154 = (uVar3 & 0xff) << 0x10 | 0xff000000 | (uVar4 & 0xff) << 8 | uVar5 & 0xff;
    iVar1 = FUN_006895d0(param_2,&local_44,*(undefined4 *)(*(int *)(local_148 + 0x30) + 0xac));
    if (iVar1 < 1) {
      FUN_00820180(&local_38,local_148,4,local_9c);
      puVar2 = (undefined4 *)
               FUN_00440210(local_168,*(int *)(local_148 + 0x30) + 0x38,param_2 + 0x40);
      local_5c = *puVar2;
      local_58 = puVar2[1];
      local_54 = puVar2[2];
      local_50 = local_5c;
      local_4c = local_58;
      local_48 = local_54;
      fVar7 = (float10)FUN_0046e0a0(local_5c,local_54);
      local_158 = (float)fVar7;
      local_15c = (uint)((3.1415927 - local_158) * 1.2732395);
      local_14c = (local_15c & 7) * 0x18 + *(int *)(local_148 + 0x34);
      FUN_006855e0(local_14c,local_3c);
      local_150 = FUN_00685670(4,6);
      local_144 = (undefined4 *)FUN_006856a0(4);
      local_140 = (short *)FUN_006856c0(6);
      puVar2 = (undefined4 *)
               FUN_00446360(local_38,uStack_34,uStack_30,local_154,*(undefined4 *)(local_14c + 8),
                            *(undefined4 *)(local_14c + 0xc));
      *local_144 = *puVar2;
      local_144[1] = puVar2[1];
      local_144[2] = puVar2[2];
      local_144[3] = puVar2[3];
      local_144[4] = puVar2[4];
      local_144[5] = puVar2[5];
      local_144 = local_144 + 6;
      puVar2 = (undefined4 *)
               FUN_00446360(uStack_2c,uStack_28,uStack_24,local_154,
                            *(undefined4 *)(local_14c + 0x10),*(undefined4 *)(local_14c + 0xc));
      *local_144 = *puVar2;
      local_144[1] = puVar2[1];
      local_144[2] = puVar2[2];
      local_144[3] = puVar2[3];
      local_144[4] = puVar2[4];
      local_144[5] = puVar2[5];
      local_144 = local_144 + 6;
      puVar2 = (undefined4 *)
               FUN_00446360(uStack_20,uStack_1c,uStack_18,local_154,
                            *(undefined4 *)(local_14c + 0x10),*(undefined4 *)(local_14c + 0x14));
      *local_144 = *puVar2;
      local_144[1] = puVar2[1];
      local_144[2] = puVar2[2];
      local_144[3] = puVar2[3];
      local_144[4] = puVar2[4];
      local_144[5] = puVar2[5];
      local_144 = local_144 + 6;
      puVar2 = (undefined4 *)
               FUN_00446360(uStack_14,uStack_10,uStack_c,local_154,*(undefined4 *)(local_14c + 8),
                            *(undefined4 *)(local_14c + 0x14));
      *local_144 = *puVar2;
      local_144[1] = puVar2[1];
      local_144[2] = puVar2[2];
      local_144[3] = puVar2[3];
      local_144[4] = puVar2[4];
      local_144[5] = puVar2[5];
      local_144 = local_144 + 6;
      *local_140 = (short)local_150;
      local_140[1] = (short)local_150 + 2;
      local_140[2] = (short)local_150 + 1;
      local_140[3] = (short)local_150;
      local_140[4] = (short)local_150 + 3;
      local_140[5] = (short)local_150 + 2;
      local_140 = local_140 + 6;
      FUN_006856e0();
    }
  }
  FUN_0083e885();
  return;
}

