
void FUN_004675f0(int param_1,undefined4 *param_2,float param_3,float *param_4)

{
  char cVar1;
  undefined1 uVar2;
  float *pfVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  float10 fVar9;
  undefined1 local_178 [12];
  undefined1 local_16c [12];
  undefined1 local_160 [12];
  undefined1 local_154 [12];
  undefined1 local_148 [12];
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  undefined4 local_12c;
  int local_128;
  float local_124;
  int local_120;
  int local_11c;
  int local_118;
  float local_114;
  int local_110;
  float local_10c;
  int local_108;
  float local_104;
  float local_100;
  uint local_fc;
  int local_f8;
  uint local_f4;
  int local_f0;
  uint local_ec;
  int local_e8;
  uint local_e4;
  int local_e0;
  uint local_dc;
  int local_d8;
  uint local_d4;
  uint local_d0;
  float local_cc;
  float local_c8;
  float *local_c4;
  float local_c0;
  float local_bc;
  int local_b8;
  uint local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  uint local_a4;
  int local_a0;
  char local_9b;
  char local_9a;
  char local_99;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  float local_8c;
  undefined4 local_88;
  float local_84;
  float local_80;
  undefined4 local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_12c = *(undefined4 *)(param_1 + 0x234);
  local_99 = '\0';
  pfVar3 = (float *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_80 = *pfVar3;
  local_78 = pfVar3[2];
  local_7c = 0;
  puVar4 = (undefined4 *)FUN_004624b0();
  local_14 = *puVar4;
  local_c = puVar4[2];
  local_10 = 0;
  FUN_00461fd0(local_80 * DAT_02cc50e4);
  local_b0 = FUN_0083f040();
  FUN_00461fd0(local_78 * DAT_02cc50e4);
  local_b8 = FUN_0083f040();
  pfVar3 = (float *)FUN_004401a0(local_148,*param_2,param_2[1],param_2[2],local_80,local_7c,local_78
                                );
  local_44 = *pfVar3;
  local_40 = pfVar3[1];
  local_3c = pfVar3[2];
  local_74 = 0.0;
  local_70 = 0.0;
  local_6c = 0.0;
  local_8c = ((float)local_b0 + 0.5) * DAT_02cc50e0;
  local_88 = 0;
  local_84 = ((float)local_b8 + 0.5) * DAT_02cc50e0;
  local_20 = local_44;
  local_1c = local_40;
  local_18 = local_3c;
  pfVar3 = (float *)FUN_004401a0(local_16c,local_8c,0,local_84,local_80,local_7c,local_78);
  local_68 = *pfVar3;
  local_64 = pfVar3[1];
  local_60 = pfVar3[2];
  local_a4 = 0;
  local_5c = local_68;
  local_58 = local_64;
  local_54 = local_60;
  fVar9 = (float10)FUN_00453f80(local_20);
  local_138 = (float)fVar9;
  local_114 = local_138;
  fVar9 = (float10)FUN_00453f80(local_18);
  local_100 = (float)fVar9;
  if (local_114 <= local_100) {
    if (local_18 <= 0.0) {
      local_e8 = 2;
    }
    else {
      local_e8 = 0;
    }
    local_a8 = local_e8;
  }
  else {
    if (local_20 <= 0.0) {
      local_f0 = 3;
    }
    else {
      local_f0 = 1;
    }
    local_a8 = local_f0;
  }
  local_11c = local_a8;
  local_128 = local_a8 << 1;
  iVar5 = (**(code **)(*(int *)(param_1 + 0x18) + 0x2c))();
  local_c4 = (float *)(iVar5 + 0x44);
  fVar9 = (float10)FUN_00456080(0,local_14);
  local_130 = (float)fVar9;
  FUN_00461fd0((local_130 + *local_c4) * DAT_02cc50e4);
  uVar6 = FUN_0083f040();
  local_118 = FUN_0046b550(local_b0 + -1,uVar6);
  fVar9 = (float10)FUN_00456080(0,local_c);
  local_124 = (float)fVar9;
  FUN_00461fd0((local_124 + local_c4[2]) * DAT_02cc50e4);
  uVar6 = FUN_0083f040();
  local_108 = FUN_0046b550(local_b8 + -1,uVar6);
  fVar9 = (float10)FUN_0044fb20(0,local_14);
  local_134 = (float)fVar9;
  FUN_00461fd0((local_134 + local_c4[3]) * DAT_02cc50e4);
  uVar6 = FUN_0083f040();
  local_120 = FUN_0043d130(local_b0 + 1,uVar6);
  fVar9 = (float10)FUN_0044fb20(0,local_c);
  local_104 = (float)fVar9;
  FUN_00461fd0((local_104 + local_c4[5]) * DAT_02cc50e4);
  uVar6 = FUN_0083f040();
  local_110 = FUN_0043d130(local_b8 + 1,uVar6);
  for (local_ac = local_108; local_ac <= local_110; local_ac = local_ac + 1) {
    for (local_a0 = local_118; local_a0 <= local_120; local_a0 = local_a0 + 1) {
      local_8c = ((float)local_a0 + 0.5) * DAT_02cc50e0;
      local_84 = ((float)local_ac + 0.5) * DAT_02cc50e0;
      puVar4 = (undefined4 *)
               FUN_004401a0(local_154,local_80,local_7c,local_78,local_8c,local_88,local_84);
      local_98 = *puVar4;
      local_94 = puVar4[1];
      local_90 = puVar4[2];
      local_50 = local_98;
      local_4c = local_94;
      local_48 = local_90;
      fVar9 = (float10)FUN_004428b0(&local_98,&local_98);
      local_bc = (float)fVar9;
      if ((0.0001 < local_bc) && (local_bc <= param_3 * param_3)) {
        uVar8 = local_a0 - local_b0 >> 0x1f;
        if (local_ac - local_b8 < (int)(((local_a0 - local_b0 ^ uVar8) - uVar8) * 2)) {
          uVar8 = local_a0 - local_b0 >> 0x1f;
          if ((local_ac - local_b8) * 2 < (int)((local_a0 - local_b0 ^ uVar8) - uVar8)) {
            iVar7 = (local_ac - local_b8) * 2;
            uVar8 = local_a0 - local_b0 >> 0x1f;
            iVar5 = (local_a0 - local_b0 ^ uVar8) - uVar8;
            if (iVar7 + iVar5 == 0 || iVar7 < -iVar5) {
              uVar8 = local_a0 - local_b0 >> 0x1f;
              if ((int)(((local_a0 - local_b0 ^ uVar8) - uVar8) * -2) < local_ac - local_b8) {
                if (local_b0 < local_a0) {
                  local_e0 = 3;
                }
                else {
                  local_e0 = 5;
                }
                local_b4 = local_e0;
              }
              else {
                local_b4 = 4;
              }
            }
            else {
              if (local_b0 < local_a0) {
                local_f8 = 2;
              }
              else {
                local_f8 = 6;
              }
              local_b4 = local_f8;
            }
          }
          else {
            if (local_b0 < local_a0) {
              local_d8 = 1;
            }
            else {
              local_d8 = 7;
            }
            local_b4 = local_d8;
          }
        }
        else {
          local_b4 = 0;
        }
        local_b4 = local_b4 - local_128 & 7;
        cVar1 = FUN_004675d0(local_a0,local_ac,local_12c);
        if (cVar1 != '\0') {
          local_a4 = 1 << ((byte)local_b4 & 0x1f) | local_a4;
        }
        uVar2 = FUN_0046acc0(local_a0,local_ac);
        iVar5 = FUN_00591670(uVar2);
        local_cc = *(float *)(&DAT_008e7688 + iVar5 * 4);
        if (local_cc != 0.0) {
          fVar9 = (float10)FUN_00462470(0x40e00000);
          fVar9 = (float10)FUN_0044fb20((float)fVar9);
          local_c0 = (float)fVar9;
          local_c8 = local_cc;
          if (local_c0 * local_c0 < local_bc) {
            local_c8 = ((local_c0 * local_c0) / local_bc) * local_cc;
          }
          fVar9 = (float10)FUN_00820570((double)local_bc,local_98,local_94,local_90);
          local_13c = (float)fVar9;
          local_10c = local_13c;
          pfVar3 = (float *)FUN_00439d00(local_160,local_74,local_70);
          local_74 = *pfVar3;
          local_70 = pfVar3[1];
          local_6c = pfVar3[2];
          local_99 = '\x01';
          local_38 = local_74;
          local_34 = local_70;
          local_30 = local_6c;
        }
      }
    }
  }
  local_9b = param_3 * param_3 < 225.0;
  local_d0 = (uint)(byte)local_9b;
  local_9a = '\0';
  if ((local_a4 != 0) || (local_99 != '\0')) {
    cVar1 = FUN_00467440(local_a4,0x83,4,0xffffffff,local_a8,param_1,&local_74);
    if (cVar1 == '\0') {
      cVar1 = FUN_00467440(local_a4,0x81,0x46,0xffffffff,local_a8,param_1,&local_74);
      if (cVar1 == '\0') {
        cVar1 = FUN_00467440(local_a4,3,0xc4,0xffffffff,local_a8,param_1,&local_74);
        if (cVar1 == '\0') {
          cVar1 = FUN_00467440(local_a4,0x82,1,0,local_a8,param_1,&local_74);
          if (cVar1 == '\0') {
            cVar1 = FUN_00467440(local_a4,6,0xc1,3,local_a8,param_1,&local_74);
            if (cVar1 == '\0') {
              cVar1 = FUN_00467440(local_a4,0xc0,7,1,local_a8,param_1,&local_74);
              if (cVar1 == '\0') {
                cVar1 = FUN_00467440(local_a4,0x80,3,0,local_a8,param_1,&local_74);
                if (cVar1 == '\0') {
                  cVar1 = FUN_00467440(local_a4,2,0x81,0,local_a8,param_1,&local_74);
                  if (cVar1 != '\0') {
                    local_9a = local_9b == '\0';
                    local_fc = (uint)(byte)local_9a;
                    local_99 = '\x01';
                  }
                }
                else {
                  local_9a = local_9b == '\0';
                  local_f4 = (uint)(byte)local_9a;
                  local_99 = '\x01';
                }
              }
              else {
                local_99 = '\x01';
              }
            }
            else {
              local_99 = '\x01';
            }
          }
          else {
            local_9a = local_9b == '\0';
            local_ec = (uint)(byte)local_9a;
            local_99 = '\x01';
          }
        }
        else {
          local_9a = local_9b == '\0';
          local_e4 = (uint)(byte)local_9a;
          local_99 = '\x01';
        }
      }
      else {
        local_9a = local_9b == '\0';
        local_dc = (uint)(byte)local_9a;
        local_99 = '\x01';
      }
    }
    else {
      local_9a = local_9b == '\0';
      local_d4 = (uint)(byte)local_9a;
      local_99 = '\x01';
    }
  }
  if (local_9a == '\0') {
    pfVar3 = (float *)FUN_00440130(local_178,*param_4,param_4[1],param_4[2],local_74,local_70,
                                   local_6c);
    local_2c = *pfVar3;
    local_28 = pfVar3[1];
    local_24 = pfVar3[2];
    *param_4 = local_2c;
    param_4[1] = local_28;
    param_4[2] = local_24;
  }
  else {
    local_6c = local_6c + local_60;
    local_74 = local_74 + local_68;
    *param_4 = local_74;
    param_4[1] = local_70;
    param_4[2] = local_6c;
  }
  FUN_0083e885();
  return;
}

