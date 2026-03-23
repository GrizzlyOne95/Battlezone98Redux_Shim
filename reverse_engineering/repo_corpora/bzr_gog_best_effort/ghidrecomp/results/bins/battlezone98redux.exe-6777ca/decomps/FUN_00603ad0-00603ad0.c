
void __fastcall FUN_00603ad0(int param_1)

{
  float *pfVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_494 [64];
  undefined1 local_454 [64];
  undefined1 local_414 [64];
  undefined1 local_3d4 [64];
  undefined1 local_394 [64];
  undefined1 local_354 [64];
  undefined1 local_314 [24];
  undefined1 local_2fc [24];
  undefined1 local_2e4 [12];
  undefined1 local_2d8 [24];
  undefined1 local_2c0 [12];
  undefined4 local_2b4;
  float local_2b0;
  uint local_2ac;
  int local_2a8;
  undefined4 local_2a4 [16];
  undefined4 local_264 [16];
  undefined4 local_224 [16];
  undefined4 local_1e4 [16];
  undefined4 local_1a4 [16];
  undefined4 local_164 [16];
  undefined4 local_124 [16];
  undefined1 local_e4 [12];
  undefined4 local_d8 [16];
  float local_98;
  float local_94;
  float local_90;
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
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_2a8 = param_1;
  if (*(int *)(param_1 + 0x18) != 0) {
    if (*(int *)(param_1 + 0xb4) == 0) {
      pfVar1 = (float *)(**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
      local_2c = *pfVar1;
      local_28 = pfVar1[1];
      local_24 = pfVar1[2];
      puVar2 = (undefined4 *)
               FUN_0062e070(local_454,
                            *(undefined4 *)(*(int *)(*(int *)(local_2a8 + 0x10) + 0x230) + 0xfc),0);
      puVar4 = local_224;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = local_224;
      puVar4 = local_124;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = (undefined4 *)FUN_00447f60(local_2fc,local_124);
      local_44 = *puVar2;
      local_40 = puVar2[1];
      local_3c = puVar2[2];
      local_38 = puVar2[3];
      local_34 = puVar2[4];
      local_30 = puVar2[5];
      local_20 = local_44;
      uStack_1c = local_40;
      local_18 = local_3c;
      uStack_14 = local_38;
      local_10 = local_34;
      uStack_c = local_30;
      puVar2 = (undefined4 *)
               FUN_0081ec40(local_3d4,
                            *(float *)(*(int *)(*(int *)(local_2a8 + 0x10) + 0x230) + 200) * -0.5);
      puVar4 = local_2a4;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = local_2a4;
      puVar4 = local_d8;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = (undefined4 *)FUN_0081fe60(local_354,local_d8,local_124);
      puVar4 = local_264;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = local_264;
      puVar4 = local_d8;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = (undefined4 *)FUN_008203f0(local_394,local_d8);
      puVar4 = local_1e4;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = local_1e4;
      puVar4 = local_d8;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
    }
    else {
      pfVar1 = (float *)(**(code **)(**(int **)(param_1 + 0xb4) + 0x2c))
                                  (local_e4,*(undefined4 *)(param_1 + 0x18));
      local_2c = *pfVar1;
      local_28 = pfVar1[1];
      local_24 = pfVar1[2];
      puVar2 = (undefined4 *)FUN_00447f60(local_314,*(int *)(local_2a8 + 0xb4) + 0x28);
      local_8c = *puVar2;
      local_88 = puVar2[1];
      local_84 = puVar2[2];
      local_80 = puVar2[3];
      local_7c = puVar2[4];
      local_78 = puVar2[5];
      local_20 = local_8c;
      uStack_1c = local_88;
      local_18 = local_84;
      uStack_14 = local_80;
      local_10 = local_7c;
      uStack_c = local_78;
      puVar2 = (undefined4 *)
               FUN_0081fe60(local_414,*(int *)(*(int *)(local_2a8 + 0xb4) + 0x10) + 0x20,
                            *(int *)(local_2a8 + 0xb4) + 0x28);
      puVar4 = local_1a4;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = local_1a4;
      puVar4 = local_d8;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = (undefined4 *)FUN_008203f0(local_494,local_d8);
      puVar4 = local_164;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = local_164;
      puVar4 = local_d8;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
    }
    FUN_00820180();
    fVar5 = (float10)FUN_004428b0(local_2a8 + 200,local_2a8 + 200);
    *(float *)(local_2a8 + 0xd4) = (float)fVar5;
    if (*(float *)(local_2a8 + 0xd4) <= 0.0) {
      puVar2 = (undefined4 *)FUN_00440000();
      local_74 = *puVar2;
      local_70 = puVar2[1];
      local_6c = puVar2[2];
      *(undefined4 *)(local_2a8 + 0xd8) = local_74;
      *(undefined4 *)(local_2a8 + 0xdc) = local_70;
      *(undefined4 *)(local_2a8 + 0xe0) = local_6c;
    }
    else {
      fVar5 = (float10)FUN_00820570((double)*(float *)(local_2a8 + 0xd4),
                                    *(undefined4 *)(local_2a8 + 200),
                                    *(undefined4 *)(local_2a8 + 0xcc),
                                    *(undefined4 *)(local_2a8 + 0xd0));
      local_2b0 = (float)fVar5;
      puVar2 = (undefined4 *)FUN_004462d0(local_2d8,local_2b0);
      local_5c = *puVar2;
      local_58 = puVar2[1];
      local_54 = puVar2[2];
      *(undefined4 *)(local_2a8 + 0xd8) = local_5c;
      *(undefined4 *)(local_2a8 + 0xdc) = local_58;
      *(undefined4 *)(local_2a8 + 0xe0) = local_54;
    }
    puVar2 = (undefined4 *)FUN_004624b0();
    puVar2 = (undefined4 *)FUN_004624b0(*puVar2,puVar2[1],puVar2[2]);
    puVar2 = (undefined4 *)FUN_004401a0(local_2e4,*puVar2,puVar2[1],puVar2[2]);
    local_68 = *puVar2;
    local_64 = puVar2[1];
    local_60 = puVar2[2];
    *(undefined4 *)(local_2a8 + 0xe4) = local_68;
    *(undefined4 *)(local_2a8 + 0xe8) = local_64;
    *(undefined4 *)(local_2a8 + 0xec) = local_60;
    puVar2 = (undefined4 *)FUN_00440210(local_2c0,local_2a8 + 0xe4,local_d8);
    local_50 = *puVar2;
    local_4c = puVar2[1];
    local_48 = puVar2[2];
    *(undefined4 *)(local_2a8 + 0xe4) = local_50;
    *(undefined4 *)(local_2a8 + 0xe8) = local_4c;
    *(undefined4 *)(local_2a8 + 0xec) = local_48;
    if (*(float *)(local_2a8 + 0xd4) < *(float *)(local_2a8 + 0xa0) ||
        *(float *)(local_2a8 + 0xd4) == *(float *)(local_2a8 + 0xa0)) {
      local_98 = (float)((double)local_2c - (double)CONCAT44(uStack_1c,local_20));
      local_94 = (float)((double)local_28 - (double)CONCAT44(uStack_14,local_18));
      local_90 = (float)((double)local_24 - (double)CONCAT44(uStack_c,local_10));
      local_2b4 = 0x3f800000;
      iVar3 = FUN_00784620(local_20,uStack_1c,local_18,uStack_14,local_10,uStack_c,local_98,local_94
                           ,local_90,&local_2b4,0);
      local_2ac = (uint)(iVar3 == 0);
    }
  }
  FUN_0083e885();
  return;
}

