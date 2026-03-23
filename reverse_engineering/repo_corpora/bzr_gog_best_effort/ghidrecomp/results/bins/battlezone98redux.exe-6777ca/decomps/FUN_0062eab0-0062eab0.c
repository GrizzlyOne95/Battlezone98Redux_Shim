
void FUN_0062eab0(int param_1)

{
  char cVar1;
  float *pfVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar9;
  float10 fVar10;
  undefined1 local_f8 [12];
  undefined1 local_ec [12];
  double local_e0;
  double local_d8;
  int local_d0;
  int local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  int local_c0;
  uint local_bc;
  undefined4 *local_b8;
  int local_b4;
  short *local_b0;
  int local_ac;
  int local_a8;
  uint local_a4;
  undefined4 local_a0 [16];
  undefined4 local_60 [16];
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar1 = FUN_0062e850();
  if (cVar1 != '\0') {
    pfVar2 = (float *)FUN_0062e8d0(local_f8,param_1);
    local_20 = *pfVar2;
    local_1c = pfVar2[1];
    local_18 = pfVar2[2];
    fVar10 = (float10)FUN_007855e0(*(undefined8 *)(param_1 + 0x160),*(undefined8 *)(param_1 + 0x170)
                                  );
    local_d8 = (double)fVar10;
    for (local_ac = DAT_02b3c72c; local_ac != 0; local_ac = *(int *)(local_ac + 0x7c)) {
      for (local_bc = 0; local_bc < 9; local_bc = local_bc + 1) {
        DAT_02ceefc8 = (double)(local_20 + *(float *)(&DAT_008eca78 + local_bc * 8) +
                               (float)*(double *)(local_ac + 0x48));
        DAT_02ceefd8 = (double)(local_18 + *(float *)(&DAT_008eca7c + local_bc * 8) +
                               (float)*(double *)(local_ac + 0x58));
        local_c8 = FUN_0077d5f0(DAT_02ceefc8,DAT_02ceefd8);
        uVar3 = FUN_0062eaa0();
        iVar4 = FUN_004e3620(local_ac,uVar3);
        if (iVar4 != 1) goto LAB_0062f11f;
        if (((*(int *)(local_ac + 100) != 0) && (2 < *(uint *)(*(int *)(local_ac + 100) + 4))) &&
           (iVar4 = FUN_0062ea90(), iVar4 != 0)) {
          fVar10 = (float10)FUN_007855e0(DAT_02ceefc8,DAT_02ceefd8);
          DAT_02ceefd0 = (double)fVar10;
          local_e0 = DAT_02ceefd0 - local_d8;
          if (local_e0 <= 5.0) {
            puVar5 = (undefined4 *)
                     FUN_006897e0(local_ec,param_1,DAT_02ceefc8,DAT_02ceefd0,DAT_02ceefd8);
            local_14 = *puVar5;
            local_10 = puVar5[1];
            local_c = (float)puVar5[2];
            if ((local_c <= 120.00001) && (local_cc = FUN_006895d0(), local_cc < 1)) {
              local_b4 = *(int *)(local_ac + 100);
              local_a8 = *(undefined4 *)(local_b4 + 0x14);
              puVar5 = (undefined4 *)FUN_0081fe60();
              puVar9 = local_60;
              for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
                *puVar9 = *puVar5;
                puVar5 = puVar5 + 1;
                puVar9 = puVar9 + 1;
              }
              FUN_00820180(DAT_02cecf70,*(undefined4 *)(local_b4 + 0xc),
                           *(undefined4 *)(local_b4 + 4),local_60);
              puVar5 = (undefined4 *)(local_ac + 0x20);
              puVar9 = local_a0;
              for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
                *puVar9 = *puVar5;
                puVar5 = puVar5 + 1;
                puVar9 = puVar9 + 1;
              }
              puVar5 = &DAT_02ceefa0;
              puVar9 = (undefined4 *)(local_ac + 0x20);
              for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
                *puVar9 = *puVar5;
                puVar5 = puVar5 + 1;
                puVar9 = puVar9 + 1;
              }
              FUN_0068a340();
              puVar5 = local_a0;
              puVar9 = (undefined4 *)(local_ac + 0x20);
              for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
                *puVar9 = *puVar5;
                puVar5 = puVar5 + 1;
                puVar9 = puVar9 + 1;
              }
              local_c0 = *(int *)(local_b4 + 4) * 0xc + DAT_02cecf70;
              FUN_0068a6f0(local_c0,DAT_02cecf70,*(undefined4 *)(local_b4 + 0x10),&DAT_02ceefa0,
                           local_60,*(undefined4 *)(local_b4 + 8));
              for (local_a8 = *(int *)(local_b4 + 0x14); local_a8 != 0;
                  local_a8 = *(int *)(local_a8 + 0x30)) {
                FUN_006855a0(local_a8 + 0x20,local_c);
                local_c4 = FUN_00685670(*(undefined4 *)(local_a8 + 4));
                local_b8 = (undefined4 *)FUN_006856a0();
                local_b0 = (short *)FUN_006856c0();
                for (local_a4 = 0; local_a4 < *(uint *)(local_a8 + 4); local_a4 = local_a4 + 1) {
                  local_d0 = *(int *)(local_a8 + 0x40 + local_a4 * 0x10);
                  puVar5 = (undefined4 *)(local_d0 * 0xc + DAT_02cecf70);
                  *local_b8 = *puVar5;
                  local_b8[1] = puVar5[1];
                  local_b8[2] = puVar5[2];
                  uVar6 = FUN_008445c0();
                  uVar7 = FUN_008445c0();
                  uVar8 = FUN_008445c0();
                  local_b8[3] = (uVar6 & 0xff) << 0x10 | 0xff000000 | (uVar7 & 0xff) << 8 |
                                uVar8 & 0xff;
                  local_b8[4] = *(undefined4 *)(local_a8 + 0x48 + local_a4 * 0x10);
                  local_b8[5] = *(undefined4 *)(local_a8 + 0x4c + local_a4 * 0x10);
                  local_b8 = local_b8 + 6;
                }
                for (local_a4 = 2; local_a4 < *(uint *)(local_a8 + 4); local_a4 = local_a4 + 1) {
                  *local_b0 = (short)local_c4;
                  local_b0[1] = (short)local_c4 + (short)local_a4;
                  local_b0[2] = (short)local_c4 + -1 + (short)local_a4;
                  local_b0 = local_b0 + 3;
                }
              }
            }
          }
        }
      }
    }
  }
LAB_0062f11f:
  FUN_0083e885();
  return;
}

