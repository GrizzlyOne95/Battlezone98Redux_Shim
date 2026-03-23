
void __thiscall FUN_004c5430(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_f4 [8];
  undefined1 local_ec [8];
  int local_e4;
  int local_e0;
  undefined4 local_dc;
  int local_d8;
  int local_d4;
  float local_d0;
  int local_cc;
  int local_c8;
  int local_c4;
  int local_c0;
  undefined1 local_bc [52];
  undefined4 uStack_88;
  undefined4 auStack_50 [6];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_d0 = DAT_00920ef4;
  DAT_00920ef4 = DAT_00920ef4 + 0.05;
  local_c4 = param_1;
  if ((*(int *)(**(int **)(param_1 + 0xc) + 0xc + *(int *)(param_1 + 0x10) * 0x24) != 0xc) &&
     ((*(int *)(param_1 + 0xec) != 0 || (*(int *)(param_1 + 0xf0) != 0)))) {
    FUN_004c6ee0(&local_c8,&local_cc,param_2);
    local_d8 = local_c8 - *(int *)(local_c4 + 0xec) / 2;
    local_e4 = local_d8 + *(int *)(local_c4 + 0xec);
    local_d4 = local_cc - *(int *)(local_c4 + 0xf0) / 2;
    local_e0 = local_d4 + *(int *)(local_c4 + 0xf0);
    for (local_cc = local_d4; local_cc <= local_e0; local_cc = local_cc + 1) {
      for (local_c8 = local_d8; local_c8 <= local_e4; local_c8 = local_c8 + 1) {
        FUN_00783430(local_bc,(float)local_c8 * 5.0,(float)local_cc * 5.0);
        for (local_c0 = 0; local_c0 < 9; local_c0 = local_c0 + 1) {
          puVar2 = (undefined4 *)FUN_004c6f30(local_ec,local_bc + local_c0 * 0xc,DAT_00917594);
          uVar1 = puVar2[1];
          auStack_50[local_c0 * 2] = *puVar2;
          auStack_50[local_c0 * 2 + 1] = uVar1;
        }
        FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,uStack_28,uStack_24,DAT_0091757c,0);
        FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,uStack_10,uStack_c,DAT_0091757c,0);
        FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,uStack_18,uStack_14,DAT_0091757c,0);
        if (local_c8 == local_d8) {
          FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,uStack_38,uStack_34,DAT_0091757c,0);
          FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,auStack_50[0],auStack_50[1],DAT_0091757c,0);
        }
        if (local_cc == local_d4) {
          FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,auStack_50[2],auStack_50[3],DAT_0091757c,0);
          FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,auStack_50[0],auStack_50[1],DAT_0091757c,0);
        }
      }
    }
  }
  FUN_00783430(local_bc,*param_2,param_2[2]);
  for (local_c0 = 0; local_c0 < 9; local_c0 = local_c0 + 1) {
    puVar2 = (undefined4 *)FUN_004c6f30(local_f4,local_bc + local_c0 * 0xc,DAT_00917594);
    uVar1 = puVar2[1];
    auStack_50[local_c0 * 2] = *puVar2;
    auStack_50[local_c0 * 2 + 1] = uVar1;
  }
  DAT_00920ef4 = local_d0 + 0.04;
  FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,uStack_38,uStack_34,DAT_0091755c,0);
  FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,auStack_50[0],auStack_50[1],DAT_0091755c,0);
  FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,auStack_50[2],auStack_50[3],DAT_0091755c,0);
  FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,uStack_28,uStack_24,DAT_0091755c,0);
  FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,uStack_10,uStack_c,DAT_0091755c,0);
  FUN_0068af40(DAT_00917580,uStack_30,uStack_2c,uStack_18,uStack_14,DAT_0091755c,0);
  DAT_00920ef4 = local_d0;
  local_dc = uStack_88;
  FUN_0083e885();
  return;
}

