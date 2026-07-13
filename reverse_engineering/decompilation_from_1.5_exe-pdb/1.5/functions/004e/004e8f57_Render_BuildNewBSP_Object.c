/*
 * Entry: 004e8f57
 * Name: Render_BuildNewBSP_Object
 * Namespace: Global
 * Signature: void Render_BuildNewBSP_Object(SORTING_LIST_ENTITY * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_BuildNewBSP_Object(SORTING_LIST_ENTITY *param_1,CAMERA *param_2)

{
  _OBJ76 *p_Var1;
  uint uVar2;
  int iVar3;
  CAMERA *unaff_ESI;
  
  LODInfo.flags = param_1->lodFlags;
  if ((char)LODInfo.flags < '\0') {
    uVar2 = 1;
  }
  else {
    uVar2 = LODInfo.flags >> 3 & 2;
  }
  Root_Polygon = (BSP_POLYGON *)0x0;
  Local_Camera = param_2;
  Project_Polygon_Only = param_1->Project_Polygons_Flag;
  p_Var1 = param_1->Obj;
  Vertex_Table = Vertex_Pool;
  Poly_Leading_Ptr = Quadtree_Cell_Pool;
  if ((p_Var1->flags & 1) == 0) {
    iVar3 = GeoCache_SelectLOD(p_Var1,uVar2);
    if (((iVar3 == 1) && (p_Var1->geom != (_GEOMETRY *)0x0)) && (p_Var1->geom->vertex_count != 0)) {
      Add_Polygons_to_Tree(p_Var1,&p_Var1->transform,unaff_ESI);
    }
  }
  Render_Bsp_Mesh((BSP_POLYGON *)param_1);
  return;
}
