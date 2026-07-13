/*
 * Entry: 00476aeb
 * Name: Line_Clip_Polygon
 * Namespace: Global
 * Signature: long Line_Clip_Polygon(POINT_3D * param_1, POINT_3D * param_2, float param_3, float param_4, float param_5, float param_6, long param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
Line_Clip_Polygon(POINT_3D *param_1,POINT_3D *param_2,float param_3,float param_4,float param_5,
                 float param_6,long param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  POINT_3D *pPVar5;
  float fVar6;
  int in_EAX;
  float *in_ECX;
  int iVar7;
  POINT_3D *pPVar8;
  POINT_3D *pPVar9;
  float *pfVar10;
  int local_c;
  
  fVar6 = param_3;
  pPVar5 = param_2;
  pPVar8 = param_1 + in_EAX + -1;
  fVar1 = (pPVar8->Vector).y * param_3;
  param_2 = (POINT_3D *)0x0;
  if (0 < in_EAX) {
    param_3 = (float)(in_ECX + 6);
    fVar1 = (float)pPVar5 * (pPVar8->Vector).x + fVar1 + param_4;
    local_c = in_EAX;
    do {
      fVar3 = (param_1->Vector).y * fVar6 + (param_1->Vector).x * (float)pPVar5 + param_4;
      if (fVar3 <= 0.0) {
        if (fVar1 > 0.0) {
          param_3 = (float)((int)param_3 + 0x18);
          fVar4 = (param_1->Vector).y - (pPVar8->Vector).y;
          fVar2 = (param_1->Vector).x - (pPVar8->Vector).x;
          fVar1 = fVar1 / (fVar4 * fVar6 + fVar2 * (float)pPVar5);
          in_ECX[1] = (pPVar8->Vector).y - fVar1 * fVar4;
          *in_ECX = (pPVar8->Vector).x - fVar2 * fVar1;
          param_2 = (POINT_3D *)((int)&(param_2->Vector).x + 1);
          in_ECX[2] = (pPVar8->Vector).z;
          in_ECX[5] = param_5;
          in_ECX = in_ECX + 6;
        }
      }
      else {
        iVar7 = 6;
        pPVar9 = param_1;
        pfVar10 = (float *)param_3;
        if (fVar1 <= 0.0) {
          for (; iVar7 != 0; iVar7 = iVar7 + -1) {
            *pfVar10 = (pPVar9->Vector).x;
            pPVar9 = (POINT_3D *)&(pPVar9->Vector).y;
            pfVar10 = pfVar10 + 1;
          }
          fVar4 = (param_1->Vector).y - (pPVar8->Vector).y;
          fVar2 = (param_1->Vector).x - (pPVar8->Vector).x;
          param_3 = (float)((int)param_3 + 0x30);
          fVar1 = fVar1 / (fVar4 * fVar6 + fVar2 * (float)pPVar5);
          in_ECX[1] = (pPVar8->Vector).y - fVar1 * fVar4;
          *in_ECX = (pPVar8->Vector).x - fVar2 * fVar1;
          param_2 = (POINT_3D *)((int)&(param_2->Vector).x + 2);
          in_ECX[2] = (pPVar8->Vector).z;
          in_ECX[5] = param_5;
          in_ECX = in_ECX + 0xc;
        }
        else {
          param_3 = (float)((int)param_3 + 0x18);
          pPVar8 = param_1;
          pfVar10 = in_ECX;
          for (; iVar7 != 0; iVar7 = iVar7 + -1) {
            *pfVar10 = (pPVar8->Vector).x;
            pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
            pfVar10 = pfVar10 + 1;
          }
          in_ECX = in_ECX + 6;
          param_2 = (POINT_3D *)((int)&(param_2->Vector).x + 1);
        }
      }
      local_c = local_c + -1;
      pPVar8 = param_1;
      fVar1 = fVar3;
      param_1 = param_1 + 1;
    } while (local_c != 0);
  }
  return (long)param_2;
}
