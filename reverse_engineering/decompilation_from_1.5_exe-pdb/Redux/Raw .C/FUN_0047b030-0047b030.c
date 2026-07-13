
void __thiscall FUN_0047b030(int *param_1,float param_2)

{
  double dVar1;
  double dVar2;
  double dVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  short sVar9;
  undefined4 *puVar10;
  int *piVar11;
  undefined4 uVar12;
  int iVar13;
  undefined4 *puVar14;
  undefined1 local_168 [64];
  undefined1 local_128 [12];
  undefined1 local_11c [12];
  int local_110;
  undefined2 *local_10c;
  int local_108;
  int local_104;
  float local_100;
  int local_fc;
  int local_f8;
  float local_f4;
  undefined1 *local_f0;
  char local_e9;
  int *local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8 [16];
  undefined4 local_98 [16];
  double local_58;
  double local_50;
  double local_48;
  undefined1 local_40 [12];
  undefined8 local_34;
  undefined8 local_2c;
  undefined8 local_24;
  int local_1c;
  int local_18;
  int local_14;
  undefined2 local_10;
  undefined2 local_e;
  undefined2 local_c;
  undefined1 auStack_a [2];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_e8 = param_1;
  if ((*(uint *)(param_1[5] + 0x14) & 0x200) == 0) {
    param_1[0x1b] = (int)(*(float *)(param_1[3] + 0x58) * param_2);
    local_e9 = '\0';
    if ((((-1 < param_1[0x41]) && (local_104 = FUN_00479f30(param_1[0x36]), local_104 != 0)) &&
        (local_108 = FUN_00417ca0(), local_108 != 0)) &&
       (local_f8 = FUN_00417f60(local_e8[0x41]), local_f8 != 0)) {
      puVar10 = (undefined4 *)
                FUN_0081fe60(local_168,*(int *)(local_f8 + 0x10) + 0x20,local_f8 + 0x28);
      puVar14 = local_d8;
      for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
        *puVar14 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar14 = puVar14 + 1;
      }
      puVar10 = local_d8;
      puVar14 = local_98;
      for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
        *puVar14 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar14 = puVar14 + 1;
      }
      puVar10 = local_98;
      puVar14 = (undefined4 *)(local_e8[5] + 0x20);
      for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
        *puVar14 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar14 = puVar14 + 1;
      }
      local_e9 = '\x01';
    }
    if (local_e9 == '\0') {
      *(uint *)(local_e8[5] + 0x14) = *(uint *)(local_e8[5] + 0x14) | 0x200;
      iVar13 = FUN_00572a70();
      if ((iVar13 != 0) && (iVar13 = local_e8[0x1f], sVar9 = FUN_00572d90(), (short)iVar13 == sVar9)
         ) {
        local_10c = &local_10;
        local_10 = 0x6f69;
        local_e = (undefined2)local_e8[0x1f];
        local_c = *(undefined2 *)((int)local_e8 + 0x7e);
        local_f0 = auStack_a;
        FUN_00575890(&local_10,(int)local_f0 - (int)&local_10,1,1);
      }
    }
    else {
      if (*(int *)(local_e8[3] + 0x70) != 0) {
        (**(code **)(**(int **)(local_e8[3] + 0x70) + 8))(local_e8 + 0x1d,local_e8[5] + 0x20);
      }
      puVar10 = (undefined4 *)FUN_004560b0(local_128,local_e8[5] + 0x20);
      local_e4 = *puVar10;
      local_e0 = puVar10[1];
      local_dc = puVar10[2];
      piVar11 = (int *)FUN_004462d0(local_11c,*(undefined4 *)(local_e8[3] + 0x54),local_e4,local_e0,
                                    local_dc);
      local_1c = *piVar11;
      local_18 = piVar11[1];
      local_14 = piVar11[2];
      local_e8[0xc] = local_1c;
      local_e8[0xd] = local_18;
      local_e8[0xe] = local_14;
      local_e8[8] = *(int *)(local_e8[3] + 0x54);
      if ((float)local_e8[8] <= 0.0) {
        local_100 = 1e+30;
      }
      else {
        local_100 = 1.0 / (float)local_e8[8];
      }
      local_e8[9] = (int)local_100;
      *(undefined8 *)(local_e8 + 0x3a) = *(undefined8 *)(local_e8[5] + 0x48);
      *(undefined8 *)(local_e8 + 0x3c) = *(undefined8 *)(local_e8[5] + 0x50);
      *(undefined8 *)(local_e8 + 0x3e) = *(undefined8 *)(local_e8[5] + 0x58);
      dVar1 = *(double *)(local_e8[5] + 0x48);
      dVar2 = *(double *)(local_e8[5] + 0x50);
      dVar3 = *(double *)(local_e8[5] + 0x58);
      local_f4 = *(float *)(local_e8[3] + 0x50);
      local_34._0_4_ = SUB84(dVar1,0);
      local_34._4_4_ = (undefined4)((ulonglong)dVar1 >> 0x20);
      uVar12 = local_34._4_4_;
      local_2c._0_4_ = SUB84(dVar2,0);
      local_2c._4_4_ = (undefined4)((ulonglong)dVar2 >> 0x20);
      uVar4 = local_2c._4_4_;
      local_24._0_4_ = SUB84(dVar3,0);
      local_24._4_4_ = (undefined4)((ulonglong)dVar3 >> 0x20);
      uVar5 = local_24._4_4_;
      uVar6 = (undefined4)local_34;
      local_34 = dVar1;
      uVar7 = (undefined4)local_2c;
      local_2c = dVar2;
      uVar8 = (undefined4)local_24;
      local_24 = dVar3;
      local_110 = FUN_00784620(uVar6,uVar12,uVar7,uVar4,uVar8,uVar5,local_e8[0xc],local_e8[0xd],
                               local_e8[0xe],&local_f4,local_40);
      local_58 = (double)(local_f4 * (float)local_e8[0xc]) + local_34;
      local_50 = (double)(local_f4 * (float)local_e8[0xd]) + local_2c;
      local_48 = (double)(local_f4 * (float)local_e8[0xe]) + local_24;
      local_fc = FUN_00480f40(&local_f4,&local_58,local_40);
      *(double *)(local_e8[5] + 0x48) = local_58;
      *(double *)(local_e8[5] + 0x50) = local_50;
      *(double *)(local_e8[5] + 0x58) = local_48;
      if (local_fc == 0) {
        if (local_110 != 0) {
          (**(code **)(*local_e8 + 0x14))(0,local_40);
        }
      }
      else {
        uVar12 = FUN_00479f30(local_fc,local_40);
        (**(code **)(*local_e8 + 0x14))(uVar12);
      }
      *(uint *)(local_e8[5] + 0x14) = *(uint *)(local_e8[5] + 0x14) & 0xfffffdff;
    }
    FUN_0044dc60(local_e8[5] + 0x20,param_2);
  }
  FUN_0083e885();
  return;
}

