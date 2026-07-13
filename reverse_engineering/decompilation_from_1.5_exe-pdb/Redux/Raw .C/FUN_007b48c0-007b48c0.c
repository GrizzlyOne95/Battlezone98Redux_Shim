
void __thiscall FUN_007b48c0(int param_1,int param_2,ushort param_3)

{
  byte bVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  uint local_11c;
  uint local_118;
  uint local_114;
  uint local_110;
  uint local_10c;
  uint local_108;
  uint local_100;
  uint local_f8;
  uint local_e8;
  uint local_e0;
  uint local_dc;
  uint local_d0;
  uint local_c4;
  byte *local_bc;
  byte *local_b8;
  byte *local_b4;
  byte *local_b0;
  byte *local_ac;
  byte *local_a8;
  byte *local_a4;
  byte *local_a0;
  byte *local_9c;
  byte *local_98;
  byte *local_94;
  byte *local_90;
  byte *local_8c;
  byte *local_88;
  byte *local_84;
  byte *local_80;
  byte *local_7c;
  byte *local_78;
  byte *local_70;
  byte *local_6c;
  byte *local_68;
  byte *local_64;
  byte *local_60;
  byte *local_5c;
  byte *local_58;
  byte *local_54;
  char *local_34;
  byte local_28 [32];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_2 == 0x1b) {
    FUN_00788060();
    goto LAB_007b541a;
  }
  if (*(int *)(param_1 + 0x184) == 0) goto LAB_007b541a;
  if ((param_3 == 0) || (0x80 < param_3)) {
    FUN_007d6a70("unavailable key for BZ %d\n",param_3);
    (**(code **)(**(int **)(param_1 + 0x178) + 0x3c))(*(undefined4 *)(param_1 + 0x180));
    FUN_007cc5c0(1);
    goto LAB_007b541a;
  }
  FUN_007cc5c0(0);
  FUN_007cc5c0(0);
  FUN_00434f60(param_3,local_28);
  local_34 = (char *)0x0;
  switch(*(undefined4 *)(param_1 + 0x184)) {
  case 1:
    local_34 = "throttle_down";
    break;
  case 2:
    local_34 = "throttle_up";
    break;
  case 3:
    local_34 = "pitch_up";
    break;
  case 4:
    local_34 = "pitch_down";
    break;
  case 5:
    local_34 = "strafe_left";
    break;
  case 6:
    local_34 = "strafe_right";
    break;
  case 7:
    local_34 = "turbo";
    break;
  case 8:
    local_34 = "jump";
    break;
  case 9:
    local_34 = "steer_right";
    break;
  case 10:
    local_34 = "steer_left";
    break;
  case 0xb:
    local_34 = "weapon_fire";
    break;
  case 0xc:
    local_34 = "weapon_cycle";
  }
  local_bc = local_28;
  local_b0 = (byte *)FUN_0081c190("throttle_up");
  do {
    bVar1 = *local_b0;
    bVar3 = bVar1 < *local_bc;
    if (bVar1 != *local_bc) {
LAB_007b4aa6:
      local_dc = -(uint)bVar3 | 1;
      goto LAB_007b4ab1;
    }
    if (bVar1 == 0) break;
    bVar1 = local_b0[1];
    bVar3 = bVar1 < local_bc[1];
    if (bVar1 != local_bc[1]) goto LAB_007b4aa6;
    local_b0 = local_b0 + 2;
    local_bc = local_bc + 2;
  } while (bVar1 != 0);
  local_dc = 0;
LAB_007b4ab1:
  if (local_dc == 0) {
LAB_007b4b85:
    bVar3 = true;
  }
  else {
    local_90 = local_28;
    local_60 = (byte *)FUN_0081c190("throttle_down");
    do {
      bVar1 = *local_60;
      bVar3 = bVar1 < *local_90;
      if (bVar1 != *local_90) {
LAB_007b4b59:
        local_f8 = -(uint)bVar3 | 1;
        goto LAB_007b4b64;
      }
      if (bVar1 == 0) break;
      bVar1 = local_60[1];
      bVar3 = bVar1 < local_90[1];
      if (bVar1 != local_90[1]) goto LAB_007b4b59;
      local_60 = local_60 + 2;
      local_90 = local_90 + 2;
    } while (bVar1 != 0);
    local_f8 = 0;
LAB_007b4b64:
    if (local_f8 == 0) goto LAB_007b4b85;
    bVar3 = false;
  }
  if (bVar3) {
LAB_007b4c38:
    bVar3 = true;
  }
  else {
    local_a8 = local_28;
    local_68 = (byte *)FUN_0081c190("strafe_left");
    do {
      bVar1 = *local_68;
      bVar3 = bVar1 < *local_a8;
      if (bVar1 != *local_a8) {
LAB_007b4c0c:
        local_100 = -(uint)bVar3 | 1;
        goto LAB_007b4c17;
      }
      if (bVar1 == 0) break;
      bVar1 = local_68[1];
      bVar3 = bVar1 < local_a8[1];
      if (bVar1 != local_a8[1]) goto LAB_007b4c0c;
      local_68 = local_68 + 2;
      local_a8 = local_a8 + 2;
    } while (bVar1 != 0);
    local_100 = 0;
LAB_007b4c17:
    if (local_100 == 0) goto LAB_007b4c38;
    bVar3 = false;
  }
  if (bVar3) {
LAB_007b4ceb:
    bVar3 = true;
  }
  else {
    local_98 = local_28;
    local_70 = (byte *)FUN_0081c190("strafe_right");
    do {
      bVar1 = *local_70;
      bVar3 = bVar1 < *local_98;
      if (bVar1 != *local_98) {
LAB_007b4cbf:
        local_108 = -(uint)bVar3 | 1;
        goto LAB_007b4cca;
      }
      if (bVar1 == 0) break;
      bVar1 = local_70[1];
      bVar3 = bVar1 < local_98[1];
      if (bVar1 != local_98[1]) goto LAB_007b4cbf;
      local_70 = local_70 + 2;
      local_98 = local_98 + 2;
    } while (bVar1 != 0);
    local_108 = 0;
LAB_007b4cca:
    if (local_108 == 0) goto LAB_007b4ceb;
    bVar3 = false;
  }
  if (bVar3) {
LAB_007b4d9e:
    bVar3 = true;
  }
  else {
    local_b8 = local_28;
    local_78 = (byte *)FUN_0081c190(&DAT_008857d0);
    do {
      bVar1 = *local_78;
      bVar3 = bVar1 < *local_b8;
      if (bVar1 != *local_b8) {
LAB_007b4d72:
        local_110 = -(uint)bVar3 | 1;
        goto LAB_007b4d7d;
      }
      if (bVar1 == 0) break;
      bVar1 = local_78[1];
      bVar3 = bVar1 < local_b8[1];
      if (bVar1 != local_b8[1]) goto LAB_007b4d72;
      local_78 = local_78 + 2;
      local_b8 = local_b8 + 2;
    } while (bVar1 != 0);
    local_110 = 0;
LAB_007b4d7d:
    if (local_110 == 0) goto LAB_007b4d9e;
    bVar3 = false;
  }
  if (bVar3) {
LAB_007b4e51:
    bVar3 = true;
  }
  else {
    local_a0 = local_28;
    local_80 = (byte *)FUN_0081c190("turbo");
    do {
      bVar1 = *local_80;
      bVar3 = bVar1 < *local_a0;
      if (bVar1 != *local_a0) {
LAB_007b4e25:
        local_118 = -(uint)bVar3 | 1;
        goto LAB_007b4e30;
      }
      if (bVar1 == 0) break;
      bVar1 = local_80[1];
      bVar3 = bVar1 < local_a0[1];
      if (bVar1 != local_a0[1]) goto LAB_007b4e25;
      local_80 = local_80 + 2;
      local_a0 = local_a0 + 2;
    } while (bVar1 != 0);
    local_118 = 0;
LAB_007b4e30:
    if (local_118 == 0) goto LAB_007b4e51;
    bVar3 = false;
  }
  if (bVar3) {
LAB_007b4f04:
    bVar3 = true;
  }
  else {
    local_58 = local_28;
    local_88 = (byte *)FUN_0081c190("pitch_up");
    do {
      bVar1 = *local_88;
      bVar3 = bVar1 < *local_58;
      if (bVar1 != *local_58) {
LAB_007b4ed8:
        local_114 = -(uint)bVar3 | 1;
        goto LAB_007b4ee3;
      }
      if (bVar1 == 0) break;
      bVar1 = local_88[1];
      bVar3 = bVar1 < local_58[1];
      if (bVar1 != local_58[1]) goto LAB_007b4ed8;
      local_88 = local_88 + 2;
      local_58 = local_58 + 2;
    } while (bVar1 != 0);
    local_114 = 0;
LAB_007b4ee3:
    if (local_114 == 0) goto LAB_007b4f04;
    bVar3 = false;
  }
  if (bVar3) {
LAB_007b4fab:
    bVar3 = true;
  }
  else {
    local_64 = local_28;
    local_5c = (byte *)FUN_0081c190("pitch_down");
    do {
      bVar1 = *local_5c;
      bVar3 = bVar1 < *local_64;
      if (bVar1 != *local_64) {
LAB_007b4f7f:
        local_10c = -(uint)bVar3 | 1;
        goto LAB_007b4f8a;
      }
      if (bVar1 == 0) break;
      bVar1 = local_5c[1];
      bVar3 = bVar1 < local_64[1];
      if (bVar1 != local_64[1]) goto LAB_007b4f7f;
      local_5c = local_5c + 2;
      local_64 = local_64 + 2;
    } while (bVar1 != 0);
    local_10c = 0;
LAB_007b4f8a:
    if (local_10c == 0) goto LAB_007b4fab;
    bVar3 = false;
  }
  if (bVar3) {
LAB_007b5052:
    bVar3 = true;
  }
  else {
    local_54 = local_28;
    local_6c = (byte *)FUN_0081c190("steer_left");
    do {
      bVar1 = *local_6c;
      bVar3 = bVar1 < *local_54;
      if (bVar1 != *local_54) {
LAB_007b5026:
        local_11c = -(uint)bVar3 | 1;
        goto LAB_007b5031;
      }
      if (bVar1 == 0) break;
      bVar1 = local_6c[1];
      bVar3 = bVar1 < local_54[1];
      if (bVar1 != local_54[1]) goto LAB_007b5026;
      local_6c = local_6c + 2;
      local_54 = local_54 + 2;
    } while (bVar1 != 0);
    local_11c = 0;
LAB_007b5031:
    if (local_11c == 0) goto LAB_007b5052;
    bVar3 = false;
  }
  if (bVar3) {
LAB_007b50f9:
    bVar3 = true;
  }
  else {
    local_84 = local_28;
    local_7c = (byte *)FUN_0081c190("steer_right");
    do {
      bVar1 = *local_7c;
      bVar3 = bVar1 < *local_84;
      if (bVar1 != *local_84) {
LAB_007b50cd:
        local_e8 = -(uint)bVar3 | 1;
        goto LAB_007b50d8;
      }
      if (bVar1 == 0) break;
      bVar1 = local_7c[1];
      bVar3 = bVar1 < local_84[1];
      if (bVar1 != local_84[1]) goto LAB_007b50cd;
      local_7c = local_7c + 2;
      local_84 = local_84 + 2;
    } while (bVar1 != 0);
    local_e8 = 0;
LAB_007b50d8:
    if (local_e8 == 0) goto LAB_007b50f9;
    bVar3 = false;
  }
  if (bVar3) {
LAB_007b51b8:
    bVar3 = true;
  }
  else {
    local_94 = local_28;
    local_8c = (byte *)FUN_0081c190("weapon_fire");
    do {
      bVar1 = *local_8c;
      bVar3 = bVar1 < *local_94;
      if (bVar1 != *local_94) {
LAB_007b518c:
        local_c4 = -(uint)bVar3 | 1;
        goto LAB_007b5197;
      }
      if (bVar1 == 0) break;
      bVar1 = local_8c[1];
      bVar3 = bVar1 < local_94[1];
      if (bVar1 != local_94[1]) goto LAB_007b518c;
      local_8c = local_8c + 2;
      local_94 = local_94 + 2;
    } while (bVar1 != 0);
    local_c4 = 0;
LAB_007b5197:
    if (local_c4 == 0) goto LAB_007b51b8;
    bVar3 = false;
  }
  if (bVar3) {
LAB_007b5277:
    bVar3 = true;
  }
  else {
    local_a4 = local_28;
    local_9c = (byte *)FUN_0081c190("weapon_cycle");
    do {
      bVar1 = *local_9c;
      bVar3 = bVar1 < *local_a4;
      if (bVar1 != *local_a4) {
LAB_007b524b:
        local_d0 = -(uint)bVar3 | 1;
        goto LAB_007b5256;
      }
      if (bVar1 == 0) break;
      bVar1 = local_9c[1];
      bVar3 = bVar1 < local_a4[1];
      if (bVar1 != local_a4[1]) goto LAB_007b524b;
      local_9c = local_9c + 2;
      local_a4 = local_a4 + 2;
    } while (bVar1 != 0);
    local_d0 = 0;
LAB_007b5256:
    if (local_d0 == 0) goto LAB_007b5277;
    bVar3 = false;
  }
  iVar2 = FUN_0081c380(local_28);
  if (iVar2 == 0) {
    if (bVar3) {
      local_ac = (byte *)FUN_0081c190(local_34);
      local_b4 = local_28;
      do {
        bVar1 = *local_ac;
        bVar4 = bVar1 < *local_b4;
        if (bVar1 != *local_b4) {
LAB_007b5375:
          local_e0 = -(uint)bVar4 | 1;
          goto LAB_007b5380;
        }
        if (bVar1 == 0) break;
        bVar1 = local_ac[1];
        bVar4 = bVar1 < local_b4[1];
        if (bVar1 != local_b4[1]) goto LAB_007b5375;
        local_ac = local_ac + 2;
        local_b4 = local_b4 + 2;
      } while (bVar1 != 0);
      local_e0 = 0;
LAB_007b5380:
      if (local_e0 == 0) {
        bVar3 = false;
      }
    }
    if (bVar3) {
      FUN_007cc5c0(1);
      (**(code **)(**(int **)(param_1 + 0x178) + 0x3c))(*(undefined4 *)(param_1 + 0x17c));
      FUN_007cc5c0(1);
    }
    else {
      FUN_0081c440(local_34,local_28);
      FUN_0061f1c0(local_34,local_28);
      FUN_007b5480();
    }
  }
  else {
    FUN_007cc5c0(1);
    (**(code **)(**(int **)(param_1 + 0x178) + 0x3c))(*(undefined4 *)(param_1 + 0x180));
    FUN_007cc5c0(1);
  }
LAB_007b541a:
  FUN_0083e885();
  return;
}

