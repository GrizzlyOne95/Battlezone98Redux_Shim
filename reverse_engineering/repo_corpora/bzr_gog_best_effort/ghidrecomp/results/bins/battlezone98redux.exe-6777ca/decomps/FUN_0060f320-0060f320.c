
void __fastcall FUN_0060f320(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_494 [64];
  undefined1 local_454 [64];
  undefined1 local_414 [64];
  undefined1 local_3d4 [64];
  undefined1 local_394 [64];
  undefined1 local_354 [64];
  undefined1 local_314 [24];
  undefined1 local_2fc [12];
  float local_2f0;
  int local_2ec;
  int local_2e8;
  int local_2e4;
  int local_2e0;
  undefined4 local_2dc [16];
  undefined4 local_29c [16];
  undefined4 local_25c [16];
  undefined4 local_21c [16];
  undefined4 local_1dc [16];
  undefined4 local_19c [16];
  undefined4 local_15c [16];
  undefined4 local_11c [16];
  undefined4 local_dc [10];
  double local_b4;
  double local_a4;
  undefined4 local_9c [10];
  undefined8 local_74;
  undefined8 local_6c;
  undefined8 local_64;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38 [3];
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
  local_2e4 = param_1;
  puVar1 = (undefined4 *)FUN_0081ec40(local_3d4,*(uint *)(param_1 + 0x280) ^ 0x80000000);
  puVar3 = local_15c;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = local_15c;
  puVar3 = local_11c;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  for (local_2e8 = 0; local_2e8 < 5; local_2e8 = local_2e8 + 1) {
    local_2e0 = FUN_00417f60(local_2e8);
    if (local_2e0 != 0) {
      puVar1 = (undefined4 *)
               FUN_0062e070(local_354,*(undefined4 *)(local_2e0 + 0x14),
                            *(undefined4 *)(local_2e4 + 0xf4));
      puVar3 = local_19c;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = local_19c;
      puVar3 = local_dc;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = (undefined4 *)FUN_008203f0(local_454,local_dc);
      puVar3 = local_21c;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = local_21c;
      puVar3 = local_9c;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      local_64 = 0;
      local_6c = 0;
      local_74 = 0;
      puVar1 = (undefined4 *)FUN_00447f60(local_314,*(int *)(local_2e0 + 0x10) + 0x20);
      local_5c = *puVar1;
      local_58 = puVar1[1];
      local_54 = puVar1[2];
      local_50 = puVar1[3];
      local_4c = puVar1[4];
      local_48 = puVar1[5];
      local_20 = local_5c;
      local_1c = local_58;
      local_18 = local_54;
      local_14 = local_50;
      local_10 = local_4c;
      local_c = local_48;
      puVar1 = (undefined4 *)FUN_0081fe60(local_394,local_9c,local_11c);
      puVar3 = local_2dc;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = local_2dc;
      puVar3 = (undefined4 *)(*(int *)(local_2e0 + 0x10) + 0x20);
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      FUN_0044b7d0(*(int *)(local_2e0 + 0x10) + 0x20,&local_5c);
      local_2ec = FUN_00462610();
      if (local_2ec != 0) {
        puVar1 = (undefined4 *)FUN_00440000(local_2fc,0,0,0);
        local_44 = *puVar1;
        local_40 = puVar1[1];
        local_3c = puVar1[2];
        local_38[0] = (float)-local_b4;
        local_38[1] = 0.0;
        local_2c = local_44;
        local_28 = local_40;
        local_24 = local_3c;
        puVar1 = (undefined4 *)(**(code **)(*(int *)(local_2ec + 0x18) + 0xc))();
        puVar1 = (undefined4 *)
                 (**(code **)(*(int *)(local_2e4 + 0x18) + 0xc))(*puVar1,puVar1[1],puVar1[2]);
        fVar4 = (float10)FUN_004976f0(*puVar1,puVar1[1],puVar1[2]);
        local_2f0 = (float)fVar4;
        local_38[2] = local_2f0 - (float)local_a4;
        puVar1 = (undefined4 *)FUN_0081fa10(local_414,&local_44,local_38);
        puVar3 = local_29c;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar1 = local_29c;
        puVar3 = local_25c;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar1 = (undefined4 *)FUN_0081fe60(local_494,local_25c,*(int *)(local_2e0 + 0x10) + 0x20);
        puVar3 = local_1dc;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar1 = local_1dc;
        puVar3 = (undefined4 *)(*(int *)(local_2e0 + 0x10) + 0x20);
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
      }
      FUN_00681a00(*(undefined4 *)(local_2e0 + 0x10),*(int *)(local_2e0 + 0x10) + 0x20);
    }
  }
  FUN_0083e885();
  return;
}

