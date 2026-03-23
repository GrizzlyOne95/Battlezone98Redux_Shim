
void FUN_00685740(undefined4 param_1,int param_2,int param_3,uint param_4)

{
  float fVar1;
  float fVar2;
  short sVar3;
  Matrix4 *this;
  float *pfVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 *local_38;
  int local_2c;
  short *local_28;
  int local_24;
  
  iVar6 = (param_3 + -2) * 3;
  FUN_0067a110(param_3,iVar6);
  sVar3 = FUN_00684c10();
  this = (Matrix4 *)(**(code **)(*DAT_02bf0418 + 0x180))();
  pfVar4 = Ogre::Matrix4::operator[](this,2);
  fVar1 = pfVar4[2];
  pfVar4 = Ogre::Matrix4::operator[](this,2);
  fVar2 = pfVar4[3];
  local_38 = (undefined4 *)FUN_0067a150(param_3);
  for (local_24 = 0; local_24 < param_3; local_24 = local_24 + 1) {
    uVar7 = (uint)*(byte *)(param_2 + 0x14 + local_24 * 0x18);
    uVar8 = (uint)*(byte *)(param_2 + 0x15 + local_24 * 0x18);
    uVar7 = (((((param_4 >> 0x10 & 0xff) * uVar7) / 0xff - (uint)DAT_02cd9120) * uVar8) / 0xff +
             (uint)DAT_02cd9120 & 0xff) << 0x10 | 0xff000000 |
            (((((param_4 >> 8 & 0xff) * uVar7) / 0xff - (uint)DAT_02cd9121) * uVar8) / 0xff +
             (uint)DAT_02cd9121 & 0xff) << 8 |
            ((((param_4 & 0xff) * uVar7) / 0xff - (uint)DAT_02cd9122) * uVar8) / 0xff +
            (uint)DAT_02cd9122 & 0xff;
    uVar13 = *(undefined4 *)(param_2 + 0x10 + local_24 * 0x18);
    uVar12 = *(undefined4 *)(param_2 + 0xc + local_24 * 0x18);
    fVar10 = fVar2 * *(float *)(param_2 + 8 + local_24 * 0x18) + -fVar1;
    fVar9 = (float10)FUN_004f90f0(param_1,*(undefined4 *)(param_2 + 4 + local_24 * 0x18),fVar10,
                                  uVar7,uVar12,uVar13);
    fVar11 = (float)fVar9;
    fVar9 = (float10)FUN_004f90a0(param_1,*(undefined4 *)(param_2 + local_24 * 0x18),fVar11);
    puVar5 = (undefined4 *)FUN_00446360((float)fVar9,fVar11,fVar10,uVar7,uVar12,uVar13);
    *local_38 = *puVar5;
    local_38[1] = puVar5[1];
    local_38[2] = puVar5[2];
    local_38[3] = puVar5[3];
    local_38[4] = puVar5[4];
    local_38[5] = puVar5[5];
    local_38 = local_38 + 6;
  }
  local_28 = (short *)FUN_0067a1e0(iVar6);
  for (local_2c = 2; local_2c < param_3; local_2c = local_2c + 1) {
    *local_28 = sVar3;
    local_28[1] = sVar3 + (short)local_2c;
    local_28[2] = sVar3 + -1 + (short)local_2c;
    local_28 = local_28 + 3;
  }
  FUN_0083e885();
  return;
}

