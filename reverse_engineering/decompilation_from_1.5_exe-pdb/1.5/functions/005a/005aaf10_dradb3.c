/*
 * Entry: 005aaf10
 * Name: dradb3
 * Namespace: Global
 * Signature: void dradb3(int param_1, int param_2, float * param_3, float * param_4, float * param_5, float * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
dradb3(int param_1,int param_2,float *param_3,float *param_4,float *param_5,float *param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *in_EAX;
  float *pfVar8;
  float *pfVar9;
  int iVar10;
  int iVar11;
  float *pfVar12;
  float *pfVar13;
  int iVar14;
  float *pfVar15;
  float *pfVar16;
  int iVar17;
  float *pfVar18;
  float *pfVar19;
  int unaff_EDI;
  float *local_40;
  float *local_34;
  float *local_2c;
  int local_28;
  int local_24;
  float *local_20;
  int local_10;
  
  fVar7 = taui;
  fVar6 = taur;
  iVar10 = unaff_EDI * param_1;
  iVar14 = 0;
  iVar17 = 0;
  iVar11 = unaff_EDI * 2;
  local_2c = (float *)0x0;
  if (3 < param_1) {
    local_40 = (float *)(param_2 + iVar10 * 8);
    pfVar8 = (float *)(param_2 + iVar10 * 4);
    local_20 = (float *)((param_1 - 4U >> 2) + 1);
    local_2c = (float *)((int)local_20 * 4);
    do {
      fVar1 = in_EAX[iVar11 + -1] + in_EAX[iVar11 + -1];
      fVar2 = in_EAX[iVar14] + fVar1 * fVar6;
      *(float *)(param_2 + iVar17 * 4) = fVar1 + in_EAX[iVar14];
      fVar1 = (in_EAX[iVar11] + in_EAX[iVar11]) * fVar7;
      *pfVar8 = fVar2 - fVar1;
      *local_40 = fVar1 + fVar2;
      pfVar8 = pfVar8 + unaff_EDI;
      iVar11 = iVar11 + unaff_EDI * 3;
      iVar14 = iVar14 + unaff_EDI * 3;
      fVar1 = in_EAX[iVar11 + -1] + in_EAX[iVar11 + -1];
      local_40 = local_40 + unaff_EDI;
      fVar2 = in_EAX[iVar14] + fVar1 * fVar6;
      *(float *)(param_2 + (iVar17 + unaff_EDI) * 4) = fVar1 + in_EAX[iVar14];
      pfVar9 = pfVar8 + unaff_EDI;
      iVar17 = iVar17 + unaff_EDI + unaff_EDI;
      fVar1 = (in_EAX[iVar11] + in_EAX[iVar11]) * fVar7;
      *pfVar8 = fVar2 - fVar1;
      pfVar12 = local_40 + unaff_EDI;
      *local_40 = fVar1 + fVar2;
      iVar11 = iVar11 + unaff_EDI * 3;
      iVar14 = iVar14 + unaff_EDI * 3;
      fVar1 = in_EAX[iVar11 + -1] + in_EAX[iVar11 + -1];
      fVar2 = in_EAX[iVar14] + fVar1 * fVar6;
      *(float *)(param_2 + iVar17 * 4) = fVar1 + in_EAX[iVar14];
      iVar17 = iVar17 + unaff_EDI;
      fVar1 = (in_EAX[iVar11] + in_EAX[iVar11]) * fVar7;
      *pfVar9 = fVar2 - fVar1;
      *pfVar12 = fVar1 + fVar2;
      iVar11 = iVar11 + unaff_EDI * 3;
      iVar14 = iVar14 + unaff_EDI * 3;
      fVar1 = in_EAX[iVar11 + -1] + in_EAX[iVar11 + -1];
      fVar2 = in_EAX[iVar14] + fVar1 * fVar6;
      *(float *)(param_2 + iVar17 * 4) = fVar1 + in_EAX[iVar14];
      pfVar8 = pfVar9 + unaff_EDI + unaff_EDI;
      iVar17 = iVar17 + unaff_EDI;
      fVar1 = (in_EAX[iVar11] + in_EAX[iVar11]) * fVar7;
      pfVar9[unaff_EDI] = fVar2 - fVar1;
      local_40 = pfVar12 + unaff_EDI + unaff_EDI;
      iVar11 = iVar11 + unaff_EDI * 3;
      iVar14 = iVar14 + unaff_EDI * 3;
      local_20 = (float *)((int)local_20 + -1);
      pfVar12[unaff_EDI] = fVar1 + fVar2;
    } while (local_20 != (float *)0x0);
  }
  if ((int)local_2c < param_1) {
    local_20 = (float *)(param_2 + iVar17 * 4);
    local_40 = (float *)(param_2 + (iVar10 * 2 + iVar17) * 4);
    local_34 = (float *)(param_2 + (iVar17 + iVar10) * 4);
    iVar17 = param_1 - (int)local_2c;
    pfVar8 = in_EAX + iVar14;
    pfVar9 = in_EAX + iVar11;
    do {
      fVar1 = pfVar9[-1] + pfVar9[-1];
      fVar2 = *pfVar8 + fVar1 * fVar6;
      *local_20 = fVar1 + *pfVar8;
      fVar1 = (*pfVar9 + *pfVar9) * fVar7;
      *local_34 = fVar2 - fVar1;
      *local_40 = fVar1 + fVar2;
      local_34 = local_34 + unaff_EDI;
      local_40 = local_40 + unaff_EDI;
      local_20 = local_20 + unaff_EDI;
      pfVar9 = pfVar9 + unaff_EDI * 3;
      pfVar8 = pfVar8 + unaff_EDI * 3;
      iVar17 = iVar17 + -1;
    } while (iVar17 != 0);
  }
  if ((unaff_EDI != 1) && (0 < param_1)) {
    local_20 = (float *)0x0;
    local_24 = 0;
    pfVar8 = in_EAX + unaff_EDI * 2;
    local_28 = param_2 + iVar10 * 8;
    local_10 = param_1;
    do {
      if (2 < unaff_EDI) {
        param_1 = local_28;
        local_34 = param_4;
        iVar11 = (unaff_EDI - 3U >> 1) + 1;
        pfVar9 = param_3 + 1;
        pfVar12 = pfVar8;
        pfVar15 = pfVar8;
        pfVar18 = in_EAX;
        local_40 = (float *)(param_2 + ((local_24 - (int)local_20) + iVar10) * 4);
        local_2c = (float *)(param_2 + (local_24 - (int)local_20) * 4);
        do {
          pfVar16 = pfVar15 + -2;
          pfVar13 = pfVar12 + 2;
          pfVar19 = pfVar18 + 2;
          fVar4 = pfVar18[1] + (pfVar15[-3] + pfVar12[1]) * fVar6;
          local_2c[1] = pfVar15[-3] + pfVar12[1] + pfVar18[1];
          fVar3 = *pfVar19 + (*pfVar13 - *pfVar16) * fVar6;
          local_2c[2] = (*pfVar13 - *pfVar16) + *pfVar19;
          fVar5 = (pfVar12[1] - pfVar15[-3]) * fVar7;
          fVar2 = (*pfVar13 + *pfVar16) * fVar7;
          fVar1 = fVar4 - fVar2;
          fVar2 = fVar2 + fVar4;
          fVar4 = fVar3 + fVar5;
          fVar3 = fVar3 - fVar5;
          local_40[1] = fVar1 * pfVar9[-1] - fVar4 * *pfVar9;
          local_40[2] = fVar1 * *pfVar9 + pfVar9[-1] * fVar4;
          *(float *)(param_1 + 4) =
               fVar2 * *local_34 - fVar3 * *(float *)((int)pfVar9 + ((int)param_4 - (int)param_3));
          fVar1 = *local_34;
          local_34 = local_34 + 2;
          iVar11 = iVar11 + -1;
          *(float *)(param_1 + 8) =
               fVar2 * *(float *)((int)pfVar9 + ((int)param_4 - (int)param_3)) + fVar1 * fVar3;
          pfVar9 = pfVar9 + 2;
          pfVar12 = pfVar13;
          pfVar15 = pfVar16;
          pfVar18 = pfVar19;
          param_1 = param_1 + 8;
          local_40 = local_40 + 2;
          local_2c = local_2c + 2;
        } while (iVar11 != 0);
      }
      local_28 = local_28 + unaff_EDI * 4;
      local_24 = local_24 + unaff_EDI * 3;
      local_20 = (float *)((int)local_20 + unaff_EDI * 2);
      pfVar8 = pfVar8 + unaff_EDI * 3;
      in_EAX = in_EAX + unaff_EDI * 3;
      local_10 = local_10 + -1;
    } while (local_10 != 0);
  }
  return;
}
