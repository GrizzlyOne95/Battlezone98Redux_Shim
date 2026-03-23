
void __fastcall FUN_005f0930(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_36c [64];
  undefined1 local_32c [64];
  undefined1 local_2ec [64];
  undefined1 local_2ac [64];
  undefined1 local_26c [24];
  undefined1 local_254 [24];
  int local_23c;
  int local_238;
  int local_234;
  int local_230;
  int local_22c;
  undefined4 local_228 [16];
  undefined4 local_1e8 [16];
  undefined4 local_1a8 [16];
  undefined4 local_168 [16];
  undefined4 local_128 [16];
  undefined4 local_e8 [16];
  undefined4 local_a8 [10];
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
  local_234 = param_1;
  if (*(int *)(param_1 + 700) < 1) {
    puVar1 = (undefined4 *)FUN_0081ec40(local_32c,*(uint *)(param_1 + 0x280) ^ 0x80000000);
    puVar3 = local_e8;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_e8;
    puVar3 = local_228;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    for (local_23c = 0; local_23c < 5; local_23c = local_23c + 1) {
      local_22c = FUN_00417f60(local_23c);
      if (local_22c != 0) {
        puVar1 = (undefined4 *)
                 FUN_0062e070(local_2ac,*(undefined4 *)(local_22c + 0x14),
                              *(undefined4 *)(local_234 + 0xf4));
        puVar3 = local_128;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar1 = local_128;
        puVar3 = local_a8;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        local_70 = 0;
        local_78 = 0;
        local_80 = 0;
        puVar1 = (undefined4 *)FUN_008203f0(local_2ec,local_a8);
        puVar3 = local_1a8;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar1 = local_1a8;
        puVar3 = local_168;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar1 = (undefined4 *)FUN_00447f60(local_254,*(int *)(local_22c + 0x10) + 0x20);
        local_68 = *puVar1;
        local_64 = puVar1[1];
        local_60 = puVar1[2];
        local_5c = puVar1[3];
        local_58 = puVar1[4];
        local_54 = puVar1[5];
        local_20 = local_68;
        local_1c = local_64;
        local_18 = local_60;
        local_14 = local_5c;
        local_10 = local_58;
        local_c = local_54;
        puVar1 = (undefined4 *)FUN_0081fe60(local_36c,local_168,local_228);
        puVar3 = local_1e8;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar1 = local_1e8;
        puVar3 = (undefined4 *)(*(int *)(local_22c + 0x10) + 0x20);
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        FUN_00681a00(*(undefined4 *)(local_22c + 0x10),*(int *)(local_22c + 0x10) + 0x20);
        FUN_0044b7d0(*(int *)(local_22c + 0x10) + 0x20,&local_68);
      }
    }
  }
  else {
    for (local_238 = 0; local_238 < 5; local_238 = local_238 + 1) {
      local_230 = FUN_00417f60(local_238);
      if (local_230 != 0) {
        puVar1 = (undefined4 *)FUN_00447f60(local_26c,*(int *)(local_230 + 0x10) + 0x20);
        local_50 = *puVar1;
        local_4c = puVar1[1];
        local_48 = puVar1[2];
        local_44 = puVar1[3];
        local_40 = puVar1[4];
        local_3c = puVar1[5];
        puVar1 = &DAT_008fe1e0;
        puVar3 = (undefined4 *)(*(int *)(local_230 + 0x10) + 0x20);
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        local_38 = local_50;
        local_34 = local_4c;
        local_30 = local_48;
        local_2c = local_44;
        local_28 = local_40;
        local_24 = local_3c;
        FUN_00681a00(*(undefined4 *)(local_230 + 0x10),*(int *)(local_230 + 0x10) + 0x20);
        FUN_0044b7d0(*(int *)(local_230 + 0x10) + 0x20,&local_50);
      }
    }
  }
  FUN_0083e885();
  return;
}

