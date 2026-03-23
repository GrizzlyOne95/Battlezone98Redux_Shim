
void FUN_004b8590(undefined2 param_1,byte *param_2,uint param_3,float param_4)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int *piVar7;
  int *piVar8;
  float10 fVar9;
  undefined1 local_164 [64];
  undefined4 local_124;
  undefined1 local_120 [4];
  undefined1 local_11c [4];
  undefined1 local_118 [4];
  undefined1 local_114 [4];
  undefined1 local_110 [4];
  float local_10c;
  float local_108;
  float local_104;
  int local_100;
  int *local_fc;
  int *local_f8;
  int *local_f4;
  int *local_f0;
  byte *local_ec;
  byte *local_e8;
  int local_e4;
  uint local_e0;
  int *local_dc;
  uint local_d8;
  int local_d4;
  byte *local_d0;
  int *local_cc;
  int local_c8;
  int local_c4;
  undefined1 local_c0 [4];
  byte *local_bc;
  uint local_b8;
  byte *local_b4;
  byte *local_b0;
  int local_ac;
  int *local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined1 local_9b;
  char local_9a;
  byte local_99;
  int *local_98;
  int local_94 [16];
  int local_54 [10];
  double local_2c;
  double local_24;
  double local_1c;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  while( true ) {
    if ((param_3 < 6) || (param_3 < *param_2)) goto LAB_004b8f31;
    if (*param_2 == 0) break;
    local_ec = param_2;
    local_99 = param_2[1];
    local_a4 = *(undefined4 *)(param_2 + 2);
    FUN_00430590();
    puVar3 = (undefined4 *)FUN_0046b370(local_120,(short)&local_a4);
    local_a0 = *puVar3;
    uVar2 = FID_conflict_begin((short)local_11c);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') {
      local_f8 = (int *)0x0;
    }
    else {
      iVar4 = FUN_00422150();
      local_f8 = *(int **)(iVar4 + 4);
    }
    local_98 = local_f8;
    if ((local_f8 == (int *)0x0) || ((local_99 & 3) != 2)) {
      if ((local_f8 == (int *)0x0) || ((local_99 & 3) != 3)) {
        if (local_f8 == (int *)0x0) {
          puVar3 = (undefined4 *)FUN_0046b370(local_114,(short)&local_a4);
          local_a0 = *puVar3;
          uVar2 = FID_conflict_begin((short)local_118);
          cVar1 = FUN_00420f10(uVar2);
          if (cVar1 == '\0') {
            local_dc = (int *)0x0;
          }
          else {
            iVar4 = FUN_00422150();
            local_dc = *(int **)(iVar4 + 4);
          }
          local_98 = local_dc;
          if ((local_dc == (int *)0x0) || ((local_99 & 3) != 2)) {
            if ((local_99 & 3) == 0) {
              if (local_dc == (int *)0x0) {
                FUN_0044eb20(local_c0,(short)&local_a4);
                uVar2 = FUN_0044eaa0((short)local_110);
                cVar1 = FUN_00420f10(uVar2);
                if ((cVar1 != '\0') &&
                   (iVar4 = FUN_0042da60(), param_4 < *(float *)(iVar4 + 4) + 1.0)) {
                  iVar4 = FUN_0042da60((double)param_4,(short)local_a4);
                  uVar5 = FUN_0081e820("OOP D=%.2f P=%.2f DELETED ID %08x\n",
                                       (double)*(float *)(iVar4 + 4));
                  FUN_0081e710(uVar5);
                  goto LAB_004b85a7;
                }
                FUN_004b9350(param_1,param_2,(short)param_3);
                puVar3 = (undefined4 *)FUN_004bad10((short)&local_a4);
                local_98 = (int *)*puVar3;
              }
              if (local_98 != (int *)0x0) {
                local_b4 = (byte *)0x0;
                local_d0 = param_2;
                local_bc = param_2;
                FUN_004b7f00(param_1);
                local_c8 = (**(code **)(*local_98 + 0x30))();
                if (local_c8 != 0) {
                  FUN_0062de80(local_c8,0x200);
                }
                if ((local_bc[0x14] & 0x80) == 0) {
                  local_b0 = local_d0 + 0x1c;
                  local_b4 = local_d0;
                }
                else {
                  local_b0 = local_bc + 0x15;
                  local_b4 = local_bc;
                }
                local_b4 = local_b4 + 6;
                if (param_4 < (float)local_98[0x1e]) {
                  uVar5 = FUN_0081e820("OOP D=%.2f P=%.2f Last Received %.2f ID %08x\n",
                                       (double)(float)local_98[0x1e],(double)param_4,
                                       (double)(float)local_98[0x1e],(short)local_a4);
                  FUN_0081e710(uVar5);
                }
                else {
                  local_98[0x1e] = (int)param_4;
                  local_9a = (char)((int)(uint)local_99 >> 7);
                  local_9b = (char)local_98[0x18] != local_9a;
                  local_d8 = (uint)(byte)local_9b;
                  *(char *)(local_98 + 0x18) = local_9a;
                  local_e0 = (int)(uint)local_99 >> 2 & 0xf;
                  if (((bool)local_9b) ||
                     (uVar6 = (**(code **)(*local_98 + 4))(), local_e0 != uVar6)) {
                    (**(code **)(*local_98 + 8))((short)local_e0);
                  }
                  local_a8 = local_98 + 4;
                  local_98[0x14] = 0;
                  local_98[0x16] = local_98[0x15];
                  local_98[0x15] = 0;
                  piVar7 = local_a8;
                  piVar8 = local_54;
                  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
                    *piVar8 = *piVar7;
                    piVar7 = piVar7 + 1;
                    piVar8 = piVar8 + 1;
                  }
                  piVar7 = (int *)FUN_006253c0(local_164,*(undefined4 *)local_b4,
                                               *(undefined4 *)(local_b4 + 4),
                                               *(undefined4 *)(local_b4 + 8),
                                               *(undefined2 *)(local_b4 + 0xc));
                  piVar8 = local_94;
                  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
                    *piVar8 = *piVar7;
                    piVar7 = piVar7 + 1;
                    piVar8 = piVar8 + 1;
                  }
                  piVar7 = local_94;
                  piVar8 = local_a8;
                  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
                    *piVar8 = *piVar7;
                    piVar7 = piVar7 + 1;
                    piVar8 = piVar8 + 1;
                  }
                  local_e8 = param_2 + ((uint)*param_2 - (int)local_b0);
                  if (local_e8 != (byte *)0x0) {
                    FUN_004b7e30(local_b0,(short)&local_e8);
                  }
                  fVar9 = (float10)FUN_00822d80();
                  local_104 = (float)fVar9;
                  local_10c = local_104 - param_4;
                  fVar9 = (float10)FUN_00822d60();
                  local_108 = (float)fVar9;
                  local_98[0x17] = (int)(local_10c - local_108);
                  local_14 = (float)(*(double *)(local_a8 + 10) - local_2c);
                  local_10 = (float)(*(double *)(local_a8 + 0xc) - local_24);
                  local_c = (float)(*(double *)(local_a8 + 0xe) - local_1c);
                  if (((((2.5 < local_14) || (local_14 < -2.5)) || (2.5 < local_10)) ||
                      ((local_10 < -2.5 || (2.5 < local_c)))) ||
                     ((local_c < -2.5 ||
                      ((0.32 < (float)local_98[0x17] ||
                       ((float)local_98[0x17] <= -0.32 && (float)local_98[0x17] != -0.32)))))) {
                    FUN_007d6a70("Possible Large Warp: Distributed Object Updated Position By (%f,%f,%f) with TS %f\n"
                                 ,(double)local_14,(double)local_10,(double)local_c,
                                 SUB84((double)(float)local_98[0x17],0),
                                 (short)((ulonglong)(double)(float)local_98[0x17] >> 0x20));
                  }
                }
              }
            }
            else {
              local_124 = FUN_0045ca50();
              if (local_98 != (int *)0x0) {
                if (local_98 == (int *)0x0) {
                  local_fc = (int *)0x0;
                }
                else {
                  local_fc = local_98 + -6;
                }
                local_fc[0x3b] = 0;
                local_ac = (**(code **)(*local_98 + 0x30))();
                if (((int)(uint)local_99 >> 6 & 1U) == 0) {
                  if (local_ac != 0) {
                    local_b8 = (int)(uint)local_99 >> 2 & 0xf;
                    if (local_b8 == 3) {
                      FUN_0062de40(local_ac,0x280);
                    }
                    else if (local_b8 == 2) {
                      FUN_0062de40(local_ac,0x280);
                    }
                    else if (local_b8 == 0) {
                      FUN_0062de40(local_ac,0x280);
                    }
                    else {
                      FUN_0062de40(local_ac,0x280);
                    }
                  }
                }
                else {
                  (**(code **)(*local_98 + 0x24))();
                }
                *(undefined1 *)(local_98 + 0x1a) = 0;
                *(undefined2 *)((int)local_98 + 0x62) = 0;
                FUN_004badc0((short)(local_98 + 0x19));
                FUN_004b7bd0();
                local_e4 = (**(code **)*local_98)();
                if ((local_e4 != 0) && (*(int *)(local_e4 + 0x14) == 0x53435250)) {
                  (**(code **)(*local_98 + 0x10))();
                }
              }
            }
          }
        }
      }
      else {
        local_d4 = (**(code **)(*local_f8 + 0x30))();
        if (local_d4 != 0) {
          FUN_0062de40(local_d4,0x200);
        }
        FUN_004b7bd0();
        local_c4 = (**(code **)*local_98)();
        if ((local_c4 != 0) && (*(int *)(local_c4 + 0x14) == 0x53435250)) {
          (**(code **)(*local_98 + 0x10))();
        }
      }
    }
    else {
      local_100 = FUN_00417c70();
      if (local_100 == 0) {
        local_cc = (int *)0x0;
      }
      else {
        local_cc = (int *)(local_100 + 0x18);
      }
      if (local_cc == local_98) {
        if (local_98 == (int *)0x0) {
          local_f0 = (int *)0x0;
        }
        else {
          local_f0 = local_98 + -6;
        }
        local_f4 = local_f0;
        (**(code **)(*local_f0 + 0x80))();
      }
      FUN_004b7f20();
      *(undefined2 *)((int)local_98 + 0x62) = param_1;
    }
LAB_004b85a7:
    param_3 = param_3 - *param_2;
    param_2 = param_2 + *param_2;
  }
  FUN_007d6a70(0x8db4);
LAB_004b8f31:
  FUN_0083e885();
  return;
}

