/*
 * Entry: 0051df87
 * Name: PointGridIntersection
 * Namespace: Global
 * Signature: int PointGridIntersection(long param_1, long param_2, VECTOR_3D_LONG param_3, VECTOR_3D param_4, float * param_5, VECTOR_3D * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
PointGridIntersection
          (long param_1,long param_2,VECTOR_3D_LONG param_3,VECTOR_3D param_4,float *param_5,
          VECTOR_3D *param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  VECTOR_3D *pVVar8;
  int iVar9;
  long unaff_ESI;
  long unaff_EDI;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  float local_14;
  float local_10;
  float local_c;
  long local_8;
  
  local_8 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
  local_14 = (float)(param_1 + 1);
  lVar5 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
  lVar6 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
  lVar7 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
  fVar1 = Terrain.Grid_Scale * 0.1;
  local_20.y = 1.0 / fVar1;
  local_20.x = (float)(local_8 - lVar5);
  local_20.z = (float)(lVar5 - lVar7);
  local_14 = param_4.y * local_20.y;
  local_c = param_4.x * local_20.x + param_4.z * local_20.z + local_14;
  if (local_c < -1.1920929e-07) {
    local_10 = (float)param_3.z - (float)param_2;
    fVar2 = ((float)param_3.x - (float)param_1) * local_20.x +
            local_10 * local_20.z + ((float)param_3.y - (float)local_8 * fVar1) * local_20.y;
    if ((fVar2 <= -0.1) || (fVar2 = -(fVar2 / local_c), *param_5 <= fVar2)) goto LAB_0051e0da;
    fVar4 = param_4.x * fVar2 + ((float)param_3.x - (float)param_1);
    fVar3 = param_4.z * fVar2 + local_10;
    if ((fVar3 < fVar4 == (fVar3 == fVar4)) || ((0.0 < fVar3 == (fVar3 == 0.0) || (1.0 < fVar4))))
    goto LAB_0051e0da;
LAB_0051e0af:
    *param_5 = fVar2;
    if (param_6 != (VECTOR_3D *)0x0) {
      pVVar8 = Normalize_Vector(&local_2c,&local_20);
      param_6->x = pVVar8->x;
      param_6->y = pVVar8->y;
      param_6->z = pVVar8->z;
    }
    iVar9 = 1;
  }
  else {
LAB_0051e0da:
    local_20.x = (float)(lVar6 - lVar7);
    local_10 = (float)(local_8 - lVar6);
    local_20.z = (float)(int)local_10;
    fVar2 = param_4.x * local_20.x + param_4.z * local_20.z + local_14;
    if (fVar2 < -1.1920929e-07) {
      fVar1 = local_20.x * ((float)param_3.x - (float)param_1) +
              ((float)param_3.z - (float)param_2) * local_20.z +
              ((float)param_3.y - (float)local_8 * fVar1) * local_20.y;
      if ((-0.1 < fVar1) && (fVar2 = -(fVar1 / fVar2), fVar2 < *param_5)) {
        fVar3 = param_4.x * fVar2 + ((float)param_3.x - (float)param_1);
        fVar1 = param_4.z * fVar2 + ((float)param_3.z - (float)param_2);
        if ((fVar3 < fVar1 != (fVar3 == fVar1)) &&
           ((0.0 < fVar3 != (fVar3 == 0.0) && (fVar1 <= 1.0)))) goto LAB_0051e0af;
      }
    }
    iVar9 = 0;
  }
  return iVar9;
}
