
void __fastcall FUN_005ab6b0(int param_1)

{
  double dVar1;
  undefined8 uVar2;
  double dVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  float *pfVar10;
  int iVar11;
  float10 fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float local_3c;
  float *local_38;
  undefined4 *local_34;
  float *local_30;
  float local_2c;
  float local_28;
  int local_24;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = param_1;
  if (*(int *)(*(int *)(param_1 + 0xc) + 0xac) == 0) {
    *(undefined4 *)(param_1 + 0x14) = 1;
  }
  else if ((*(uint *)(*(int *)(*(int *)(param_1 + 0xc) + 0x228) + 0x114) & 1) == 0) {
    if ((*(uint *)(*(int *)(*(int *)(param_1 + 0xc) + 0x228) + 0x114) & 4) == 0) {
      *(undefined4 *)(param_1 + 0x14) = 1;
      iVar11 = *(int *)(*(int *)(param_1 + 0xc) + 0x228);
      local_34 = (undefined4 *)(iVar11 + 0xc4);
      *(undefined4 *)(iVar11 + 0xd0) = 0;
      *(undefined4 *)(iVar11 + 0xcc) = 0;
      *local_34 = 0;
      *(undefined4 *)(iVar11 + 200) = 0;
    }
  }
  else {
    local_38 = (float *)(*(int *)(*(int *)(param_1 + 0xc) + 0x228) + 0xc4);
    local_30 = (float *)FUN_0045c4d0();
    pfVar10 = (float *)FUN_004624b0();
    iVar11 = *(int *)(*(int *)(*(int *)(local_24 + 0xc) + 0xb4) + 8);
    local_2c = *(float *)(iVar11 + 8);
    local_28 = *(float *)(iVar11 + 0xc);
    dVar1 = *(double *)(local_30 + 10);
    uVar2 = *(undefined8 *)(local_30 + 0xc);
    dVar3 = *(double *)(local_30 + 0xe);
    local_3c = 10.0;
    local_20._0_4_ = SUB84(dVar1,0);
    local_20._4_4_ = (undefined4)((ulonglong)dVar1 >> 0x20);
    uVar4 = local_20._4_4_;
    local_18._0_4_ = (undefined4)uVar2;
    local_18._4_4_ = (undefined4)((ulonglong)uVar2 >> 0x20);
    uVar5 = local_18._4_4_;
    local_10._0_4_ = SUB84(dVar3,0);
    local_10._4_4_ = (undefined4)((ulonglong)dVar3 >> 0x20);
    uVar6 = local_10._4_4_;
    uVar7 = (undefined4)local_20;
    local_20 = dVar1;
    uVar8 = (undefined4)local_18;
    local_18 = uVar2;
    uVar9 = (undefined4)local_10;
    local_10 = dVar3;
    iVar11 = FUN_00784620(uVar7,uVar4,uVar8,uVar5,uVar9,uVar6,*pfVar10,pfVar10[1],pfVar10[2],
                          &local_3c,0);
    dVar1 = local_20;
    dVar3 = local_10;
    if (iVar11 != 0) {
      dVar1 = (double)(local_3c * *pfVar10) + local_20;
      dVar3 = (double)(local_3c * pfVar10[2]) + local_10;
    }
    local_28 = local_28 - (float)dVar3;
    local_2c = local_2c - (float)dVar1;
    fVar13 = local_2c * *local_30 + local_28 * local_30[2];
    fVar14 = local_2c * local_30[6];
    fVar15 = local_28 * local_30[8];
    fVar12 = (float10)FUN_00447ed0(fVar13 * 0.2,0xbf800000,0x3f800000);
    local_38[2] = (float)fVar12;
    fVar12 = (float10)FUN_00447ed0((fVar14 + fVar15) * 0.2,0xbf800000,0x3f800000);
    local_38[3] = (float)fVar12;
    fVar12 = (float10)FUN_00820570((double)(local_2c * local_2c + local_28 * local_28 + 0.0001));
    fVar13 = fVar13 * (float)fVar12 * 5.0;
    iVar11 = FUN_0045c490(0xbf800000,0x3f800000,fVar13);
    fVar12 = (float10)FUN_00447ed0(fVar13 - *(float *)(iVar11 + 0x28));
    *local_38 = (float)fVar12;
  }
  FUN_0083e885();
  return;
}

