
void __fastcall FUN_004f95d0(int param_1)

{
  char cVar1;
  float *pfVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  float10 fVar6;
  undefined1 local_158 [12];
  double local_14c;
  double local_144;
  int local_13c;
  int local_138;
  int local_134;
  int local_130;
  int local_12c;
  int local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  int local_110;
  float local_10c;
  int local_108;
  int local_104;
  uint local_100;
  float local_fc;
  int local_f8;
  byte local_f1;
  float *local_f0;
  float local_ec;
  undefined4 *local_e8;
  undefined2 *local_e4;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_f8 = param_1;
  if ((((DAT_02cf4000 != 0) && (DAT_008eaad8 != 9)) && (DAT_008eaad8 != 10)) && (DAT_02cecf74 == 0))
  {
    local_f0 = (float *)FUN_00439e60();
    pfVar2 = (float *)FUN_00440210(local_158,&DAT_02ceb830,local_f0 + 0x10);
    local_20 = *pfVar2;
    local_1c = pfVar2[1];
    local_18 = pfVar2[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    if (local_f0[0x42] <= local_18) {
      local_120 = 1.0 / local_18;
      local_108 = (int)(local_f0[2] * local_120 * local_20 + *local_f0);
      local_104 = (int)(local_f0[3] * local_120 * local_1c + local_f0[1]);
      local_fc = local_f0[0xe];
      local_12c = (*(int *)((int)local_fc + 8) + *(int *)((int)local_fc + 0x10)) / 2;
      local_128 = (*(int *)((int)local_fc + 0xc) + *(int *)((int)local_fc + 0x14)) / 2;
      if (((*(int *)((int)local_fc + 8) <= local_108) &&
          (local_108 <= *(int *)((int)local_fc + 0x10))) &&
         ((*(int *)((int)local_fc + 0xc) <= local_104 &&
          (local_104 <= *(int *)((int)local_fc + 0x14))))) {
        FUN_00685460();
        cVar1 = FUN_0048efc0();
        if (cVar1 != '\0') {
          local_110 = (int)(local_f0[2] * local_120 * 0.00436332);
          fVar6 = (float10)FUN_004f90a0(local_f0,(float)(local_108 - local_110));
          local_10c = (float)fVar6;
          fVar6 = (float10)FUN_004f90a0(local_f0,(float)(local_108 + 1 + local_110));
          local_114 = (float)fVar6;
          fVar6 = (float10)FUN_004f90f0(local_f0,(float)(local_104 - local_110));
          local_118 = (float)fVar6;
          fVar6 = (float10)FUN_004f90f0(local_f0,(float)(local_104 + 1 + local_110));
          local_11c = (float)fVar6;
          local_f1 = FUN_00685560();
          FUN_00685580(local_f1 + 1);
          uVar3 = FUN_00685620(local_f8 + 0x30,0,4,6);
          *(undefined4 *)(local_f8 + 0x40) = uVar3;
          local_e8 = (undefined4 *)FUN_006856a0(4);
          puVar4 = (undefined4 *)FUN_00446360(local_10c,local_118,0x3f800000,0xffffffff,0,0);
          *local_e8 = *puVar4;
          local_e8[1] = puVar4[1];
          local_e8[2] = puVar4[2];
          local_e8[3] = puVar4[3];
          local_e8[4] = puVar4[4];
          local_e8[5] = puVar4[5];
          local_e8 = local_e8 + 6;
          puVar4 = (undefined4 *)
                   FUN_00446360(local_114,local_118,0x3f800000,0xffffffff,0x3f800000,0);
          *local_e8 = *puVar4;
          local_e8[1] = puVar4[1];
          local_e8[2] = puVar4[2];
          local_e8[3] = puVar4[3];
          local_e8[4] = puVar4[4];
          local_e8[5] = puVar4[5];
          local_e8 = local_e8 + 6;
          puVar4 = (undefined4 *)
                   FUN_00446360(local_114,local_11c,0x3f800000,0xffffffff,0x3f800000,0x3f800000);
          *local_e8 = *puVar4;
          local_e8[1] = puVar4[1];
          local_e8[2] = puVar4[2];
          local_e8[3] = puVar4[3];
          local_e8[4] = puVar4[4];
          local_e8[5] = puVar4[5];
          local_e8 = local_e8 + 6;
          puVar4 = (undefined4 *)
                   FUN_00446360(local_10c,local_11c,0x3f800000,0xffffffff,0,0x3f800000);
          *local_e8 = *puVar4;
          local_e8[1] = puVar4[1];
          local_e8[2] = puVar4[2];
          local_e8[3] = puVar4[3];
          local_e8[4] = puVar4[4];
          local_e8[5] = puVar4[5];
          local_e8 = local_e8 + 6;
          local_e4 = (undefined2 *)FUN_006856c0(6);
          *local_e4 = 0;
          local_e4[1] = 2;
          local_e4[2] = 1;
          local_e4[3] = 0;
          local_e4[4] = 3;
          local_e4[5] = 2;
          local_e4 = local_e4 + 6;
          FUN_006856e0();
          uVar3 = FUN_00685620(local_f8 + 0x38,0,4,6);
          *(undefined4 *)(local_f8 + 0x44) = uVar3;
          local_e8 = (undefined4 *)FUN_006856a0(4);
          puVar4 = (undefined4 *)FUN_00446360(local_10c,local_118,0x3f800000,0xffffffff,0,0);
          *local_e8 = *puVar4;
          local_e8[1] = puVar4[1];
          local_e8[2] = puVar4[2];
          local_e8[3] = puVar4[3];
          local_e8[4] = puVar4[4];
          local_e8[5] = puVar4[5];
          local_e8 = local_e8 + 6;
          puVar4 = (undefined4 *)
                   FUN_00446360(local_114,local_118,0x3f800000,0xffffffff,0x3f800000,0);
          *local_e8 = *puVar4;
          local_e8[1] = puVar4[1];
          local_e8[2] = puVar4[2];
          local_e8[3] = puVar4[3];
          local_e8[4] = puVar4[4];
          local_e8[5] = puVar4[5];
          local_e8 = local_e8 + 6;
          puVar4 = (undefined4 *)
                   FUN_00446360(local_114,local_11c,0x3f800000,0xffffffff,0x3f800000,0x3f800000);
          *local_e8 = *puVar4;
          local_e8[1] = puVar4[1];
          local_e8[2] = puVar4[2];
          local_e8[3] = puVar4[3];
          local_e8[4] = puVar4[4];
          local_e8[5] = puVar4[5];
          local_e8 = local_e8 + 6;
          puVar4 = (undefined4 *)
                   FUN_00446360(local_10c,local_11c,0x3f800000,0xffffffff,0,0x3f800000);
          *local_e8 = *puVar4;
          local_e8[1] = puVar4[1];
          local_e8[2] = puVar4[2];
          local_e8[3] = puVar4[3];
          local_e8[4] = puVar4[4];
          local_e8[5] = puVar4[5];
          local_e8 = local_e8 + 6;
          local_e4 = (undefined2 *)FUN_006856c0(6);
          *local_e4 = 0;
          local_e4[1] = 2;
          local_e4[2] = 1;
          local_e4[3] = 0;
          local_e4[4] = 3;
          local_e4[5] = 2;
          local_e4 = local_e4 + 6;
          FUN_006856e0();
          FUN_00685580(local_f1);
          if (*(int *)(local_f8 + 0x48) != 0) {
            local_ec = local_c * local_c * local_c * local_c;
            local_ec = local_ec * local_ec;
            local_ec = local_ec * local_ec;
            local_ec = local_ec * local_ec;
            local_130 = *(int *)(local_f8 + 0x48);
            local_144 = (double)local_130 + (double)(&DAT_008a2fd0)[-(local_130 >> 0x1f)];
            FUN_0049b4c0((float)local_144 * local_ec * *(float *)(local_f8 + 0x4c));
            local_134 = *(int *)(local_f8 + 0x48) * 0xff;
            local_14c = (double)local_134 + (double)(&DAT_008a2fd0)[-(local_134 >> 0x1f)];
            FUN_00417990((int)((float)local_14c * *(float *)(local_f8 + 0x4c)) << 0x18 | 0xffffff);
            local_124 = ((float)*(int *)((int)local_fc + 4) * local_f0[0xc]) / 480.0;
            for (local_100 = 0; local_100 < 6; local_100 = local_100 + 1) {
              iVar5 = FUN_0068f090(*(undefined4 *)(&DAT_008e8698 + local_100 * 0xc));
              local_13c = (int)((float)iVar5 * local_124);
              iVar5 = FUN_0068f0c0(*(undefined4 *)(&DAT_008e8698 + local_100 * 0xc));
              local_138 = (int)((float)iVar5 * local_124);
              FUN_0068ce80(local_f0,*(undefined4 *)(&DAT_008e8698 + local_100 * 0xc),
                           ((local_108 - local_12c) * *(int *)(&DAT_008e8694 + local_100 * 0xc) >> 8
                           ) + local_12c,
                           ((local_104 - local_128) * *(int *)(&DAT_008e8694 + local_100 * 0xc) >> 8
                           ) + local_128,DAT_00920ef4,local_13c,local_138,0x250005);
            }
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

