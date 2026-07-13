/*
 * Entry: 0051de57
 * Name: Transform_Terrain_Vertex_List
 * Namespace: Global
 * Signature: void Transform_Terrain_Vertex_List(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Transform_Terrain_Vertex_List(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  MAT_3D *pMVar4;
  VECTOR_3D *pVVar5;
  int iVar6;
  long lVar7;
  MAT_3D *pMVar8;
  bool bVar9;
  MAT_3D local_90;
  MAT_3D local_50;
  float local_10;
  float local_c;
  float local_8;
  
  pMVar4 = &Identity_Matrix;
  pMVar8 = &local_50;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    pMVar8->right_x = pMVar4->right_x;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
  }
  local_50.right_x = Terrain.Grid_Size;
  local_50.front_z = Terrain.Grid_Size;
  local_50.up_y = 0.1;
  local_10 = 1000.0;
  local_c = 1000.0;
  local_8 = 16000.0;
  pMVar4 = Matrix_Multiply(&local_90,&local_50,&(Terrain.Camera)->Matrix);
  pMVar8 = &local_50;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    pMVar8->right_x = pMVar4->right_x;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
  }
  bVar9 = false;
  pVVar5 = Vertex_Pool;
  for (lVar7 = Terrain.Vertex_Counter; lVar7 != 0 && bVar9 == lVar7 < 0; lVar7 = lVar7 + -1) {
    fVar1 = pVVar5->x;
    fVar2 = pVVar5->z;
    fVar3 = local_50.front_z * pVVar5->z + local_50.up_z * pVVar5->y + local_50.right_z * pVVar5->x
            + (float)local_50.posit_z;
    pVVar5->x = local_50.front_x * pVVar5->z +
                local_50.up_x * pVVar5->y + local_50.right_x * pVVar5->x + (float)local_50.posit_x;
    pVVar5->z = fVar3;
    fVar3 = fVar3 + local_10;
    if ((int)pVVar5->y < (int)local_8) {
      local_8 = pVVar5->y;
    }
    pVVar5->y = local_50.front_y * fVar2 + local_50.up_y * pVVar5->y + local_50.right_y * fVar1 +
                (float)local_50.posit_y;
    pVVar5 = pVVar5 + 1;
    if ((int)local_c <= (int)fVar3) {
      local_c = fVar3;
    }
    bVar9 = SBORROW4(lVar7,1);
  }
  Terrain.Lowest_Elevation = local_8 * 0.1;
  SortZmin = -300.0;
  SortZmax = (local_c - -300.0) - 1000.0;
  return;
}
