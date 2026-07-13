
void __thiscall FUN_004de110(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  int local_9c;
  undefined8 local_98;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 local_7c;
  int local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  uint local_64;
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
  int local_38;
  undefined1 local_31;
  int local_30;
  char local_29;
  char local_28 [32];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(int *)(param_1 + 0xcc) != 3) {
    *(undefined4 *)(param_1 + 0xd4) = 0;
  }
  local_28[0] = '\0';
  local_28[1] = '\0';
  local_28[2] = '\0';
  local_28[3] = '\0';
  local_28[4] = '\0';
  local_28[5] = '\0';
  local_28[6] = '\0';
  local_28[7] = '\0';
  local_28[8] = '\0';
  local_28[9] = '\0';
  local_28[10] = '\0';
  local_28[0xb] = '\0';
  local_28[0xc] = '\0';
  local_28[0xd] = '\0';
  local_28[0xe] = '\0';
  local_28[0xf] = '\0';
  local_28[0x10] = '\0';
  local_28[0x11] = '\0';
  local_28[0x12] = '\0';
  local_28[0x13] = '\0';
  local_28[0x14] = '\0';
  local_28[0x15] = '\0';
  local_28[0x16] = '\0';
  local_28[0x17] = '\0';
  local_28[0x18] = '\0';
  local_28[0x19] = '\0';
  local_28[0x1a] = '\0';
  local_28[0x1b] = '\0';
  local_28[0x1c] = '\0';
  local_28[0x1d] = '\0';
  local_28[0x1e] = '\0';
  local_28[0x1f] = '\0';
  local_30 = param_1;
  iVar2 = strncmp(*(char **)(param_1 + 0x184),(char *)(*(int *)(param_1 + 0xf8) + 100),0x20);
  if (iVar2 != 0) {
    strncpy(local_28,*(char **)(local_30 + 0x184),0x20);
  }
  cVar1 = FUN_004cd360(param_2,local_30 + 0xe8,4,"illumination");
  if ((((((cVar1 == '\0') ||
         (cVar1 = FUN_004cd520(param_2,local_30 + 0x108,0xc,&DAT_00875e34), cVar1 == '\0')) ||
        (cVar1 = FUN_004cdb40(param_2,local_30 + 0x114,0x48,"euler"), cVar1 == '\0')) ||
       ((cVar1 = FUN_004cd1b0(param_2,local_30 + 0x15c,4,"seqNo"), cVar1 == '\0' ||
        (cVar1 = FUN_004cce90(param_2,local_28,0x20,&DAT_00879d2c), cVar1 == '\0')))) ||
      (cVar1 = FUN_004ccf20(param_2,local_30 + 0x188,1,"isCritical"), cVar1 == '\0')) ||
     (((cVar1 = FUN_004ccf20(param_2,local_30 + 0x189,1,"isObjective"), cVar1 == '\0' ||
       (cVar1 = FUN_004ccf20(param_2,local_30 + 0x18a,1,"isSelected"), cVar1 == '\0')) ||
      ((cVar1 = FUN_004cd290(param_2,local_30 + 0x18c,4,"isVisible"), cVar1 == '\0' ||
       (cVar1 = FUN_004cd290(param_2,local_30 + 400,4,&DAT_00879cf4), cVar1 == '\0')))))) {
    local_68 = 0;
  }
  else {
    local_68 = 1;
  }
  local_29 = (char)local_68;
  if (DAT_009173b7 == '\0') {
    if ((((((char)local_68 == '\0') ||
          (cVar1 = FUN_004cd360(param_2,local_30 + 0x1d8,4,"playerShot"), cVar1 == '\0')) ||
         (cVar1 = FUN_004cd360(param_2,local_30 + 0x1dc,4,"playerCollide"), cVar1 == '\0')) ||
        ((cVar1 = FUN_004cd360(param_2,local_30 + 0x1e0,4,"friendShot"), cVar1 == '\0' ||
         (cVar1 = FUN_004cd360(param_2,local_30 + 0x1e4,4,"friendCollide"), cVar1 == '\0')))) ||
       ((cVar1 = FUN_004cd360(param_2,local_30 + 0x1e8,4,"enemyShot"), cVar1 == '\0' ||
        (cVar1 = FUN_004cd360(param_2,local_30 + 0x1f0,4,"groundCollide"), cVar1 == '\0')))) {
      local_80 = 0;
    }
    else {
      local_80 = 1;
    }
    local_29 = (char)local_80;
  }
  FUN_0046fbd0();
  local_8c = FUN_0083f040();
  FUN_004624f0();
  local_90 = FUN_0083f040();
  local_a0 = FUN_00417c80();
  local_a4 = FUN_0046d060();
  if ((((local_29 == '\0') ||
       (cVar1 = FUN_004cd360(param_2,local_30 + 0x200,4,"healthRatio"), cVar1 == '\0')) ||
      ((cVar1 = FUN_004cd1b0(param_2,&local_8c,4,"curHealth"), cVar1 == '\0' ||
       (((cVar1 = FUN_004cd1b0(param_2,&local_90,4,"maxHealth"), cVar1 == '\0' ||
         (cVar1 = FUN_004cd360(param_2,local_30 + 0x20c,4,"ammoRatio"), cVar1 == '\0')) ||
        (cVar1 = FUN_004cd1b0(param_2,&local_a0,4,"curAmmo"), cVar1 == '\0')))))) ||
     (cVar1 = FUN_004cd1b0(param_2,&local_a4,4,"maxAmmo"), cVar1 == '\0')) {
    local_44 = 0;
  }
  else {
    local_44 = 1;
  }
  local_29 = (char)local_44;
  if (DAT_009173b7 == '\0') {
    if ((((char)local_44 == '\0') || (cVar1 = FUN_0045c2a0(param_2), cVar1 == '\0')) ||
       ((cVar1 = FUN_0045c2a0(param_2), cVar1 == '\0' ||
        (cVar1 = FUN_004cf520(param_2,local_30 + 0xfc,4,"undefptr"), cVar1 == '\0')))) {
      local_6c = 0;
    }
    else {
      local_6c = 1;
    }
    local_29 = (char)local_6c;
  }
  else {
    if (*(int *)(local_30 + 0xcc) == 0) {
      if (((char)local_44 == '\0') || (cVar1 = FUN_0045c2a0(param_2), cVar1 == '\0')) {
        local_60 = 0;
      }
      else {
        local_60 = 1;
      }
      local_29 = (char)local_60;
    }
    else {
      if (((char)local_44 == '\0') || (cVar1 = FUN_0045c2a0(param_2), cVar1 == '\0')) {
        local_4c = 0;
      }
      else {
        local_4c = 1;
      }
      local_29 = (char)local_4c;
    }
    local_31 = *(int *)(local_30 + 0xfc) != 0;
    local_64 = (uint)(byte)local_31;
    if ((local_29 == '\0') || (cVar1 = FUN_004ccf20(param_2,&local_31,1,"aiProcess"), cVar1 == '\0')
       ) {
      local_54 = 0;
    }
    else {
      local_54 = 1;
    }
    local_29 = (char)local_54;
  }
  if ((local_29 == '\0') ||
     (cVar1 = FUN_004ccf20(param_2,local_30 + 0x9c,1,"isCargo"), cVar1 == '\0')) {
    local_5c = 0;
  }
  else {
    local_5c = 1;
  }
  local_29 = (char)local_5c;
  if (((char)local_5c == '\0') ||
     (cVar1 = FUN_004cd1b0(param_2,local_30 + 0x104,4,"independence"), cVar1 == '\0')) {
    local_74 = 0;
  }
  else {
    local_74 = 1;
  }
  local_29 = (char)local_74;
  if (*(int *)(local_30 + 0xec) == 0) {
    local_88 = 0;
    uStack_84 = 0;
  }
  else {
    local_88 = *(undefined4 *)(*(int *)(local_30 + 0xec) + 0x30);
    uStack_84 = *(undefined4 *)(*(int *)(local_30 + 0xec) + 0x34);
  }
  local_ac = local_88;
  local_a8 = uStack_84;
  if (((char)local_74 == '\0') ||
     (cVar1 = FUN_004cda70(param_2,&local_ac,8,"curPilot"), cVar1 == '\0')) {
    local_7c = 0;
  }
  else {
    local_7c = 1;
  }
  local_29 = (char)local_7c;
  if (((char)local_7c == '\0') ||
     (cVar1 = FUN_004cd1b0(param_2,local_30 + 0x180,4,"perceivedTeam"), cVar1 == '\0')) {
    local_3c = 0;
  }
  else {
    local_3c = 1;
  }
  local_29 = (char)local_3c;
  if (DAT_009173b7 == '\0') {
    for (local_38 = 0; local_38 < 5; local_38 = local_38 + 1) {
      local_98 = 0;
      if ((*(int *)(local_30 + 0x1a0) != 0) && (local_78 = FUN_00417f60(local_38), local_78 != 0)) {
        local_9c = *(int *)(local_78 + 8);
        local_98 = *(undefined8 *)(local_9c + 0x18);
      }
      if ((local_29 == '\0') || (cVar1 = FUN_004cda70(param_2,&local_98,8,"wpnID"), cVar1 == '\0'))
      {
        local_70 = 0;
      }
      else {
        local_70 = 1;
      }
      local_29 = (char)local_70;
    }
    local_40 = 0;
    local_50 = 0;
    if (*(int *)(local_30 + 0x1a0) != 0) {
      local_40 = FUN_00417fb0();
      local_50 = FUN_00417f90();
    }
    if ((local_29 == '\0') || (cVar1 = FUN_004cd290(param_2,&local_40,4,"enabled"), cVar1 == '\0'))
    {
      local_48 = 0;
    }
    else {
      local_48 = 1;
    }
    local_29 = (char)local_48;
    if (((char)local_48 == '\0') ||
       (cVar1 = FUN_004cd290(param_2,&local_50,4,"selected"), cVar1 == '\0')) {
      local_58 = 0;
    }
    else {
      local_58 = 1;
    }
    local_29 = (char)local_58;
  }
  FUN_0083e885();
  return;
}

