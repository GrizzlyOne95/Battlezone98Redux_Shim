/*
 * Entry: 0052001d
 * Name: TrimToViewPort
 * Namespace: Global
 * Signature: void TrimToViewPort(CAMERA * param_1, int * param_2, int * param_3, int * param_4, int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TrimToViewPort(CAMERA *param_1,int *param_2,int *param_3,int *param_4,int *param_5)

{
  VECTOR_3D_LONG *pVVar1;
  double *pdVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  double *pdVar9;
  int iVar10;
  int local_24;
  int local_1c;
  int local_14;
  int local_c;
  
  pVVar1 = param_1->View_Pyramid;
  dVar3 = pVVar1->x;
  dVar4 = pVVar1->x;
  if (View_Record.Current_View == OVER_VIEW) {
    pdVar2 = &param_1->View_Pyramid[0].z;
    dVar5 = *pdVar2;
    dVar6 = *pdVar2;
    pdVar9 = &param_1->View_Pyramid[1].y;
    iVar10 = 4;
    do {
      dVar7 = *pdVar9 - param_1->View_Pyramid[0].y;
      if (dVar7 < 0.0) {
        dVar7 = -dVar7;
      }
      dVar7 = param_1->View_Pyramid[0].y / dVar7;
      dVar8 = dVar7 * (((VECTOR_3D_LONG *)(pdVar9 + -1))->x - pVVar1->x) + pVVar1->x;
      dVar7 = (pdVar9[1] - *pdVar2) * dVar7 + *pdVar2;
      if (dVar8 < dVar3) {
        dVar3 = dVar8;
      }
      if (dVar4 < dVar8) {
        dVar4 = dVar8;
      }
      if (dVar7 < dVar5) {
        dVar5 = dVar7;
      }
      if (dVar6 < dVar7) {
        dVar6 = dVar7;
      }
      pdVar9 = pdVar9 + 3;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
  }
  else {
    if (param_1->View_Pyramid[1].x < dVar3) {
      dVar3 = param_1->View_Pyramid[1].x;
    }
    if (dVar4 < param_1->View_Pyramid[1].x) {
      dVar4 = param_1->View_Pyramid[1].x;
    }
    if (param_1->View_Pyramid[2].x < dVar3) {
      dVar3 = param_1->View_Pyramid[2].x;
    }
    if (dVar4 < param_1->View_Pyramid[2].x) {
      dVar4 = param_1->View_Pyramid[2].x;
    }
    if (param_1->View_Pyramid[3].x < dVar3) {
      dVar3 = param_1->View_Pyramid[3].x;
    }
    if (dVar4 < param_1->View_Pyramid[3].x) {
      dVar4 = param_1->View_Pyramid[3].x;
    }
    if (param_1->View_Pyramid[4].x < dVar3) {
      dVar3 = param_1->View_Pyramid[4].x;
    }
    if (dVar4 < param_1->View_Pyramid[4].x) {
      dVar4 = param_1->View_Pyramid[4].x;
    }
    pdVar2 = &param_1->View_Pyramid[0].z;
    dVar5 = *pdVar2;
    dVar6 = *pdVar2;
    if (param_1->View_Pyramid[1].z < dVar5) {
      dVar5 = param_1->View_Pyramid[1].z;
    }
    if (dVar6 < param_1->View_Pyramid[1].z) {
      dVar6 = param_1->View_Pyramid[1].z;
    }
    if (param_1->View_Pyramid[2].z < dVar5) {
      dVar5 = param_1->View_Pyramid[2].z;
    }
    if (dVar6 < param_1->View_Pyramid[2].z) {
      dVar6 = param_1->View_Pyramid[2].z;
    }
    if (param_1->View_Pyramid[3].z < dVar5) {
      dVar5 = param_1->View_Pyramid[3].z;
    }
    if (dVar6 < param_1->View_Pyramid[3].z) {
      dVar6 = param_1->View_Pyramid[3].z;
    }
    if (param_1->View_Pyramid[4].z < dVar5) {
      dVar5 = param_1->View_Pyramid[4].z;
    }
    if (dVar6 < param_1->View_Pyramid[4].z) {
      dVar6 = param_1->View_Pyramid[4].z;
    }
  }
  dVar7 = (double)Terrain.Grid_Scale;
  dVar3 = dVar7 * dVar3 + Float2Int;
  local_c = SUB84(dVar7 * dVar4 + Float2Int,0);
  dVar4 = dVar7 * dVar5 + Float2Int;
  local_14 = SUB84(dVar7 * dVar6 + Float2Int,0);
  _ftol2_sse();
  _ftol2_sse();
  _ftol2_sse();
  *param_2 = extraout_EAX_00 - extraout_EAX;
  *param_4 = extraout_EAX_00 + extraout_EAX;
  *param_3 = extraout_EAX_01 - extraout_EAX;
  *param_5 = extraout_EAX_01 + extraout_EAX;
  local_1c = SUB84(dVar3,0);
  if (*param_2 < local_1c) {
    *param_2 = local_1c;
  }
  if (local_c + 1 < *param_4) {
    *param_4 = local_c + 1;
  }
  local_24 = SUB84(dVar4,0);
  if (*param_3 < local_24) {
    *param_3 = local_24;
  }
  if (local_14 + 1 < *param_5) {
    *param_5 = local_14 + 1;
  }
  return;
}
