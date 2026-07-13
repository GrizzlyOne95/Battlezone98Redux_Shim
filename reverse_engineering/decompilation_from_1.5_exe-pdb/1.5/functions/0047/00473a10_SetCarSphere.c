/*
 * Entry: 00473a10
 * Name: SetCarSphere
 * Namespace: Global
 * Signature: void SetCarSphere(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetCarSphere(tagENTITY *param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float *pfVar9;
  int iVar10;
  float local_7c;
  int iStack_78;
  int iStack_74;
  int local_70;
  int iStack_6c;
  int iStack_68;
  int local_64;
  int iStack_60;
  int iStack_5c;
  int local_58;
  int iStack_54;
  int iStack_50;
  int local_4c;
  int iStack_48;
  int iStack_44;
  int local_40;
  int iStack_3c;
  int iStack_38;
  int local_34;
  int iStack_30;
  int iStack_2c;
  int local_28;
  int iStack_24;
  int iStack_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  piVar4 = param_1->clsnDetails;
  if (piVar4 != (int *)0x0) {
    local_7c = (float)piVar4[3];
    iStack_78 = piVar4[8];
    iStack_74 = piVar4[0xb];
    piVar1 = piVar4 + *piVar4 + 2;
    piVar2 = piVar4 + piVar4[2] + 10;
    local_70 = *piVar1;
    iStack_6c = piVar4[8];
    iStack_68 = piVar4[0xb];
    local_64 = *piVar1;
    iStack_60 = piVar4[8];
    iStack_5c = *piVar2;
    local_58 = piVar4[3];
    iStack_54 = piVar4[8];
    iStack_50 = *piVar2;
    piVar3 = piVar4 + piVar4[1] + 6;
    local_4c = piVar4[3];
    iStack_48 = *piVar3;
    iStack_44 = piVar4[0xb];
    local_40 = *piVar1;
    iStack_3c = *piVar3;
    iStack_38 = piVar4[0xb];
    local_34 = *piVar1;
    iStack_30 = *piVar3;
    iStack_2c = *piVar2;
    local_10 = (float)piVar4[3];
    local_c = (float)*piVar3;
    local_8 = (float)*piVar2;
    fVar5 = -1e+30;
    local_28 = piVar4[3];
    iStack_24 = *piVar3;
    iStack_20 = *piVar2;
    local_1c = (param_1->bSphere).origin.x;
    local_18 = (param_1->bSphere).origin.y;
    local_14 = (param_1->bSphere).origin.z;
    pfVar9 = &local_7c;
    iVar10 = 8;
    do {
      local_10 = *pfVar9;
      local_c = pfVar9[1];
      local_8 = pfVar9[2];
      fVar6 = *pfVar9 - local_1c;
      fVar7 = pfVar9[1] - local_18;
      fVar8 = pfVar9[2] - local_14;
      fVar6 = fVar8 * fVar8 + fVar7 * fVar7 + fVar6 * fVar6;
      if (fVar5 < fVar6) {
        fVar5 = fVar6;
      }
      pfVar9 = pfVar9 + 3;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    if ((param_1->bSphere).radius < SQRT(fVar5) + 0.1) {
      (param_1->bSphere).radius = SQRT(fVar5) + 0.1;
      return;
    }
  }
  return;
}
