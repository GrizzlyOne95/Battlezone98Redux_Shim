
/* WARNING: Removing unreachable block (ram,0x00458f6b) */

void FUN_00458d70(int param_1)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined8 uVar6;
  undefined1 local_e8 [16];
  undefined4 local_d8;
  int local_d4;
  undefined8 local_d0;
  float local_c8;
  undefined8 local_c4;
  float local_bc;
  undefined4 local_b4;
  int local_b0;
  float local_ac;
  uint local_a8;
  undefined4 *local_a4;
  int local_a0;
  short *local_9c;
  float local_98;
  float local_94;
  undefined4 local_90;
  float local_8c;
  float local_88;
  undefined4 local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_d8 = 2;
  iVar1 = FUN_00684ca0();
  if (iVar1 != 0) {
    iVar1 = FUN_004170c0();
    if (iVar1 != 0) {
      local_c8 = *(float *)(param_1 + 0x30) / (*(float *)(param_1 + 0x28) * 0.0025);
      FUN_00447e20();
      while( true ) {
        iVar1 = FUN_00447e70();
        FUN_00447e50();
        iVar2 = FUN_00447e70();
        if (iVar1 == iVar2) break;
        local_d4 = FUN_00447e70();
        local_a0 = local_d4;
        FUN_00447e90();
        if (*(char *)(local_a0 + 0x1c) != '\0') {
          pfVar3 = (float *)FUN_006897e0(local_e8,param_1,*(undefined8 *)(local_a0 + 0x48),
                                         *(undefined8 *)(local_a0 + 0x50),
                                         *(undefined8 *)(local_a0 + 0x58));
          local_80 = *pfVar3;
          local_7c = pfVar3[1];
          local_78 = pfVar3[2];
          local_14 = local_80;
          local_10 = local_7c;
          local_c = local_78;
          iVar1 = FUN_006895d0();
          if (iVar1 < 1) {
            fVar5 = (float10)FUN_00447ed0();
            local_bc = (float)fVar5;
            fVar5 = (float10)FUN_004497c0();
            local_ac = (float)fVar5;
            if (local_78 <= local_ac * local_c8) {
              FUN_006855e0(local_b0 + 0x144,local_78 - local_ac);
              local_b4 = FUN_00685670(4,6);
              local_a4 = (undefined4 *)FUN_006856a0();
              local_9c = (short *)FUN_006856c0();
              local_a8 = FUN_00449690();
              if (*(int *)(local_a0 + 0x78) != -1) {
                local_a8 = ((local_a8 >> 0x18) * (*(uint *)(local_a0 + 0x78) >> 0x18)) / 0xff <<
                           0x18 | (((local_a8 >> 0x10 & 0xff) *
                                   (*(uint *)(local_a0 + 0x78) >> 0x10 & 0xff)) / 0xff & 0xff) <<
                                  0x10 |
                           (((local_a8 >> 8 & 0xff) * (*(uint *)(local_a0 + 0x78) >> 8 & 0xff)) /
                            0xff & 0xff) << 8 |
                           ((local_a8 & 0xff) * (*(uint *)(local_a0 + 0x78) & 0xff)) / 0xff & 0xff;
              }
              uVar6 = FUN_008205a0();
              local_88 = (float)((ulonglong)uVar6 >> 0x20);
              local_98 = local_ac * local_88;
              local_94 = local_ac * (float)uVar6;
              local_90 = 0;
              local_8c = -local_ac * (float)uVar6;
              local_88 = local_ac * local_88;
              local_84 = 0;
              local_d0 = uVar6;
              local_c4 = uVar6;
              puVar4 = (undefined4 *)
                       FUN_00446360((local_80 - local_98) + local_8c,
                                    (local_7c - local_94) + local_88,-local_78,local_a8,0,0);
              *local_a4 = *puVar4;
              local_a4[1] = puVar4[1];
              local_a4[2] = puVar4[2];
              local_a4[3] = puVar4[3];
              local_a4[4] = puVar4[4];
              local_a4[5] = puVar4[5];
              local_a4 = local_a4 + 6;
              puVar4 = (undefined4 *)
                       FUN_00446360(local_80 + local_98 + local_8c,local_7c + local_94 + local_88,
                                    -local_78,local_a8,0x3f800000,0);
              *local_a4 = *puVar4;
              local_a4[1] = puVar4[1];
              local_a4[2] = puVar4[2];
              local_a4[3] = puVar4[3];
              local_a4[4] = puVar4[4];
              local_a4[5] = puVar4[5];
              local_a4 = local_a4 + 6;
              puVar4 = (undefined4 *)
                       FUN_00446360((local_80 + local_98) - local_8c,
                                    (local_7c + local_94) - local_88,-local_78,local_a8,0x3f800000,
                                    0x3f800000);
              *local_a4 = *puVar4;
              local_a4[1] = puVar4[1];
              local_a4[2] = puVar4[2];
              local_a4[3] = puVar4[3];
              local_a4[4] = puVar4[4];
              local_a4[5] = puVar4[5];
              local_a4 = local_a4 + 6;
              puVar4 = (undefined4 *)
                       FUN_00446360((local_80 - local_98) - local_8c,
                                    (local_7c - local_94) - local_88,-local_78,local_a8,0,0x3f800000
                                   );
              *local_a4 = *puVar4;
              local_a4[1] = puVar4[1];
              local_a4[2] = puVar4[2];
              local_a4[3] = puVar4[3];
              local_a4[4] = puVar4[4];
              local_a4[5] = puVar4[5];
              local_a4 = local_a4 + 6;
              *local_9c = (short)local_b4;
              local_9c[1] = (short)local_b4 + 2;
              local_9c[2] = (short)local_b4 + 1;
              local_9c[3] = (short)local_b4;
              local_9c[4] = (short)local_b4 + 3;
              local_9c[5] = (short)local_b4 + 2;
              local_9c = local_9c + 6;
              FUN_006856e0();
            }
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

