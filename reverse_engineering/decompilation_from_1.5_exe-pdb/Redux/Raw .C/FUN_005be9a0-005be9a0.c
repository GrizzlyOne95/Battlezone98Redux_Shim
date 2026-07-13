
void __thiscall FUN_005be9a0(int *param_1,float param_2)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_108 [24];
  undefined1 local_f0 [12];
  undefined1 local_e4 [12];
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  uint local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  int local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  int local_54;
  undefined1 local_4d;
  float local_4c;
  int *local_48;
  undefined1 local_44 [12];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_54 = param_1[0x3d] + 0x20;
  local_48 = param_1;
  puVar2 = (undefined4 *)FUN_00447f60(local_108,local_54);
  local_38 = *puVar2;
  local_34 = puVar2[1];
  local_30 = puVar2[2];
  local_2c = puVar2[3];
  local_28 = puVar2[4];
  local_24 = puVar2[5];
  FUN_00444f70(local_48[0x3c],local_38,local_34,local_30,local_2c,local_28,local_24,&local_cc,
               local_44,0);
  local_58 = (float)((*(double *)(local_54 + 0x30) - (double)(float)local_48[0xc0]) -
                    (double)local_cc);
  if ((local_48[0x3f] == 0) && ((local_48[0x8a] == 2 || (local_48[0x8a] == 1)))) {
    local_48[0xc0] = *(int *)(local_48[0x3e] + 0x34c);
    *(uint *)(local_48[0x3d] + 0x14) = *(uint *)(local_48[0x3d] + 0x14) & 0xfffffffe;
    *(uint *)(local_48[0x8c] + 0x114) = *(uint *)(local_48[0x8c] + 0x114) & 0xfffffffb;
    local_48[0x8d] = 0;
    if (40.0 <= local_58) {
      local_48[0x8a] = 3;
    }
    else {
      local_48[0x8a] = 0;
    }
  }
  local_4d = *(int *)(local_48[0x8c] + 0xd4) != 0;
  local_90 = (uint)(byte)local_4d;
  if ((bool)local_4d) {
    local_78 = 2.0;
  }
  else {
    local_78 = *(float *)(local_48[0x8c] + 0xd0);
  }
  local_5c = local_78;
  local_d0 = *(float *)(local_48[0x8c] + 0xcc);
  local_d4 = *(float *)(local_48[0x8c] + 0xc4);
  fVar5 = (float10)FUN_004e9610(local_48[0x80]);
  local_4c = (float)fVar5;
  local_ac = *(float *)(local_48[0x3e] + 0x35c) * local_4c;
  local_a0 = *(float *)(local_48[0x3e] + 0x360) * local_4c;
  local_a8 = *(float *)(local_48[0x3e] + 0x328) * local_4c;
  local_b4 = *(float *)(local_48[0x3e] + 0x32c) * local_4c;
  local_74 = *(float *)(local_48[0x3e] + 0x330) * local_4c;
  local_bc = *(float *)(local_48[0x3e] + 0x334) * local_4c;
  local_d8 = *(float *)(local_48[0x3e] + 0x338) * local_4c;
  local_80 = *(float *)(local_48[0x3e] + 0x33c) * local_4c;
  local_c4 = *(float *)(local_48[0x3e] + 0x340) * local_4c;
  local_94 = *(float *)(local_48[0x3e] + 0x344) * local_4c;
  local_68 = *(float *)(local_48[0x3e] + 0x348) * local_4c;
  local_60 = local_5c * local_5c;
  if (1.0 < local_60) {
    local_60 = 1.0;
  }
  local_88 = (local_c4 - local_80) * local_60 + local_80;
  if (0.0 < local_88) {
    local_b0 = local_94 * param_2;
    fVar5 = (float10)FUN_00447ed0(local_d4 - (float)local_48[0x4f] / local_88,0xbf800000,0x3f800000)
    ;
    local_c0 = (float)fVar5;
    local_48[0x4f] = (int)(local_b0 * local_c0 + (float)local_48[0x4f]);
  }
  local_64 = local_a0 * param_2;
  local_48[0x4e] = (int)((float)local_48[0x4e] - local_64 * (float)local_48[0x4e]);
  local_48[0x50] = (int)((float)local_48[0x50] - local_64 * (float)local_48[0x50]);
  local_6c = local_ac * param_2;
  local_48[0x4e] = (int)((float)local_48[0x4e] - local_6c * *(float *)(local_54 + 0x1c));
  local_48[0x50] = (int)(local_6c * *(float *)(local_54 + 4) + (float)local_48[0x50]);
  piVar3 = (int *)FUN_00440300(local_e4,local_48 + 0x4b,local_48[0x3d] + 0x20);
  local_20 = *piVar3;
  local_1c = piVar3[1];
  local_18 = piVar3[2];
  local_48[0x4b] = local_20;
  local_48[0x4c] = local_1c;
  local_48[0x4d] = local_18;
  if (local_5c <= 0.0) {
    local_8c = local_b4;
  }
  else {
    local_8c = local_a8;
  }
  local_84 = local_8c;
  local_7c = local_bc * param_2;
  if (0.0 < local_74) {
    fVar5 = (float10)FUN_00447ed0(local_d0 - (float)local_48[0x4b] / local_74,0xbf800000,0x3f800000)
    ;
    local_b8 = (float)fVar5;
    local_48[0x4b] = (int)(local_b8 * local_7c + (float)local_48[0x4b]);
  }
  if (0.0 < local_84) {
    fVar5 = (float10)FUN_00447ed0(local_5c - (float)local_48[0x4d] / local_84,0xbf800000,0x3f800000)
    ;
    local_c8 = (float)fVar5;
    local_48[0x4d] = (int)(local_c8 * local_7c + (float)local_48[0x4d]);
  }
  if ((*(uint *)(local_48[0x3d] + 0x14) & 0x200) == 0) {
    fVar5 = (float10)FUN_00417910(local_68 * 0.025);
    local_98 = (float)fVar5;
    local_48[0x4c] = (int)((float)local_48[0x4c] - local_98 * 2.0 * param_2 * (float)local_48[0x4c])
    ;
  }
  piVar3 = (int *)FUN_00440210(local_f0,local_48 + 0x4b,local_48[0x3d] + 0x20);
  local_14 = *piVar3;
  local_10 = piVar3[1];
  local_c = piVar3[2];
  local_48[0x4b] = local_14;
  local_48[0x4c] = local_10;
  local_48[0x4d] = local_c;
  if ((*(uint *)(local_48[0x3d] + 0x14) & 0x200) == 0) {
    local_9c = local_68 * param_2;
    fVar5 = (float10)FUN_00447ed0(local_58 * -0.025,0xbf800000,0x3f800000);
    local_a4 = (float)fVar5;
    local_48[0x4c] = (int)(local_9c * local_a4 + (float)local_48[0x4c]);
  }
  else {
    local_48[0x4c] = (int)((float)local_48[0x4c] - param_2 * 9.8);
  }
  local_70 = local_48[0x8a];
  switch(local_70) {
  case 1:
    if (-40.0 < local_58) {
      local_48[0x8a] = 2;
      *(uint *)(local_48[0x3d] + 0x14) = *(uint *)(local_48[0x3d] + 0x14) | 1;
      *(uint *)(local_48[0x8c] + 0x114) = *(uint *)(local_48[0x8c] + 0x114) | 4;
      local_48[0x8d] = 3;
    }
    if (*(int *)(local_48[0x8c] + 0xe0) == 0) break;
  case 2:
    if (*(int *)(local_48[0x8c] + 0xe0) != 0) {
      *(undefined4 *)(local_48[0x8c] + 0xe0) = 0;
      local_48[0x8a] = 3;
      local_48[0xc0] = *(int *)(local_48[0x3e] + 0x34c);
      *(uint *)(local_48[0x3d] + 0x14) = *(uint *)(local_48[0x3d] + 0x14) & 0xfffffffe;
      *(uint *)(local_48[0x8c] + 0x114) = *(uint *)(local_48[0x8c] + 0x114) & 0xfffffffb;
      local_48[0x8d] = 0;
    }
    break;
  case 3:
    if (local_58 < 40.0) {
      local_48[0x8a] = 0;
      FUN_004376c0(local_48[0x3e] + 0x5e0,local_48[0x3d],0);
    }
    if (*(int *)(local_48[0x8c] + 0xe0) == 0) break;
  case 0:
    if (*(int *)(local_48[0x8c] + 0xe0) != 0) {
      *(undefined4 *)(local_48[0x8c] + 0xe0) = 0;
      local_48[0x8a] = 1;
      FUN_004376c0(local_48[0x3e] + 0x5d0,local_48[0x3d],0);
      local_48[0xc0] = *(int *)(local_48[0x3e] + 0x5f0);
    }
  }
  local_48[0xa0] = (int)(*(float *)(local_48[0x8c] + 200) * 0.5);
  if ((((*(uint *)(local_48[0x3d] + 0x14) & 0x10) != 0) && (iVar4 = FUN_004e96a0(), iVar4 != 0)) ||
     ((cVar1 = FUN_004b9830(), cVar1 != '\0' && ((*(uint *)(local_48[0x8c] + 0x114) & 0x1000) != 0))
     )) {
    local_48[0xa0] = (int)((float)local_48[0xa0] - *(float *)(local_54 + 0x1c));
  }
  (**(code **)(*local_48 + 0x9c))(param_2);
  FUN_004ab380(param_2);
  FUN_0083e885();
  return;
}

