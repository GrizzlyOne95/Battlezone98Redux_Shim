
void __thiscall FUN_004540d0(undefined4 *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  short *psVar5;
  char cVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float fVar15;
  int local_7c;
  int local_78;
  undefined4 *local_74;
  int local_6c;
  int local_64;
  short *local_60;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846c90;
  local_10 = ExceptionList;
  uVar7 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00448f90(param_2,param_3);
  local_8 = 0;
  *param_1 = SphereRenderClass::vftable;
  if (param_2 == 0) {
    param_1[99] = 0;
    param_1[100] = 0;
    param_1[0x65] = 0;
    param_1[0x66] = 0;
    param_1[0x67] = 0;
    param_1[0x68] = 0;
  }
  else {
    FUN_00589430(param_1 + 0x25);
    local_8._0_1_ = 1;
    uVar8 = FUN_00446460(param_1 + 0x15,0x811c9dc5,uVar7);
    cVar6 = FUN_00589800(uVar8,0x1b0f0923,param_1 + 99,*(undefined4 *)(param_2 + 0x18c));
    if (cVar6 != '\0') {
      param_1[99] = (float)param_1[99] * 0.017453292;
    }
    cVar6 = FUN_00589800(uVar8,0x96e52be4,param_1 + 100,*(undefined4 *)(param_2 + 400));
    if (cVar6 != '\0') {
      param_1[100] = (float)param_1[100] * 0.017453292;
    }
    cVar6 = FUN_00589800(uVar8,0x8997ad48,param_1 + 0x65,*(undefined4 *)(param_2 + 0x194));
    if (cVar6 != '\0') {
      param_1[0x65] = (float)param_1[0x65] * 0.017453292;
    }
    cVar6 = FUN_00589800(uVar8,0xcbe84a8f,param_1 + 0x66,*(undefined4 *)(param_2 + 0x198));
    if (cVar6 != '\0') {
      param_1[0x66] = (float)param_1[0x66] * 0.017453292;
    }
    cVar6 = FUN_00589800(uVar8,0x1698a8f6,param_1 + 0x67,*(undefined4 *)(param_2 + 0x19c));
    if (cVar6 != '\0') {
      param_1[0x67] = (float)param_1[0x67] * 0.017453292;
    }
    cVar6 = FUN_00589800(uVar8,0x9d185fa6,param_1 + 0x68,*(undefined4 *)(param_2 + 0x1a0));
    if (cVar6 != '\0') {
      param_1[0x68] = (float)param_1[0x68] * 0.017453292;
    }
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00589530();
  }
  if (DAT_0091553e == '\0') {
    DAT_0091553e = '\x01';
    local_74 = &DAT_009495c8;
    local_60 = &DAT_00915698;
    for (local_78 = 0; psVar5 = local_60, local_78 < 3; local_78 = local_78 + 1) {
      iVar1 = *(int *)(&DAT_00871a98 + local_78 * 4);
      iVar2 = *(int *)(&DAT_00871a8c + local_78 * 4);
      *(undefined4 **)(&DAT_00915688 + local_78 * 4) = local_74;
      *(short **)(&DAT_00915664 + local_78 * 4) = local_60;
      puVar9 = (undefined4 *)FUN_00446360(0,0x3f800000,0,0xffffffff,0x3f000000,0x3f000000);
      *local_74 = *puVar9;
      local_74[1] = puVar9[1];
      local_74[2] = puVar9[2];
      local_74[3] = puVar9[3];
      local_74[4] = puVar9[4];
      local_74[5] = puVar9[5];
      local_74 = local_74 + 6;
      for (local_7c = 1; local_7c < iVar1; local_7c = local_7c + 1) {
        fVar15 = ((float)local_7c * 3.1415927) / (float)iVar1;
        fVar10 = (float10)FUN_004178b0(fVar15);
        fVar11 = (float10)FUN_004178f0(fVar15);
        fVar12 = (float10)FUN_00453f80((float)local_7c / (float)iVar1 - 0.5);
        for (local_64 = 0; local_64 < iVar2; local_64 = local_64 + 1) {
          fVar15 = ((float)local_64 * 6.2831855) / (float)iVar2;
          fVar13 = (float10)FUN_004178b0(fVar15);
          fVar14 = (float10)FUN_004178f0(fVar15);
          puVar9 = (undefined4 *)
                   FUN_00446360((float)fVar11 * (float)fVar13,(float)fVar10,
                                (float)fVar11 * (float)fVar14,0xffffffff,
                                (0.5 - (float)fVar12) * (float)fVar13 + 0.5,
                                (0.5 - (float)fVar12) * (float)fVar14 + 0.5);
          *local_74 = *puVar9;
          local_74[1] = puVar9[1];
          local_74[2] = puVar9[2];
          local_74[3] = puVar9[3];
          local_74[4] = puVar9[4];
          local_74[5] = puVar9[5];
          local_74 = local_74 + 6;
        }
      }
      puVar9 = (undefined4 *)FUN_00446360(0,0xbf800000,0,0xffffffff,0x3f000000,0x3f000000);
      *local_74 = *puVar9;
      local_74[1] = puVar9[1];
      local_74[2] = puVar9[2];
      local_74[3] = puVar9[3];
      local_74[4] = puVar9[4];
      local_74[5] = puVar9[5];
      local_74 = local_74 + 6;
      local_6c = 1;
      for (local_64 = 0; sVar3 = (short)local_64, local_64 < iVar2 + -1; local_64 = local_64 + 1) {
        *local_60 = 0;
        local_60[1] = sVar3 + 1;
        local_60[2] = sVar3 + 2;
        local_60 = local_60 + 3;
      }
      *local_60 = 0;
      local_60[1] = sVar3 + 1;
      local_60[2] = 1;
      local_60 = local_60 + 3;
      for (local_7c = 1; sVar3 = (short)iVar2, local_7c < iVar1 + -1; local_7c = local_7c + 1) {
        for (local_64 = 0; sVar4 = (short)local_64, local_64 < iVar2 + -1; local_64 = local_64 + 1)
        {
          *local_60 = (short)local_6c + sVar4;
          local_60[1] = (short)local_6c + 1 + sVar4;
          local_60[2] = (short)local_6c + sVar4 + sVar3;
          local_60[3] = (short)local_6c + sVar4 + 1 + sVar3;
          local_60[4] = (short)local_6c + sVar4 + sVar3;
          local_60[5] = (short)local_6c + 1 + sVar4;
          local_60 = local_60 + 6;
        }
        *local_60 = (short)local_6c + sVar4;
        local_60[1] = (short)local_6c;
        local_60[2] = (short)local_6c + sVar4 + sVar3;
        local_60[3] = (short)local_6c + sVar3;
        local_60[4] = (short)local_6c + sVar4 + sVar3;
        local_60[5] = (short)local_6c;
        local_60 = local_60 + 6;
        local_6c = local_6c + iVar2;
      }
      for (local_64 = 0; sVar4 = (short)local_64, local_64 < iVar2 + -1; local_64 = local_64 + 1) {
        *local_60 = (short)local_6c + sVar4;
        local_60[1] = (short)local_6c + 1 + sVar4;
        local_60[2] = (short)local_6c + sVar3;
        local_60 = local_60 + 3;
      }
      *local_60 = (short)local_6c + sVar4;
      local_60[1] = (short)local_6c;
      local_60[2] = (short)local_6c + sVar3;
      local_60 = local_60 + 3;
      *(int *)(&DAT_00915670 + local_78 * 4) =
           ((int)local_74 - *(int *)(&DAT_00915688 + local_78 * 4)) / 0x18;
      *(int *)(&DAT_0091567c + local_78 * 4) = (int)local_60 - (int)psVar5 >> 1;
    }
  }
  FUN_00455440(2);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

