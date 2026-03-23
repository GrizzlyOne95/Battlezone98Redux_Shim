
void __fastcall FUN_005a12a0(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_328 [64];
  undefined1 local_2e8 [64];
  undefined1 local_2a8 [64];
  undefined1 local_268 [64];
  undefined1 local_228 [24];
  int local_210;
  int local_20c;
  int local_208;
  undefined4 local_204 [16];
  undefined4 local_1c4 [16];
  undefined4 local_184 [16];
  undefined4 local_144 [16];
  undefined4 local_104 [16];
  undefined4 local_c4 [16];
  undefined4 local_84 [10];
  undefined8 local_5c;
  undefined8 local_54;
  undefined8 local_4c;
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
  local_210 = param_1;
  puVar1 = (undefined4 *)FUN_0081ec40(local_268,*(uint *)(param_1 + 0x280) ^ 0x80000000);
  puVar3 = local_c4;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = local_c4;
  puVar3 = local_104;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  FUN_006819a0(*(undefined4 *)(local_210 + 0xf0),&local_14);
  for (local_20c = 0; local_20c < 5; local_20c = local_20c + 1) {
    local_208 = FUN_00417f60(local_20c);
    if (local_208 != 0) {
      *(undefined4 *)(local_208 + 0x1c) = local_14;
      *(undefined4 *)(local_208 + 0x20) = local_10;
      *(undefined4 *)(local_208 + 0x24) = local_c;
      puVar1 = (undefined4 *)
               FUN_0062e070(local_2e8,*(undefined4 *)(local_208 + 0x14),
                            *(undefined4 *)(local_210 + 0xf4));
      puVar3 = local_144;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = local_144;
      puVar3 = local_84;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      local_4c = 0;
      local_54 = 0;
      local_5c = 0;
      puVar1 = (undefined4 *)FUN_008203f0(local_2a8,local_84);
      puVar3 = local_1c4;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = local_1c4;
      puVar3 = local_204;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = (undefined4 *)FUN_00447f60(local_228,*(int *)(local_208 + 0x10) + 0x20);
      local_44 = *puVar1;
      local_40 = puVar1[1];
      local_3c = puVar1[2];
      local_38 = puVar1[3];
      local_34 = puVar1[4];
      local_30 = puVar1[5];
      local_2c = local_44;
      local_28 = local_40;
      local_24 = local_3c;
      local_20 = local_38;
      local_1c = local_34;
      local_18 = local_30;
      puVar1 = (undefined4 *)FUN_0081fe60(local_328,local_204,local_104);
      puVar3 = local_184;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar1 = local_184;
      puVar3 = (undefined4 *)(*(int *)(local_208 + 0x10) + 0x20);
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
      FUN_0044b7d0(*(int *)(local_208 + 0x10) + 0x20,&local_44);
      FUN_00681a00(*(undefined4 *)(local_208 + 0x10),*(int *)(local_208 + 0x10) + 0x20);
    }
  }
  FUN_0083e885();
  return;
}

