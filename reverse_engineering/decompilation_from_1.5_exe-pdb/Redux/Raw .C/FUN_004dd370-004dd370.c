
/* WARNING: Removing unreachable block (ram,0x004dd56a) */

void __thiscall FUN_004dd370(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_f8 [4];
  undefined1 local_f4 [4];
  undefined1 local_f0 [4];
  undefined1 local_ec [4];
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  int local_cc;
  int local_c8;
  int local_c4;
  undefined4 local_c0;
  int local_bc;
  int local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  int local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  int local_7c;
  uint local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  uint local_54;
  undefined4 local_50;
  undefined1 local_49;
  int local_48;
  undefined1 local_44 [4];
  int local_40;
  undefined1 local_39;
  int local_38;
  char local_32;
  char local_31;
  int local_30;
  char local_29;
  char local_28 [32];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_30 = param_1;
  local_29 = FUN_004ceb10(param_2,param_1 + 0xe8,4);
  if ((local_29 == '\0') || (cVar1 = FUN_004ced10(param_2,local_30 + 0x108,0xc), cVar1 == '\0')) {
    local_8c = 0;
  }
  else {
    local_8c = 1;
  }
  local_29 = (char)local_8c;
  if (((char)local_8c == '\0') ||
     (cVar1 = FUN_004cf350(param_2,local_30 + 0x114,0x48), cVar1 == '\0')) {
    local_84 = 0;
  }
  else {
    local_84 = 1;
  }
  local_29 = (char)local_84;
  if (((char)local_84 == '\0') || (cVar1 = FUN_004ce910(param_2,local_30 + 0x15c,4), cVar1 == '\0'))
  {
    local_80 = 0;
  }
  else {
    local_80 = 1;
  }
  local_29 = (char)local_80;
  if (DAT_009173b7 != '\0') {
    *(undefined4 *)(local_30 + 0x138) = 0;
    *(undefined4 *)(local_30 + 0x13c) = 0;
    *(undefined4 *)(local_30 + 0x140) = 0;
  }
  if (DAT_00917b20 < 0x3fa) {
    if (((((char)local_80 == '\0') || (cVar1 = FUN_004ce910(param_2,local_f4,4), cVar1 == '\0')) ||
        (cVar1 = FUN_004ce910(param_2,local_ec,4), cVar1 == '\0')) ||
       ((cVar1 = FUN_004ce910(param_2,local_f0,4), cVar1 == '\0' ||
        (cVar1 = FUN_004ce910(param_2,local_f8,4), cVar1 == '\0')))) {
      local_5c = 0;
    }
    else {
      local_5c = 1;
    }
    local_29 = (char)local_5c;
  }
  if (0x406 < DAT_00917b20) {
    local_88 = 0;
    local_28[0] = '\0';
    if ((local_29 == '\0') || (cVar1 = FUN_004ce2f0(param_2,local_28,0x20), cVar1 == '\0')) {
      local_64 = 0;
    }
    else {
      local_64 = 1;
    }
    local_29 = (char)local_64;
    if (local_28[0] != '\0') {
      FUN_004d9730(local_28);
    }
    if (((0x415 < DAT_00917b20) && (DAT_00917b20 < 2000)) || (0x7d9 < DAT_00917b20)) {
      if ((local_29 == '\0') || (cVar1 = FUN_004ce5e0(param_2,local_30 + 0x188,1), cVar1 == '\0')) {
        local_90 = 0;
      }
      else {
        local_90 = 1;
      }
      local_29 = (char)local_90;
    }
  }
  if (((local_29 == '\0') || (cVar1 = FUN_004ce5e0(param_2,&local_39,1), cVar1 == '\0')) ||
     ((cVar1 = FUN_004ce5e0(param_2,&local_49,1), cVar1 == '\0' ||
      ((cVar1 = FUN_004cea20(param_2,local_30 + 0x18c,4), cVar1 == '\0' ||
       (cVar1 = FUN_004cea20(param_2,local_30 + 400,4), cVar1 == '\0')))))) {
    local_6c = 0;
  }
  else {
    local_6c = 1;
  }
  local_29 = (char)local_6c;
  if (DAT_009173b7 != '\0') {
    *(undefined4 *)(local_30 + 0x18c) = 0;
    *(undefined4 *)(local_30 + 400) = 0;
  }
  if (DAT_009173b7 == '\0') {
    if ((((char)local_6c == '\0') ||
        (cVar1 = FUN_004ceb10(param_2,local_30 + 0x1d8,4), cVar1 == '\0')) ||
       ((cVar1 = FUN_004ceb10(param_2,local_30 + 0x1dc,4), cVar1 == '\0' ||
        ((((cVar1 = FUN_004ceb10(param_2,local_30 + 0x1e0,4), cVar1 == '\0' ||
           (cVar1 = FUN_004ceb10(param_2,local_30 + 0x1e4,4), cVar1 == '\0')) ||
          (cVar1 = FUN_004ceb10(param_2,local_30 + 0x1e8,4), cVar1 == '\0')) ||
         (cVar1 = FUN_004ceb10(param_2,local_30 + 0x1f0,4), cVar1 == '\0')))))) {
      local_98 = 0;
    }
    else {
      local_98 = 1;
    }
    local_29 = (char)local_98;
  }
  else if (DAT_00917b20 < 0x409) {
    if ((((((char)local_6c == '\0') || (cVar1 = FUN_004ceb10(param_2,local_44,4), cVar1 == '\0')) ||
         (cVar1 = FUN_004ceb10(param_2,local_44,4), cVar1 == '\0')) ||
        ((cVar1 = FUN_004ceb10(param_2,local_44,4), cVar1 == '\0' ||
         (cVar1 = FUN_004ceb10(param_2,local_44,4), cVar1 == '\0')))) ||
       ((cVar1 = FUN_004ceb10(param_2,local_44,4), cVar1 == '\0' ||
        (cVar1 = FUN_004ceb10(param_2,local_44,4), cVar1 == '\0')))) {
      local_74 = 0;
    }
    else {
      local_74 = 1;
    }
    local_29 = (char)local_74;
  }
  if (((local_29 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_30 + 0x200,4), cVar1 == '\0')) ||
     ((cVar1 = FUN_004ce910(param_2,&local_cc,4), cVar1 == '\0' ||
      (cVar1 = FUN_004ce910(param_2,&local_7c,4), cVar1 == '\0')))) {
    local_a0 = 0;
  }
  else {
    local_a0 = 1;
  }
  local_29 = (char)local_a0;
  if ((DAT_009173b7 == '\0') || ((float)local_7c == *(float *)(local_30 + 0x208))) {
    *(float *)(local_30 + 0x208) = (float)local_7c;
    FUN_004a76a0((float)local_cc);
  }
  else {
    FUN_004a76a0(*(float *)(local_30 + 0x200) * *(float *)(local_30 + 0x208));
  }
  FUN_0049f300(local_39);
  if (DAT_00917b20 < 0x3f7) {
    local_e0 = 0;
    local_e8 = 0;
    local_d4 = 0;
    if ((((local_29 == '\0') || (cVar1 = FUN_004ceb10(param_2,&local_e0,4), cVar1 == '\0')) ||
        (cVar1 = FUN_004ce910(param_2,&local_e8,4), cVar1 == '\0')) ||
       (cVar1 = FUN_004ce910(param_2,&local_d4,4), cVar1 == '\0')) {
      local_a8 = 0;
    }
    else {
      local_a8 = 1;
    }
    local_29 = (char)local_a8;
  }
  if (((local_29 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_30 + 0x20c,4), cVar1 == '\0')) ||
     ((cVar1 = FUN_004ce910(param_2,&local_d8,4), cVar1 == '\0' ||
      (cVar1 = FUN_004ce910(param_2,&local_a4,4), cVar1 == '\0')))) {
    local_b0 = 0;
  }
  else {
    local_b0 = 1;
  }
  local_29 = (char)local_b0;
  if ((DAT_009173b7 == '\0') || (iVar2 = FUN_0046d060(), local_a4 == iVar2)) {
    FUN_004d96d0(local_a4);
    FUN_004a7700(local_d8);
  }
  else {
    iVar2 = FUN_0046d060();
    FUN_004a7700((int)((float)iVar2 * *(float *)(local_30 + 0x20c) + 0.5));
  }
  if (DAT_009173b7 == '\0') {
    if ((((local_29 == '\0') || (cVar1 = FUN_0045c160(param_2), cVar1 == '\0')) ||
        (cVar1 = FUN_0045c160(param_2), cVar1 == '\0')) ||
       (cVar1 = FUN_004cf640(param_2,local_30 + 0xfc,4,"GameObject:aiProcess",local_30),
       cVar1 == '\0')) {
      local_94 = 0;
    }
    else {
      local_94 = 1;
    }
    local_29 = (char)local_94;
  }
  else {
    if ((local_29 == '\0') || (cVar1 = FUN_0045c160(param_2), cVar1 == '\0')) {
      local_50 = 0;
    }
    else {
      local_50 = 1;
    }
    local_29 = (char)local_50;
    if (0x3fd < DAT_00917b20) {
      if (((char)local_50 == '\0') || (cVar1 = FUN_004ce5e0(param_2,&local_31,1), cVar1 == '\0')) {
        local_b4 = 0;
      }
      else {
        local_b4 = 1;
      }
      local_29 = (char)local_b4;
    }
  }
  if ((0x3ef < DAT_00917b20) && (local_29 != '\0')) {
    local_29 = FUN_004ce5e0(param_2,local_30 + 0x9c,1);
  }
  if (0x3f8 < DAT_00917b20) {
    if ((local_29 == '\0') || (cVar1 = FUN_004ce910(param_2,local_30 + 0x104,4), cVar1 == '\0')) {
      local_ac = 0;
    }
    else {
      local_ac = 1;
    }
    local_29 = (char)local_ac;
    if (DAT_00917b20 < 0x406) {
      if (((char)local_ac == '\0') || (cVar1 = FUN_004ce5e0(param_2,&local_32,1), cVar1 == '\0')) {
        local_9c = 0;
      }
      else {
        local_9c = 1;
      }
      local_29 = (char)local_9c;
      if (local_32 == '\0') {
        *(undefined4 *)(local_30 + 0xec) = 0;
      }
      else if (local_30 == DAT_00917afc) {
        *(undefined4 *)(local_30 + 0xec) = *(undefined4 *)(*(int *)(local_30 + 0xf8) + 0xd4);
      }
      else {
        *(undefined4 *)(local_30 + 0xec) = *(undefined4 *)(*(int *)(local_30 + 0xf8) + 0xd0);
      }
    }
    else {
      if (((char)local_ac == '\0') || (cVar1 = FUN_004cf210(param_2,&local_bc,8), cVar1 == '\0')) {
        local_c0 = 0;
      }
      else {
        local_c0 = 1;
      }
      local_29 = (char)local_c0;
      if (*(int *)(*(int *)(local_30 + 0xf8) + 0x50) < 1) {
        if (local_bc != 0 || local_b8 != 0) {
          FUN_007d6a70("%s skipped pilot class %.8s\n",*(undefined4 *)(local_30 + 0x100),&local_bc);
        }
      }
      else {
        uVar3 = FUN_004e0f70(local_bc,local_b8);
        *(undefined4 *)(local_30 + 0xec) = uVar3;
        local_32 = *(int *)(local_30 + 0xec) != 0;
        local_54 = (uint)(byte)local_32;
      }
    }
  }
  if (0x407 < DAT_00917b20) {
    if ((local_29 == '\0') || (cVar1 = FUN_004ce910(param_2,local_30 + 0x180,4), cVar1 == '\0')) {
      local_58 = 0;
    }
    else {
      local_58 = 1;
    }
    local_29 = (char)local_58;
  }
  if ((0x408 < DAT_00917b20) && (DAT_009173b7 == '\0')) {
    for (local_40 = 0; local_40 < 5; local_40 = local_40 + 1) {
      if ((local_29 == '\0') || (cVar1 = FUN_004cf210(param_2,&local_c8,8), cVar1 == '\0')) {
        local_60 = 0;
      }
      else {
        local_60 = 1;
      }
      local_29 = (char)local_60;
      local_48 = 0;
      if (local_c8 != 0 || local_c4 != 0) {
        local_48 = FUN_00611e30(local_c8,local_c4);
      }
      if (((local_48 != 0) && (iVar2 = FUN_00417ca0(), iVar2 != 0)) &&
         (iVar2 = FUN_00417f40(local_40), iVar2 != 0)) {
        local_38 = FUN_00417f60(local_40);
        if ((local_38 != 0) && (local_48 != *(int *)(local_38 + 8))) {
          FUN_00611590();
          local_38 = 0;
        }
        if (local_38 == 0) {
          local_e4 = FUN_00417f40(local_40);
          local_38 = FUN_006121c0(*(undefined4 *)(local_30 + 0xf4),local_e4);
          FUN_004a77a0(local_40,local_38);
        }
      }
    }
    if ((local_29 == '\0') || (cVar1 = FUN_004cea20(param_2,&local_dc,4), cVar1 == '\0')) {
      local_68 = 0;
    }
    else {
      local_68 = 1;
    }
    local_29 = (char)local_68;
    if (((char)local_68 == '\0') || (cVar1 = FUN_004cea20(param_2,&local_d0,4), cVar1 == '\0')) {
      local_70 = 0;
    }
    else {
      local_70 = 1;
    }
    local_29 = (char)local_70;
    if (*(int *)(local_30 + 0x1a0) != 0) {
      FUN_004d9950(local_dc);
      FUN_004d9880(local_d0);
    }
  }
  if (DAT_009173b7 != '\0') {
    if (DAT_00917b20 < 0x3fe) {
      local_31 = local_32;
    }
    else if (local_31 == '\0') {
      *(undefined4 *)(local_30 + 0xec) = 0;
    }
    local_78 = (uint)(local_31 != '\0');
    *(uint *)(local_30 + 0xfc) = local_78;
  }
  FUN_004db800();
  FUN_0083e885();
  return;
}

