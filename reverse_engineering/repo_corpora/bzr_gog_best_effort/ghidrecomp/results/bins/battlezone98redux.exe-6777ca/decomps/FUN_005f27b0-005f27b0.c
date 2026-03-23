
void __thiscall FUN_005f27b0(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_31c [64];
  undefined1 local_2dc [64];
  undefined1 local_29c [64];
  undefined1 local_25c [64];
  undefined1 local_21c [24];
  int local_204;
  int local_200;
  int local_1fc;
  undefined4 local_1f8 [16];
  undefined4 local_1b8 [16];
  undefined4 local_178 [16];
  undefined4 local_138 [16];
  undefined4 local_f8 [16];
  undefined4 local_b8 [16];
  undefined4 local_78 [10];
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
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
  local_200 = param_1;
  if ((*(int *)(param_1 + 800) < 1) || (*(int *)(param_1 + 0x228) == 0)) {
    FUN_004eb590(param_2);
  }
  else {
    puVar1 = (undefined4 *)FUN_0081ec40(local_2dc,*(uint *)(param_1 + 0x280) ^ 0x80000000);
    puVar3 = local_138;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_138;
    puVar3 = local_1b8;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    for (local_204 = 0; local_204 < 5; local_204 = local_204 + 1) {
      local_1fc = FUN_00417f60(local_204);
      if (local_1fc != 0) {
        puVar1 = (undefined4 *)
                 FUN_0062e070(local_25c,*(undefined4 *)(local_1fc + 0x14),
                              *(undefined4 *)(local_200 + 0xf4));
        puVar3 = local_b8;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar1 = local_b8;
        puVar3 = local_1f8;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar1 = (undefined4 *)FUN_008203f0(local_29c,local_1f8);
        puVar3 = local_f8;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar1 = local_f8;
        puVar3 = local_78;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        local_40 = 0;
        local_48 = 0;
        local_50 = 0;
        puVar1 = (undefined4 *)FUN_00447f60(local_21c,*(int *)(local_1fc + 0x10) + 0x20);
        local_38 = *puVar1;
        local_34 = puVar1[1];
        local_30 = puVar1[2];
        local_2c = puVar1[3];
        local_28 = puVar1[4];
        local_24 = puVar1[5];
        local_20 = local_38;
        local_1c = local_34;
        local_18 = local_30;
        local_14 = local_2c;
        local_10 = local_28;
        local_c = local_24;
        puVar1 = (undefined4 *)FUN_0081fe60(local_31c,local_78,local_1b8);
        puVar3 = local_178;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar1 = local_178;
        puVar3 = (undefined4 *)(*(int *)(local_1fc + 0x10) + 0x20);
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        FUN_0044b7d0(*(int *)(local_1fc + 0x10) + 0x20,&local_38);
        FUN_00681a00(*(undefined4 *)(local_1fc + 0x10),*(int *)(local_1fc + 0x10) + 0x20);
      }
    }
  }
  FUN_0083e885();
  return;
}

