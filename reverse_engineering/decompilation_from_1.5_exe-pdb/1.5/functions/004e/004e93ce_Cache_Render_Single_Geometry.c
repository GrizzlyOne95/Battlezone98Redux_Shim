/*
 * Entry: 004e93ce
 * Name: Cache_Render_Single_Geometry
 * Namespace: Global
 * Signature: void Cache_Render_Single_Geometry(BSP_POLYGON * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cache_Render_Single_Geometry(BSP_POLYGON *param_1)

{
  _OBJ76 *p_Var1;
  int in_EAX;
  MAT_3D *pMVar2;
  int iVar3;
  CAMERA *unaff_EDI;
  MAT_3D *pMVar4;
  MAT_3D local_84;
  MAT_3D local_44;
  
  Root_Polygon = (BSP_POLYGON *)0x0;
  p_Var1 = *(_OBJ76 **)(in_EAX + 4);
  Poly_Leading_Ptr = Quadtree_Cell_Pool;
  pMVar2 = Matrix_Multiply(&local_84,&p_Var1->transform,(MAT_3D *)(in_EAX + 0x30));
  pMVar4 = &local_44;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar4->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  pMVar2 = Matrix_Multiply(&local_84,&local_44,&World_Matrix);
  pMVar4 = &local_44;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar4->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  if ((p_Var1->flags & 1) == 0) {
    iVar3 = GeoCache_SelectLOD(p_Var1,LOD);
    if (((iVar3 == 1) && (p_Var1->geom != (_GEOMETRY *)0x0)) && (p_Var1->geom->vertex_count != 0)) {
      Add_Polygons_to_Tree(p_Var1,&local_44,unaff_EDI);
    }
  }
  if (p_Var1->child != (_OBJ76 *)0x0) {
    Recursive_Build_Display_List(p_Var1->child,&local_44);
  }
  Render_Bsp_Mesh((BSP_POLYGON *)unaff_EDI);
  return;
}
