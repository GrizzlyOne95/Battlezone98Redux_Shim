
void __thiscall FUN_004e1d90(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_268 [64];
  undefined1 local_228 [64];
  undefined1 local_1e8 [24];
  undefined1 local_1d0 [24];
  undefined1 local_1b8 [24];
  int local_1a0;
  int local_19c;
  undefined4 local_198;
  int local_194;
  int *local_190;
  undefined4 local_18c [16];
  undefined4 local_14c [16];
  undefined4 local_10c [16];
  undefined4 local_cc [16];
  float local_8c;
  float local_88;
  float local_84;
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
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1a0 = param_2;
  local_194 = param_1;
  if (param_2 != 4) {
    FUN_00583430(param_2);
    goto LAB_004e20cc;
  }
  local_190 = (int *)(param_1 + 100);
  puVar1 = (undefined4 *)
           FUN_0062e070(local_228,*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x34) + 0x230) + 0xfc)
                        ,0);
  puVar4 = local_10c;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar1 = local_10c;
  puVar4 = local_18c;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar1 = (undefined4 *)FUN_00447f60(local_1b8,local_18c);
  local_68 = *puVar1;
  local_64 = puVar1[1];
  local_60 = puVar1[2];
  local_5c = puVar1[3];
  local_58 = puVar1[4];
  local_54 = puVar1[5];
  local_20 = local_68;
  uStack_1c = local_64;
  local_18 = local_60;
  uStack_14 = local_5c;
  local_10 = local_58;
  uStack_c = local_54;
  uVar2 = (**(code **)(*(int *)(*local_190 + 0x18) + 0x30))();
  iVar3 = FUN_00417e20(uVar2);
  if (iVar3 == 0) {
    uVar2 = (**(code **)(*(int *)(*local_190 + 0x18) + 0x30))();
    iVar3 = FUN_00462340(uVar2);
    if (iVar3 != 0) goto LAB_004e1ecd;
    puVar1 = (undefined4 *)(**(code **)(*(int *)(*local_190 + 0x18) + 0xc))();
    puVar1 = (undefined4 *)FUN_0049c4f0(local_1d0,*puVar1,puVar1[1],puVar1[2]);
    local_80 = *puVar1;
    local_7c = puVar1[1];
    local_78 = puVar1[2];
    local_74 = puVar1[3];
    local_70 = puVar1[4];
    local_6c = puVar1[5];
    local_38 = local_80;
    uStack_34 = local_7c;
    local_30 = local_78;
    uStack_2c = local_74;
    local_28 = local_70;
    uStack_24 = local_6c;
  }
  else {
LAB_004e1ecd:
    local_19c = *local_190;
    puVar1 = (undefined4 *)
             FUN_0062e070(local_268,*(undefined4 *)(*(int *)(local_19c + 0x230) + 0xfc),0);
    puVar4 = local_14c;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar1 = local_14c;
    puVar4 = local_cc;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar1 = (undefined4 *)FUN_00447f60(local_1e8,local_cc);
    local_50 = *puVar1;
    local_4c = puVar1[1];
    local_48 = puVar1[2];
    local_44 = puVar1[3];
    local_40 = puVar1[4];
    local_3c = puVar1[5];
    local_38 = local_50;
    uStack_34 = local_4c;
    local_30 = local_48;
    uStack_2c = local_44;
    local_28 = local_40;
    uStack_24 = local_3c;
  }
  local_8c = (float)((double)CONCAT44(uStack_34,local_38) - (double)CONCAT44(uStack_1c,local_20));
  local_88 = (float)((double)CONCAT44(uStack_2c,local_30) - (double)CONCAT44(uStack_14,local_18));
  local_84 = (float)((double)CONCAT44(uStack_24,local_28) - (double)CONCAT44(uStack_c,local_10));
  local_198 = 0x3f800000;
  FUN_00784620(local_20,uStack_1c,local_18,uStack_14,local_10,uStack_c,local_8c,local_88,local_84,
               &local_198,0);
LAB_004e20cc:
  FUN_0083e885();
  return;
}

