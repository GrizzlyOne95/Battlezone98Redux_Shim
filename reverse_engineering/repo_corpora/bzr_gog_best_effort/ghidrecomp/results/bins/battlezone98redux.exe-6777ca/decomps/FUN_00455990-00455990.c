
/* WARNING: Removing unreachable block (ram,0x00455b8b) */

void FUN_00455990(int param_1)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_c0 [16];
  undefined4 local_b0;
  float local_ac;
  int local_a8;
  float local_a4;
  undefined4 local_9c;
  int local_98;
  uint local_94;
  int local_90;
  undefined4 *local_8c;
  float local_88;
  short *local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00684ca0();
  if ((iVar1 != 0) && (iVar1 = FUN_004170c0(), iVar1 != 0)) {
    local_b0 = 2;
    local_ac = *(float *)(param_1 + 0x30) / (*(float *)(param_1 + 0x28) * 0.0025);
    FUN_00447e20();
    while( true ) {
      iVar1 = FUN_00447e70();
      FUN_00447e50();
      iVar2 = FUN_00447e70();
      if (iVar1 == iVar2) break;
      local_a8 = FUN_00447e70();
      local_90 = local_a8;
      FUN_00447e90();
      if (*(char *)(local_90 + 0x1c) != '\0') {
        pfVar3 = (float *)FUN_006897e0(local_c0,param_1,*(undefined8 *)(local_90 + 0x48),
                                       *(undefined8 *)(local_90 + 0x50),
                                       *(undefined8 *)(local_90 + 0x58));
        local_80 = *pfVar3;
        local_7c = pfVar3[1];
        local_78 = pfVar3[2];
        local_14 = local_80;
        local_10 = local_7c;
        local_c = local_78;
        iVar1 = FUN_006895d0();
        if (iVar1 < 1) {
          fVar5 = (float10)FUN_00447ed0();
          local_a4 = (float)fVar5;
          fVar5 = (float10)FUN_004497c0();
          local_88 = (float)fVar5;
          if (local_78 <= local_88 * local_ac) {
            FUN_006855e0(local_98 + 0x144,local_78 - local_88);
            local_9c = FUN_00685670(4,6);
            local_8c = (undefined4 *)FUN_006856a0();
            local_84 = (short *)FUN_006856c0();
            local_94 = FUN_00449690();
            if (*(int *)(local_90 + 0x70) != -1) {
              local_94 = ((local_94 >> 0x18) * (*(uint *)(local_90 + 0x70) >> 0x18)) / 0xff << 0x18
                         | (((local_94 >> 0x10 & 0xff) * (*(uint *)(local_90 + 0x70) >> 0x10 & 0xff)
                            ) / 0xff & 0xff) << 0x10 |
                         (((local_94 >> 8 & 0xff) * (*(uint *)(local_90 + 0x70) >> 8 & 0xff)) / 0xff
                         & 0xff) << 8 |
                         ((local_94 & 0xff) * (*(uint *)(local_90 + 0x70) & 0xff)) / 0xff & 0xff;
            }
            local_80 = *(float *)(local_98 + 0x17c) * local_88 + local_80;
            local_7c = *(float *)(local_98 + 0x180) * local_88 + local_7c;
            puVar4 = (undefined4 *)
                     FUN_00446360(local_80 - local_88,local_7c + local_88,-local_78,local_94,0,0);
            *local_8c = *puVar4;
            local_8c[1] = puVar4[1];
            local_8c[2] = puVar4[2];
            local_8c[3] = puVar4[3];
            local_8c[4] = puVar4[4];
            local_8c[5] = puVar4[5];
            local_8c = local_8c + 6;
            puVar4 = (undefined4 *)
                     FUN_00446360(local_80 + local_88,local_7c + local_88,-local_78,local_94,
                                  0x3f800000,0);
            *local_8c = *puVar4;
            local_8c[1] = puVar4[1];
            local_8c[2] = puVar4[2];
            local_8c[3] = puVar4[3];
            local_8c[4] = puVar4[4];
            local_8c[5] = puVar4[5];
            local_8c = local_8c + 6;
            puVar4 = (undefined4 *)
                     FUN_00446360(local_80 + local_88,local_7c - local_88,-local_78,local_94,
                                  0x3f800000,0x3f800000);
            *local_8c = *puVar4;
            local_8c[1] = puVar4[1];
            local_8c[2] = puVar4[2];
            local_8c[3] = puVar4[3];
            local_8c[4] = puVar4[4];
            local_8c[5] = puVar4[5];
            local_8c = local_8c + 6;
            puVar4 = (undefined4 *)
                     FUN_00446360(local_80 - local_88,local_7c - local_88,-local_78,local_94,0,
                                  0x3f800000);
            *local_8c = *puVar4;
            local_8c[1] = puVar4[1];
            local_8c[2] = puVar4[2];
            local_8c[3] = puVar4[3];
            local_8c[4] = puVar4[4];
            local_8c[5] = puVar4[5];
            local_8c = local_8c + 6;
            *local_84 = (short)local_9c;
            local_84[1] = (short)local_9c + 2;
            local_84[2] = (short)local_9c + 1;
            local_84[3] = (short)local_9c;
            local_84[4] = (short)local_9c + 3;
            local_84[5] = (short)local_9c + 2;
            local_84 = local_84 + 6;
            FUN_006856e0();
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

