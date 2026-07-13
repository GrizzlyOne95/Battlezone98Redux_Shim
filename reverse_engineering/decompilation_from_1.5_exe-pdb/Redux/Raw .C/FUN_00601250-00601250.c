
void __fastcall FUN_00601250(int *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  float10 fVar4;
  undefined1 local_dc [12];
  undefined1 local_d0 [12];
  undefined1 local_c4 [12];
  undefined1 local_b8 [12];
  float local_ac;
  float local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  float local_9c;
  undefined4 *local_98;
  undefined4 local_94;
  uint local_90;
  float local_8c;
  int *local_88;
  char local_81;
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
  local_88 = param_1;
  if (*(int *)(param_1[0x10] + 4) + -1 <= param_1[0x11]) goto LAB_006016ef;
  puVar2 = (undefined4 *)(**(code **)(*(int *)(param_1[4] + 0x18) + 0xc))();
  local_68 = *puVar2;
  local_60 = puVar2[2];
  local_64 = 0;
  puVar2 = (undefined4 *)
           FUN_004e5270(local_b8,*(undefined4 *)(*(int *)(local_88[0x10] + 8) + local_88[0x11] * 8),
                        *(undefined4 *)(*(int *)(local_88[0x10] + 8) + 4 + local_88[0x11] * 8));
  local_74 = *puVar2;
  local_70 = puVar2[1];
  local_6c = puVar2[2];
  local_2c = local_74;
  local_28 = local_70;
  local_24 = local_6c;
  fVar4 = (float10)FUN_00462010(&local_68,&local_74);
  local_9c = (float)fVar4;
  if ((float)local_88[0x3f] * (float)local_88[0x3f] <= local_9c) {
LAB_006013b2:
    local_94 = 0;
  }
  else {
    uVar3 = (**(code **)(*(int *)(local_88[4] + 0x18) + 4))();
    cVar1 = FUN_00466290(local_68,local_60,local_74,local_6c,uVar3);
    if (cVar1 == '\0') goto LAB_006013b2;
    local_94 = 1;
  }
  local_81 = (char)local_94;
  if (((char)local_94 == '\0') && (0 < local_88[0x11])) {
    puVar2 = (undefined4 *)
             FUN_004e5270(local_d0,*(undefined4 *)
                                    (*(int *)(local_88[0x10] + 8) + -8 + local_88[0x11] * 8),
                          *(undefined4 *)(*(int *)(local_88[0x10] + 8) + -4 + local_88[0x11] * 8));
    local_80 = *puVar2;
    local_7c = puVar2[1];
    local_78 = puVar2[2];
    local_20 = local_80;
    local_1c = local_7c;
    local_18 = local_78;
    puVar2 = (undefined4 *)
             FUN_004401a0(local_c4,local_74,local_70,local_6c,local_80,local_7c,local_78);
    local_50 = *puVar2;
    local_4c = puVar2[1];
    local_48 = puVar2[2];
    local_14 = local_50;
    local_10 = local_4c;
    local_c = local_48;
    puVar2 = (undefined4 *)
             FUN_004401a0(local_dc,local_68,local_64,local_60,local_74,local_70,local_6c);
    local_5c = *puVar2;
    local_58 = puVar2[1];
    local_54 = puVar2[2];
    local_38 = local_5c;
    local_34 = local_58;
    local_30 = local_54;
    fVar4 = (float10)FUN_004428b0(&local_50,&local_5c);
    local_ac = (float)fVar4;
    if (0.0 <= local_ac) {
      local_81 = '\x01';
    }
  }
  if ((local_81 == '\0') && (local_88[0x1f] != 0)) {
    puVar2 = (undefined4 *)(**(code **)(*(int *)(local_88[0x1f] + 0x18) + 0xc))();
    local_44 = *puVar2;
    local_3c = puVar2[2];
    local_40 = 0;
    fVar4 = (float10)FUN_00462470();
    local_8c = (float)fVar4;
    fVar4 = (float10)FUN_00462010(&local_44,&local_74);
    local_a8 = (float)fVar4;
    local_81 = local_a8 < local_8c * local_8c;
    local_90 = (uint)(byte)local_81;
  }
  if (local_81 == '\0') {
    local_81 = FUN_00466d40(&local_74);
  }
  if (local_81 == '\0') {
    local_a4 = *(undefined4 *)(*(int *)(local_88[0x10] + 8) + 8 + local_88[0x11] * 8);
    local_a0 = *(undefined4 *)(*(int *)(local_88[0x10] + 8) + 0xc + local_88[0x11] * 8);
    uVar3 = (**(code **)(*(int *)(local_88[4] + 0x18) + 4))();
    cVar1 = FUN_00466290(local_68,local_60,local_a4,local_a0,uVar3);
    if (cVar1 != '\0') {
      local_81 = '\x01';
      local_98 = (undefined4 *)(*(int *)(local_88[0x10] + 8) + local_88[0x11] * 8);
      *local_98 = local_68;
      local_98[1] = local_60;
    }
  }
  if (local_81 != '\0') {
    local_88[0x11] = local_88[0x11] + 1;
    local_88[0x12] = local_88[0x11];
  }
LAB_006016ef:
  if (local_88[0x12] == local_88[0x11]) {
    FUN_00602400();
  }
  (**(code **)(*local_88 + 0x34))();
  FUN_0083e885();
  return;
}

