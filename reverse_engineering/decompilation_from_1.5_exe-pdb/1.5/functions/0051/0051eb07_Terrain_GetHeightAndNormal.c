/*
 * Entry: 0051eb07
 * Name: Terrain_GetHeightAndNormal
 * Namespace: Global
 * Signature: void Terrain_GetHeightAndNormal(double param_1, double param_2, float * param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Terrain_GetHeightAndNormal(double param_1,double param_2,float *param_3,VECTOR_3D *param_4)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  VECTOR_3D *pVVar8;
  long unaff_ESI;
  int unaff_EDI;
  float10 extraout_ST0;
  float10 fVar9;
  float10 fVar10;
  float10 extraout_ST0_00;
  VECTOR_3D local_30;
  VECTOR_3D local_24;
  undefined8 local_18;
  int local_10;
  int local_c;
  float local_8;
  
  fVar2 = (float)param_1 * Terrain.Grid_Scale;
  fVar1 = Terrain.Grid_Scale * (float)param_2;
  Set_Rounding(unaff_EDI);
  local_18._0_4_ = (int)(longlong)ROUND(fVar2);
  iVar3 = (int)local_18;
  local_8 = (float)(int)local_18;
  local_18 = (longlong)ROUND(fVar1);
  iVar4 = (int)local_18;
  local_c = (int)local_18;
  Set_Rounding(unaff_EDI);
  local_8 = fVar2 - (float)(int)local_8;
  fVar1 = fVar1 - (float)local_c;
  lVar5 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
  local_c = iVar4 + 1;
  local_10 = iVar3 + 1;
  local_18 = CONCAT44(lVar5,(int)local_18);
  lVar6 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
  if (fVar1 <= local_8) {
    lVar7 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
    local_10 = lVar5 - lVar7;
    fVar9 = (float10)local_10 * extraout_ST0_00;
    fVar10 = extraout_ST0_00 * (float10)(lVar7 - lVar6);
  }
  else {
    lVar7 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
    fVar9 = (float10)(lVar7 - lVar6) * extraout_ST0;
    fVar10 = extraout_ST0 * (float10)(lVar5 - lVar7);
  }
  local_24.x = (float)fVar9;
  local_24.y = 1.0;
  local_24.z = (float)fVar10;
  if (param_4 != (VECTOR_3D *)0x0) {
    pVVar8 = Normalize_Vector(&local_30,&local_24);
    param_4->x = pVVar8->x;
    param_4->y = pVVar8->y;
    param_4->z = pVVar8->z;
  }
  if (param_3 != (float *)0x0) {
    *param_3 = (float)local_18._4_4_ * 0.1 -
               (local_24.x * local_8 + local_24.z * fVar1) * Terrain.Grid_Size;
  }
  return;
}
