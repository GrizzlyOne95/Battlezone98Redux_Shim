
void __fastcall FUN_006057e0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  float10 fVar4;
  undefined1 local_124 [12];
  undefined1 local_118 [12];
  undefined1 local_10c [12];
  undefined1 local_100 [12];
  undefined1 local_f4 [12];
  undefined1 local_e8 [12];
  undefined1 local_dc [12];
  undefined1 local_d0 [12];
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float *local_a0;
  int local_9c;
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
  iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
  local_a0 = (float *)(iVar1 + 0xc4);
  local_9c = param_1;
  if (*(int *)(*(int *)(param_1 + 0x10) + 0x228) == 0) {
    puVar2 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
    local_14 = *puVar2;
    local_10 = puVar2[1];
    local_c = puVar2[2];
    puVar2 = (undefined4 *)FUN_00440000(local_d0,0,0,0);
    local_74 = *puVar2;
    local_70 = puVar2[1];
    local_6c = puVar2[2];
    local_38 = local_74;
    local_34 = local_70;
    local_30 = local_6c;
    if (*(float *)(local_9c + 0xd4) <= *(float *)(local_9c + 0x9c) &&
        *(float *)(local_9c + 0x9c) != *(float *)(local_9c + 0xd4)) {
      uVar3 = FUN_0045c4d0();
      puVar2 = (undefined4 *)FUN_00440210(local_e8,local_9c + 0xd8,uVar3);
      local_80 = *puVar2;
      local_7c = puVar2[1];
      local_78 = puVar2[2];
      local_20 = local_80;
      local_1c = local_7c;
      local_18 = local_78;
      puVar2 = (undefined4 *)
               FUN_00439d00(local_118,local_74,local_70,local_6c,
                            (1.0 - *(float *)(local_9c + 0xd4) / *(float *)(local_9c + 0x9c)) *
                            -40.0,local_80,local_7c,local_78);
      local_74 = *puVar2;
      local_70 = puVar2[1];
      local_6c = puVar2[2];
      local_2c = local_74;
      local_28 = local_70;
      local_24 = local_6c;
    }
    FUN_00465320(*(undefined4 *)(local_9c + 0x10),*(undefined4 *)(local_9c + 0x80),0x42200000,
                 local_14,local_10,local_c,&local_74,0);
    FUN_004675f0(*(undefined4 *)(local_9c + 0x10),&local_14,0x42200000,&local_74);
    if (4.0 <= *(float *)(local_9c + 0x98)) {
      puVar2 = (undefined4 *)
               FUN_005fd5f0(local_100,*(undefined4 *)(local_9c + 0x10),
                            *(undefined4 *)(local_9c + 0x124),local_9c + 0x124);
      local_8c = *puVar2;
      local_88 = puVar2[1];
      local_84 = puVar2[2];
      local_50 = local_8c;
      local_4c = local_88;
      local_48 = local_84;
      fVar4 = (float10)FUN_00822d60();
      local_c0 = (float)fVar4;
      puVar2 = (undefined4 *)
               FUN_004401a0(local_dc,local_8c,local_88,local_84,*(undefined4 *)(local_9c + 0x128),
                            *(undefined4 *)(local_9c + 300),*(undefined4 *)(local_9c + 0x130));
      local_98 = *puVar2;
      local_94 = puVar2[1];
      local_90 = puVar2[2];
      puVar2 = (undefined4 *)
               FUN_00439d00(local_f4,*(undefined4 *)(local_9c + 0x128),
                            *(undefined4 *)(local_9c + 300),*(undefined4 *)(local_9c + 0x130),
                            local_c0 * 2.0,local_98,local_94,local_90);
      local_5c = *puVar2;
      local_58 = puVar2[1];
      local_54 = puVar2[2];
      *(undefined4 *)(local_9c + 0x128) = local_5c;
      *(undefined4 *)(local_9c + 300) = local_58;
      *(undefined4 *)(local_9c + 0x130) = local_54;
      puVar2 = (undefined4 *)
               FUN_00440130(local_10c,local_74,local_70,local_6c,*(undefined4 *)(local_9c + 0x128),
                            *(undefined4 *)(local_9c + 300),*(undefined4 *)(local_9c + 0x130));
      local_74 = *puVar2;
      local_70 = puVar2[1];
      local_6c = puVar2[2];
      local_44 = local_74;
      local_40 = local_70;
      local_3c = local_6c;
    }
    puVar2 = (undefined4 *)
             FUN_004462d0(local_124,*(float *)(local_9c + 0x98) * 0.5 - 0.5,
                          *(undefined4 *)(local_9c + 0xe4),*(undefined4 *)(local_9c + 0xe8),
                          *(undefined4 *)(local_9c + 0xec));
    local_68 = *puVar2;
    local_64 = puVar2[1];
    local_60 = puVar2[2];
    FUN_00607110(local_9c + 200,&local_68);
    FUN_00606f70(&local_74);
    fVar4 = (float10)FUN_0045c420(*(undefined4 *)(local_9c + 0x4c),*(undefined4 *)(local_9c + 0x50),
                                  *(undefined4 *)(local_9c + 0x54));
    local_ac = (float)fVar4;
    if (local_ac < 5.0) {
      local_a0[3] = 0.0;
      local_a0[2] = 0.0;
    }
  }
  else {
    *(undefined4 *)(iVar1 + 0xd0) = 0;
    *(undefined4 *)(iVar1 + 0xd4) = 0;
    *(undefined4 *)(iVar1 + 0xcc) = 0;
    fVar4 = (float10)FUN_00447ed0(-*(float *)(param_1 + 0xd8) * *(float *)(param_1 + 0x6c),
                                  0xbf800000,0x3f800000);
    *local_a0 = (float)fVar4;
    local_b8 = *(float *)(local_9c + 0xdc) * 4.0;
    fVar4 = (float10)FUN_00822d60(0xbf800000,0x3f800000);
    local_b0 = (float)fVar4;
    fVar4 = (float10)FUN_00447ed0(local_b8 * local_b0 + *(float *)(local_9c + 0xb0));
    *(float *)(local_9c + 0xb0) = (float)fVar4;
    local_a0[1] = *(float *)(local_9c + 0xb0);
  }
  if (*(float *)(local_9c + 0x98) <= 4.0 && *(float *)(local_9c + 0x98) != 4.0) {
    fVar4 = (float10)FUN_00822d80();
    local_bc = (float)fVar4;
    local_a4 = local_bc * 0.5;
    local_a8 = 0.1 - *(float *)(local_9c + 0x98) * 0.025;
    fVar4 = (float10)FUN_00822970(local_a4,0xbf800000,0x3f800000);
    local_c4 = (float)fVar4;
    fVar4 = (float10)FUN_00447ed0(local_c4 * local_a8 + local_a0[1]);
    local_a0[1] = (float)fVar4;
    fVar4 = (float10)FUN_00822970(local_a4 + 25.734,0xbf800000,0x3f800000);
    local_b4 = (float)fVar4;
    fVar4 = (float10)FUN_00447ed0(local_b4 * local_a8 + *local_a0);
    *local_a0 = (float)fVar4;
  }
  FUN_0083e885();
  return;
}

