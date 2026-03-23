
void FUN_00583070(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_8c [12];
  undefined1 local_80 [12];
  undefined1 local_74 [12];
  undefined1 local_68 [12];
  int local_5c;
  int local_58;
  int local_54;
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
  FUN_005fa020();
  fVar3 = (float10)FUN_00417910(*(undefined4 *)(local_54 + 0x68),DAT_0091755c);
  uVar1 = (**(code **)(*(int *)(*(int *)(local_54 + 0x34) + 0x18) + 0xc))((float)fVar3);
  FUN_004b71f0(uVar1);
  if (*(int *)(local_54 + 0x1c) == 8) {
    local_5c = FUN_00462630(*(undefined4 *)(local_54 + 0x3c));
    if (local_5c != 0) {
      fVar3 = (float10)FUN_00417910(*(undefined4 *)(local_54 + 0x6c),DAT_00917578);
      uVar1 = (**(code **)(*(int *)(local_5c + 0x18) + 0xc))((float)fVar3);
      FUN_004b71f0(uVar1);
    }
  }
  if ((*(int *)(local_54 + 0x1c) == 7) && (*(int *)(local_54 + 0x24) != 0)) {
    local_58 = FUN_00462630(*(undefined4 *)(local_54 + 0x3c));
    if (local_58 == 0) {
      local_58 = 0;
    }
    else {
      puVar2 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_54 + 0x34) + 0x18) + 0xc))();
      puVar2 = (undefined4 *)
               (**(code **)(*(int *)(local_58 + 0x18) + 0xc))(*puVar2,puVar2[1],puVar2[2]);
      puVar2 = (undefined4 *)FUN_004401a0(local_68,*puVar2,puVar2[1],puVar2[2]);
      local_50 = *puVar2;
      local_4c = puVar2[1];
      local_48 = puVar2[2];
      local_20 = local_50;
      local_1c = local_4c;
      local_18 = local_48;
      puVar2 = (undefined4 *)FUN_004621a0(local_80,&local_50);
      local_50 = *puVar2;
      local_4c = puVar2[1];
      local_48 = puVar2[2];
      local_38 = local_50;
      local_34 = local_4c;
      local_30 = local_48;
      puVar2 = (undefined4 *)FUN_004462d0(local_74,0x43160000,local_50,local_4c,local_48);
      local_50 = *puVar2;
      local_4c = puVar2[1];
      local_48 = puVar2[2];
      local_14 = local_50;
      local_10 = local_4c;
      local_c = local_48;
      puVar2 = (undefined4 *)
               (**(code **)(*(int *)(*(int *)(local_54 + 0x34) + 0x18) + 0xc))
                         (local_50,local_4c,local_48);
      puVar2 = (undefined4 *)FUN_00440130(local_8c,*puVar2,puVar2[1],puVar2[2]);
      local_44 = *puVar2;
      local_40 = puVar2[1];
      local_3c = puVar2[2];
      local_2c = local_44;
      local_28 = local_40;
      local_24 = local_3c;
      uVar1 = (**(code **)(*(int *)(*(int *)(local_54 + 0x34) + 0x18) + 0xc))
                        (&local_44,DAT_0091755c);
      FUN_004b7150(uVar1);
      uVar1 = (**(code **)(*(int *)(local_58 + 0x18) + 0xc))(DAT_00917560);
      uVar1 = (**(code **)(*(int *)(*(int *)(local_54 + 0x34) + 0x18) + 0xc))(uVar1);
      FUN_004b7150(uVar1);
      local_58 = FUN_00462630(*(undefined4 *)(local_54 + 0x28));
      if (local_58 != 0) {
        uVar1 = (**(code **)(*(int *)(local_58 + 0x18) + 0xc))(DAT_00917560);
        uVar1 = (**(code **)(*(int *)(*(int *)(local_54 + 0x34) + 0x18) + 0xc))(uVar1);
        FUN_004b7150(uVar1);
      }
    }
  }
  FUN_0083e885();
  return;
}

