/*
 * Entry: 004e96c0
 * Name: Render_CachedBSP_Entity
 * Namespace: Global
 * Signature: void Render_CachedBSP_Entity(SORTING_LIST_ENTITY * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_CachedBSP_Entity(SORTING_LIST_ENTITY *param_1,CAMERA *param_2)

{
  tagENTITY *ptVar1;
  _OBJ76 *p_Var2;
  float fVar3;
  float fVar4;
  float fVar5;
  MAT_3D *pMVar6;
  int iVar7;
  BSP_POLYGON *unaff_ESI;
  MAT_3D *pMVar8;
  MAT_3D local_44;
  
  ptVar1 = param_1->Entity;
  if (((byte)LODInfo.mergeBSP & 4) == 0) {
    Render_BuildNewBSP_Entity(param_1,param_2);
  }
  else {
    p_Var2 = ptVar1->obj76;
    if (p_Var2->child != (_OBJ76 *)0x0) {
      LODInfo.flags = param_1->lodFlags;
      if ((LODInfo.flags & 0x20) == 0) {
        Render_Shadow(ptVar1,param_2);
      }
      if ((char)LODInfo.flags < '\0') {
        LOD = 1;
      }
      else {
        LOD = LODInfo.flags >> 3 & 2;
      }
      if ((((LODInfo.flags & 8) == 0) || (ptVar1->Bsp_Container == (BSP_CONTAINER *)0x0)) ||
         (ptVar1->Bsp_Geom_LOD != LOD)) {
        Cache_Invalidate_Bsp(ptVar1);
        Cache_Entity_Bsp(ptVar1,LOD);
      }
      Entity_Vertex_Count = 0;
      Luma_Base_Entry = &Vertex_Pool[ptVar1->Bsp_Vertex_Pool_Size].x;
      Vertex_Table = (VECTOR_3D *)
                     (&((VECTOR_3D *)Luma_Base_Entry)->x + ptVar1->Bsp_Vertex_Pool_Size);
      if ((LODInfo.flags & 0x44) == 0) {
        Select_Light_Sources(p_Var2);
      }
      Project_Polygon_Only = param_1->Project_Polygons_Flag;
      Local_Camera = param_2;
      pMVar6 = &p_Var2->transform;
      pMVar8 = &World_Matrix;
      for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
        pMVar8->right_x = pMVar6->right_x;
        pMVar6 = (MAT_3D *)&pMVar6->right_y;
        pMVar8 = (MAT_3D *)&pMVar8->right_y;
      }
      pMVar6 = Matrix_Multiply(&local_44,&p_Var2->transform,&param_2->Matrix);
      pMVar8 = &Camera_Transform;
      for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
        pMVar8->right_x = pMVar6->right_x;
        pMVar6 = (MAT_3D *)&pMVar6->right_y;
        pMVar8 = (MAT_3D *)&pMVar8->right_y;
      }
      fVar5 = (float)Camera_Transform.posit_z;
      fVar4 = (float)Camera_Transform.posit_y;
      fVar3 = (float)Camera_Transform.posit_x;
      Test_Point.x = -(Camera_Transform.right_z * fVar5 + Camera_Transform.right_y * fVar4 +
                      Camera_Transform.right_x * fVar3);
      Test_Point.y = -(Camera_Transform.up_x * fVar3 +
                      Camera_Transform.up_y * fVar4 + Camera_Transform.up_z * fVar5);
      Test_Point.z = -(fVar3 * Camera_Transform.front_x +
                      Camera_Transform.front_z * fVar5 + Camera_Transform.front_y * fVar4);
      Cache_Recursive_Transform_Vertex_List(p_Var2->child,&p_Var2->transform);
      Cache_Render_Bsp_Mesh(unaff_ESI);
    }
  }
  return;
}
