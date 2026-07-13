
void FUN_00606980(void)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_12c [24];
  undefined1 local_114 [24];
  undefined1 local_fc [12];
  undefined1 local_f0 [24];
  undefined1 local_d8 [24];
  undefined8 local_c0;
  float local_b8;
  undefined8 local_b4;
  undefined4 local_ac;
  int local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
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
  local_c0 = FUN_008205a0();
  local_b4 = local_c0;
  local_ac = FUN_0045c4d0();
  puVar1 = (undefined4 *)FUN_00439d80();
  local_a4 = *puVar1;
  local_a0 = puVar1[1];
  local_9c = puVar1[2];
  puVar1 = (undefined4 *)FUN_004560b0();
  local_98 = *puVar1;
  local_94 = puVar1[1];
  local_90 = puVar1[2];
  puVar1 = (undefined4 *)FUN_00459570(local_f0,local_b4._4_4_,local_98,local_94);
  local_74 = *puVar1;
  local_70 = puVar1[1];
  local_6c = puVar1[2];
  local_2c = local_74;
  local_28 = local_70;
  local_24 = local_6c;
  puVar1 = (undefined4 *)FUN_004462d0();
  local_68 = *puVar1;
  local_64 = puVar1[1];
  local_60 = puVar1[2];
  local_44 = local_68;
  local_40 = local_64;
  local_3c = local_60;
  puVar1 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_a8 + 0x10) + 0x18) + 0xc))();
  puVar1 = (undefined4 *)FUN_00440130(local_d8,*puVar1);
  local_50 = *puVar1;
  local_4c = puVar1[1];
  local_48 = puVar1[2];
  local_14 = local_50;
  local_10 = local_4c;
  local_c = local_48;
  FUN_00465320(*(undefined4 *)(local_a8 + 0x10),*(undefined4 *)(local_a8 + 0x80),0x42200000);
  FUN_004675f0();
  if (4.0 <= *(float *)(local_a8 + 0x98)) {
    puVar1 = (undefined4 *)FUN_005fd5f0();
    local_80 = *puVar1;
    local_7c = puVar1[1];
    local_78 = puVar1[2];
    local_20 = local_80;
    local_1c = local_7c;
    local_18 = local_78;
    fVar2 = (float10)FUN_00822d60();
    local_b8 = (float)fVar2;
    puVar1 = (undefined4 *)FUN_004401a0(local_fc,local_80);
    local_8c = *puVar1;
    local_88 = puVar1[1];
    local_84 = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_00439d00(local_114,*(undefined4 *)(local_a8 + 0x128),
                          *(undefined4 *)(local_a8 + 300));
    local_5c = *puVar1;
    local_58 = puVar1[1];
    local_54 = puVar1[2];
    *(undefined4 *)(local_a8 + 0x128) = local_5c;
    *(undefined4 *)(local_a8 + 300) = local_58;
    *(undefined4 *)(local_a8 + 0x130) = local_54;
    puVar1 = (undefined4 *)FUN_00440130(local_12c,local_68);
    local_68 = *puVar1;
    local_64 = puVar1[1];
    local_60 = puVar1[2];
    local_38 = local_68;
    local_34 = local_64;
    local_30 = local_60;
  }
  FUN_00607320();
  FUN_00606f70();
  FUN_0083e885();
  return;
}

