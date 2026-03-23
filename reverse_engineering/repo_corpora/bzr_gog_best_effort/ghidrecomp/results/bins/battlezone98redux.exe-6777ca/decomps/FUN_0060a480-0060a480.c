
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0060a480(int param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  uint uVar6;
  float *pfVar7;
  undefined4 *puVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined1 local_220 [64];
  undefined1 local_1e0 [12];
  undefined1 local_1d4 [12];
  undefined1 local_1c8 [12];
  void *local_1bc;
  undefined4 local_1b8;
  float local_1b4;
  uint local_1b0;
  undefined4 local_1ac;
  int local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  uint local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  uint local_174;
  float local_170;
  uint local_16c;
  float local_168;
  uint local_164;
  uint local_160;
  _Order_node_base<enum_Concurrency::agent_status> *local_15c;
  float local_158;
  float local_154;
  uint local_150;
  float local_14c;
  undefined2 local_148;
  float local_144;
  float local_140;
  float local_13c;
  int local_138;
  int local_134;
  int local_130;
  float local_12c;
  uint local_128;
  int local_124;
  float local_120;
  char local_11c;
  char local_11b;
  char local_11a;
  char local_119;
  float *local_118;
  int local_114;
  undefined4 local_110 [16];
  undefined4 local_d0 [16];
  undefined4 local_90 [6];
  float local_78;
  float local_74;
  float local_70;
  double local_68;
  double local_60;
  double local_58;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_15c = *(_Order_node_base<enum_Concurrency::agent_status> **)(param_1 + 0xc);
  local_114 = param_1;
  local_124 = FUN_00417ca0();
  iVar3 = FUN_006217c0();
  if (iVar3 == 0) {
    local_148 = DAT_0091989c;
    memset(&DAT_0091989c,0,0x38);
    DAT_0091989c = local_148;
    local_1bc = (void *)(*(int *)(local_15c + 0x230) + 0xc4);
    memset(local_1bc,0,0x2c);
    *(undefined4 *)(local_114 + 0x78) = 0;
  }
  else if ((((DAT_009198b6 == '\0') && (DAT_009198bf == '\0')) && (DAT_009198be == '\0')) &&
          (DAT_009198c1 == '\0')) {
    *(undefined4 *)(local_114 + 0x78) = 0;
  }
  else {
    FUN_00609d10();
  }
  if ((((DAT_009198d1 != '\0') && (*(int *)(local_114 + 0x18) != 0)) &&
      ((iVar3 = (*(code *)**(undefined4 **)(*(int *)(local_114 + 0xc) + 0x18))(),
       *(int *)(iVar3 + 0x1c) == 6 ||
       (iVar3 = (*(code *)**(undefined4 **)(*(int *)(local_114 + 0xc) + 0x18))(),
       *(int *)(iVar3 + 0x1c) == 1)))) &&
     (((local_1ac = FUN_00462590(), *(int *)(*(int *)(local_114 + 0x18) + 0x13c) == -1 ||
       (*(int *)(*(int *)(local_114 + 0x18) + 0x140) == -1)) ||
      (iVar3 = FUN_005e0f90(*(undefined4 *)(*(int *)(local_114 + 0x18) + 0x13c),
                            *(undefined4 *)(*(int *)(local_114 + 0x18) + 0x140)), iVar3 != -1)))) {
    puVar4 = (undefined4 *)FUN_0045c4d0();
    puVar8 = local_90;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar8 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar8 = puVar8 + 1;
    }
    iVar3 = FUN_00462400();
    local_154 = *(float *)(iVar3 + 0xc);
    local_68 = local_68 - (double)(local_154 * local_78);
    local_60 = local_60 - (double)(local_154 * local_74);
    local_58 = local_58 - (double)(local_154 * local_70);
    uVar12 = 0;
    uVar11 = 0xffffffff;
    uVar10 = 0;
    uVar5 = (**(code **)(*(int *)(*(int *)(local_114 + 0xc) + 0x18) + 4))(0,0xffffffff,0);
    local_130 = FUN_004e1190(local_90,uVar5,uVar10,uVar11,uVar12);
    cVar1 = FUN_00571c40();
    if (cVar1 != '\0') {
      FUN_004b8460();
    }
    *(uint *)(*(int *)(local_130 + 0x228) + 0x114) =
         *(uint *)(*(int *)(local_130 + 0x228) + 0x114) | 4;
    uVar5 = (**(code **)(*(int *)(local_130 + 0x18) + 0x30))(0);
    FUN_004376c0("gprox00.wav",uVar5);
  }
  if (local_124 != 0) {
    local_128 = FUN_00417f90();
    local_1b0 = FUN_00417fb0();
    for (local_138 = 0; local_138 < 5; local_138 = local_138 + 1) {
      local_150 = 1 << ((byte)local_138 & 0x1f);
      uVar6 = local_128;
      if ((((local_1b0 & local_150) != 0) && ((&DAT_009198c5)[local_138] != '\0')) &&
         (uVar6 = local_150, DAT_00919875 != '\0')) {
        uVar6 = local_128 ^ local_150;
      }
      local_128 = uVar6;
    }
    if (DAT_009198c3 != '\0') {
      local_160 = (uint)(*(int *)(local_114 + 0x20) == 0);
      *(uint *)(local_114 + 0x20) = local_160;
      local_128 = *(uint *)(local_114 + 0x24 + *(int *)(local_114 + 0x20) * 0x14 +
                           *(int *)(local_114 + 0x1c) * 4);
    }
    if (DAT_009198c2 != '\0') {
      *(undefined4 *)(local_114 + 0x1c) =
           *(undefined4 *)
            (local_114 + 0x4c + *(int *)(local_114 + 0x20) * 0x14 + *(int *)(local_114 + 0x1c) * 4);
      local_128 = *(uint *)(local_114 + 0x24 + *(int *)(local_114 + 0x20) * 0x14 +
                           *(int *)(local_114 + 0x1c) * 4);
    }
    uVar6 = FUN_00417f90();
    if (local_128 != uVar6) {
      FUN_0043aa30("cammo.wav",0,0,0);
      FUN_004d9880(local_128);
      FUN_0060a240();
    }
    bVar2 = Concurrency::_Order_node_base<enum_Concurrency::agent_status>::has_value(local_15c);
    if (!bVar2) {
      local_119 = DAT_009198c0 != '\0';
      local_164 = (uint)(byte)local_119;
      if ((!(bool)local_119) && (DAT_009198c1 != '\0')) {
        local_11c = '\x01';
        for (local_134 = 0; local_134 < 5; local_134 = local_134 + 1) {
          if (((1 << ((byte)local_134 & 0x1f) & local_128) != 0) &&
             (local_1a8 = FUN_00417f60(local_134), *(char *)(*(int *)(local_1a8 + 8) + 0x79) == '\0'
             )) {
            local_11c = '\0';
            break;
          }
        }
        if ((*(int *)(local_114 + 0x78) != 0) && (local_11c != '\0')) {
          local_11b = '\0';
          local_1b8 = *(undefined4 *)(local_114 + 0xc);
          fVar9 = (float10)FUN_005ba130();
          puVar4 = (undefined4 *)FUN_0081ec40(local_220,(float)fVar9);
          puVar8 = local_110;
          for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar8 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar8 = puVar8 + 1;
          }
          puVar4 = local_110;
          puVar8 = local_d0;
          for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar8 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar8 = puVar8 + 1;
          }
          puVar4 = (undefined4 *)FUN_00440210(local_1c8,local_114 + 0x7c,local_d0);
          local_2c = *puVar4;
          local_28 = puVar4[1];
          local_24 = (float)puVar4[2];
          local_14 = local_2c;
          local_10 = local_28;
          local_c = local_24;
          local_119 = FUN_0060a320(&local_11b,&local_2c);
          if (local_119 != '\0') {
            if (local_11b == '\0') {
              cVar1 = FUN_00462b60(*(undefined4 *)(local_114 + 0xc),
                                   *(float *)(local_114 + 0x74) * *(float *)(local_114 + 0x74),
                                   0x3e99999a,0x3f800000);
              local_119 = cVar1 == '\0';
              local_174 = (uint)(byte)local_119;
            }
            else {
              cVar1 = FUN_00462b60(*(undefined4 *)(local_114 + 0xc),local_24 * local_24,0x3e99999a,
                                   0x3f800000);
              local_119 = cVar1 == '\0';
              local_16c = (uint)(byte)local_119;
            }
          }
        }
      }
      if (local_119 != '\0') {
        FUN_00511fc0();
      }
      if (DAT_009198c4 != '\0') {
        FUN_00608aa0();
      }
    }
  }
  fVar9 = (float10)FUN_00822d60();
  local_120 = (float)fVar9;
  local_118 = (float *)(*(int *)(*(int *)(local_114 + 0xc) + 0x230) + 0xc4);
  if ((DAT_009198b6 == '\0') || (*(int *)(local_114 + 0x78) == 0)) {
    if ((DAT_009198b4 == '\0') && (DAT_009198b5 == '\0')) {
      local_158 = (float)_DAT_009198b0 / 65536.0;
      if (DAT_009198f4 == 0) {
        *local_118 = (local_158 - *local_118) * 5.0 * local_120 + *local_118;
      }
      else {
        *local_118 = local_158;
      }
    }
    else {
      local_194 = (float)((int)DAT_009198b5 - (int)DAT_009198b4);
      if (DAT_009198f4 == 0) {
        *local_118 = (local_194 - *local_118) * 1.0 * local_120 + *local_118;
      }
      else {
        *local_118 = local_194;
      }
    }
  }
  else {
    if ((DAT_009198b4 == '\0') && (DAT_009198b5 == '\0')) {
      local_14c = (float)_DAT_009198b0 / 65536.0;
    }
    else {
      local_14c = (float)((int)DAT_009198b5 - (int)DAT_009198b4);
    }
    fVar9 = (float10)FUN_0046e0a0(*(undefined4 *)(local_114 + 0x7c),
                                  *(undefined4 *)(local_114 + 0x84));
    local_19c = (float)fVar9;
    puVar4 = (undefined4 *)FUN_004624b0();
    puVar4 = (undefined4 *)FUN_004624b0(*puVar4,puVar4[1],puVar4[2]);
    puVar4 = (undefined4 *)FUN_004401a0(local_1d4,*puVar4,puVar4[1],puVar4[2]);
    local_50 = *puVar4;
    local_4c = puVar4[1];
    local_48 = puVar4[2];
    local_38 = local_50;
    local_34 = local_4c;
    local_30 = local_48;
    uVar5 = FUN_0045c4d0();
    pfVar7 = (float *)FUN_00440300(local_1e0,&local_50,uVar5);
    local_44 = *pfVar7;
    local_40 = pfVar7[1];
    local_3c = pfVar7[2];
    local_17c = (local_3c * *(float *)(local_114 + 0x7c) - local_44 * *(float *)(local_114 + 0x84))
                / (*(float *)(local_114 + 0x7c) * *(float *)(local_114 + 0x7c) +
                  *(float *)(local_114 + 0x84) * *(float *)(local_114 + 0x84));
    local_1a4 = local_17c * 0.3;
    local_20 = local_44;
    local_1c = local_40;
    local_18 = local_3c;
    iVar3 = FUN_0045c490(0xbf800000,0x3f800000);
    fVar9 = (float10)FUN_00447ed0(local_1a4 +
                                  ((local_17c - *(float *)(iVar3 + 0x28)) * 0.3 - local_19c) * 5.0);
    local_184 = (float)fVar9;
    local_1b4 = local_14c - local_184;
    fVar9 = (float10)FUN_00453f80(local_14c);
    local_198 = (float)fVar9;
    local_18c = local_1b4 * local_198 + local_184;
    if (DAT_009198f4 == 0) {
      *local_118 = (local_18c - *local_118) * 5.0 * local_120 + *local_118;
    }
    else {
      *local_118 = local_18c;
    }
  }
  local_11a = '\0';
  if (((DAT_009198bf != '\0') || (DAT_009198be != '\0')) && (*(int *)(local_114 + 0x78) != 0)) {
    local_11a = '\x01';
    if ((DAT_009198bc == '\0') && (DAT_009198bd == '\0')) {
      local_12c = (float)_DAT_009198b8 / 65536.0;
      if ((*(uint *)(DAT_0094672c + 0x30) & 0x40) != 0) {
        local_12c = -local_12c;
      }
    }
    else {
      local_12c = (float)((int)DAT_009198bd - (int)DAT_009198bc);
    }
    fVar9 = (float10)FUN_0045c420(*(undefined4 *)(local_114 + 0x7c),
                                  *(undefined4 *)(local_114 + 0x80),
                                  *(undefined4 *)(local_114 + 0x84));
    local_1a0 = (float)fVar9;
    fVar9 = (float10)FUN_00608a60(*(float *)(local_114 + 0x80) / local_1a0);
    local_144 = (float)fVar9;
    iVar3 = FUN_004e96a0();
    if (iVar3 != 0) {
      iVar3 = FUN_0045c4d0();
      local_144 = local_144 + *(float *)(iVar3 + 0x1c);
    }
    fVar9 = (float10)FUN_00447ed0(local_144 * 2.0,0xbf800000,0x3f800000);
    local_13c = (float)fVar9;
    if (((local_12c != 0.0) || (DAT_009198bf == '\0')) &&
       ((0.1 < local_12c - local_13c || (0.1 < local_13c - local_12c)))) {
      local_11a = '\0';
    }
    if (local_11a != '\0') {
      if (DAT_009198f4 == 0) {
        local_118[1] = (local_13c - local_118[1]) * 5.0 * local_120 + local_118[1];
      }
      else {
        local_118[1] = local_13c;
      }
    }
  }
  if (local_11a == '\0') {
    if ((DAT_009198bc == '\0') && (DAT_009198bd == '\0')) {
      local_140 = (float)_DAT_009198b8 / 65536.0;
      if ((*(uint *)(DAT_0094672c + 0x30) & 0x40) != 0) {
        local_140 = -local_140;
      }
      if (DAT_009198f4 == 0) {
        local_118[1] = (local_140 - local_118[1]) * 5.0 * local_120 + local_118[1];
      }
      else {
        local_118[1] = local_140;
      }
    }
    else {
      local_178 = (float)((int)DAT_009198bd - (int)DAT_009198bc);
      if (DAT_009198f4 == 0) {
        local_118[1] = (local_178 - local_118[1]) * 1.0 * local_120 + local_118[1];
      }
      else {
        local_118[1] = local_178;
      }
    }
  }
  if ((DAT_009198a4 == '\0') && (DAT_009198a5 == '\0')) {
    local_168 = (float)DAT_009198a0 / 65536.0;
    if (DAT_009198f4 == 0) {
      local_118[3] = (local_168 - local_118[3]) * 3.0 * local_120 + local_118[3];
    }
    else {
      local_118[3] = local_168;
    }
  }
  else {
    local_188 = (float)((int)DAT_009198a4 - (int)DAT_009198a5);
    if (DAT_009198f4 == 0) {
      local_118[3] = (local_188 - local_118[3]) * 3.0 * local_120 + local_118[3];
    }
    else {
      local_118[3] = local_188;
    }
  }
  if ((DAT_009198ac == '\0') && (DAT_009198ad == '\0')) {
    local_170 = (float)DAT_009198a8 / 65536.0;
    if (DAT_009198f4 == 0) {
      local_118[2] = (local_170 - local_118[2]) * 3.0 * local_120 + local_118[2];
    }
    else {
      local_118[2] = local_170;
    }
  }
  else {
    local_180 = (float)((int)DAT_009198ac - (int)DAT_009198ad);
    if (DAT_009198f4 == 0) {
      local_118[2] = (local_180 - local_118[2]) * 3.0 * local_120 + local_118[2];
    }
    else {
      local_118[2] = local_180;
    }
  }
  iVar3 = FUN_00594280(DAT_009198a8);
  if ((iVar3 < DAT_009198a0) && (iVar3 = FUN_00594280(DAT_009198a8), 0xf000 < iVar3 + DAT_009198a0))
  {
    local_190 = 1;
  }
  else {
    local_190 = 0;
  }
  local_118[4] = (float)((int)DAT_009198ca | local_190);
  local_118[5] = 0.0;
  if (DAT_009198cb != '\0') {
    local_118[5] = (float)(int)DAT_009198cb;
  }
  local_118[6] = (float)(int)DAT_009198cd;
  local_118[7] = (float)(int)DAT_009198cc;
  local_118[8] = (float)(int)DAT_009198ce;
  cVar1 = FUN_00417dd0();
  if (cVar1 != '\0') {
    local_118[10] = (float)(int)DAT_009198d2;
  }
  FUN_0083e885();
  return;
}

