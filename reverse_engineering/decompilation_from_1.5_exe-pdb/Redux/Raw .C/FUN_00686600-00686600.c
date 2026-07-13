
void FUN_00686600(int param_1,int param_2,int param_3,undefined4 param_4)

{
  float fVar1;
  float fVar2;
  short sVar3;
  Matrix4 *this;
  float *pfVar4;
  undefined4 *puVar5;
  int iVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 *local_34;
  int local_2c;
  int local_28;
  short *local_24;
  
  if (param_1 == 0) {
    param_1 = DAT_02b79b2c;
  }
  iVar6 = (param_3 + -2) * 3;
  FUN_0067a110(param_3,iVar6);
  sVar3 = FUN_00684c10();
  this = (Matrix4 *)(**(code **)(*DAT_02bf0418 + 0x180))();
  pfVar4 = Ogre::Matrix4::operator[](this,2);
  fVar1 = pfVar4[2];
  pfVar4 = Ogre::Matrix4::operator[](this,2);
  fVar2 = pfVar4[3];
  local_34 = (undefined4 *)FUN_0067a150(param_3);
  for (local_28 = 0; local_28 < param_3; local_28 = local_28 + 1) {
    uVar12 = *(undefined4 *)(param_2 + 0x10 + local_28 * 0x18);
    uVar11 = *(undefined4 *)(param_2 + 0xc + local_28 * 0x18);
    fVar8 = fVar2 * *(float *)(param_2 + 8 + local_28 * 0x18) + -fVar1;
    uVar10 = param_4;
    fVar7 = (float10)FUN_004f90f0(param_1,*(float *)(param_2 + 4 + local_28 * 0x18) - DAT_00920e9c,
                                  fVar8,param_4,uVar11,uVar12);
    fVar9 = (float)fVar7;
    fVar7 = (float10)FUN_004f90a0(param_1,*(float *)(param_2 + local_28 * 0x18) - DAT_00920e9c,fVar9
                                 );
    puVar5 = (undefined4 *)FUN_00446360((float)fVar7,fVar9,fVar8,uVar10,uVar11,uVar12);
    *local_34 = *puVar5;
    local_34[1] = puVar5[1];
    local_34[2] = puVar5[2];
    local_34[3] = puVar5[3];
    local_34[4] = puVar5[4];
    local_34[5] = puVar5[5];
    local_34 = local_34 + 6;
  }
  local_24 = (short *)FUN_0067a1e0(iVar6);
  for (local_2c = 2; local_2c < param_3; local_2c = local_2c + 1) {
    *local_24 = sVar3;
    local_24[1] = sVar3 + (short)local_2c;
    local_24[2] = sVar3 + -1 + (short)local_2c;
    local_24 = local_24 + 3;
  }
  FUN_0083e885();
  return;
}

