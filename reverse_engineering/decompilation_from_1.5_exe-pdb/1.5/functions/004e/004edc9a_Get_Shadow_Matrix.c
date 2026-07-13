/*
 * Entry: 004edc9a
 * Name: Get_Shadow_Matrix
 * Namespace: Global
 * Signature: int Get_Shadow_Matrix(CAMERA * param_1, MAT_3D * param_2, VECTOR_3D * param_3, MAT_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Get_Shadow_Matrix(CAMERA *param_1,MAT_3D *param_2,VECTOR_3D *param_3,MAT_3D *param_4)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  PLANE *pPVar6;
  MAT_3D *pMVar7;
  float unaff_EDI;
  MAT_3D *pMVar8;
  MAT_3D local_88;
  PLANE local_48;
  PLANE local_38;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  local_1c.x = param_3->x;
  local_1c.y = param_3->y;
  local_1c.z = param_3->z;
  local_10.x = local_1c.x - Light_Vector.x * 128.0;
  local_10.y = local_1c.y - Light_Vector.y * 128.0;
  local_10.z = local_1c.z - Light_Vector.z * 128.0;
  uVar3 = param_3->y;
  uVar4 = param_3->z;
  VVar1.y = (float)uVar4;
  VVar1.x = (float)uVar3;
  VVar1.z = local_10.x;
  VVar2.y = local_10.z;
  VVar2.x = local_10.y;
  VVar2.z = unaff_EDI;
  iVar5 = Get_ShadowPosition((VECTOR_3D *)param_3->x,VVar1,VVar2);
  if (iVar5 != 0) {
    local_1c.x = Center.x;
    local_1c.z = Center.z - 2.0;
    local_10.x = Center.x + 2.0;
    local_28.z = Center.z + 2.0;
    local_28.x = Center.x - 2.0;
    local_10.z = local_28.z;
    local_1c.y = Terrain_FindFloor((double)Center.x,(double)local_1c.z);
    local_1c.y = local_1c.y + 0.5;
    local_10.y = Terrain_FindFloor((double)local_10.x,(double)local_10.z);
    local_10.y = local_10.y + 0.5;
    local_28.y = Terrain_FindFloor((double)local_28.x,(double)local_28.z);
    local_28.y = local_28.y + 0.5;
    pPVar6 = Plane_Equation(&local_48,&local_1c,&local_28,&local_10);
    local_38.surf_normal.x = (pPVar6->surf_normal).x;
    local_38.surf_normal.y = (pPVar6->surf_normal).y;
    local_38.surf_normal.z = (pPVar6->surf_normal).z;
    local_38.dist = pPVar6->dist;
    iVar5 = Create_Oblique_Projection_Matrix(param_2,&local_38,&Light_Vector);
    if (iVar5 != 0) {
      pMVar7 = Matrix_Multiply(&local_88,param_2,&param_1->Matrix);
      pMVar8 = param_2;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar8->right_x = pMVar7->right_x;
        pMVar7 = (MAT_3D *)&pMVar7->right_y;
        pMVar8 = (MAT_3D *)&pMVar8->right_y;
      }
      pMVar7 = Matrix_Multiply(&local_88,param_4,param_2);
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        param_2->right_x = pMVar7->right_x;
        pMVar7 = (MAT_3D *)&pMVar7->right_y;
        param_2 = (MAT_3D *)&param_2->right_y;
      }
      return 1;
    }
  }
  return 0;
}
