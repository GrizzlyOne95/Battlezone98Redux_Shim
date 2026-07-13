/*
 * Entry: 004e986e
 * Name: Render_CachedBSP_Object
 * Namespace: Global
 * Signature: void Render_CachedBSP_Object(SORTING_LIST_ENTITY * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_CachedBSP_Object(SORTING_LIST_ENTITY *param_1,CAMERA *param_2)

{
  _OBJ76 *p_Var1;
  int iVar2;
  CAMERA *unaff_ESI;
  
  Root_Polygon = (BSP_POLYGON *)0x0;
  Local_Camera = param_2;
  LOD = param_1->LOD;
  p_Var1 = param_1->Obj;
  Project_Polygon_Only = param_1->Project_Polygons_Flag;
  LODInfo.flags = param_1->lodFlags;
  Vertex_Table = Vertex_Pool;
  Poly_Leading_Ptr = Quadtree_Cell_Pool;
  Select_Light_Sources(p_Var1);
  if ((p_Var1->flags & 1) == 0) {
    iVar2 = GeoCache_SelectLOD(p_Var1,LOD);
    if (((iVar2 == 1) && (p_Var1->geom != (_GEOMETRY *)0x0)) && (p_Var1->geom->vertex_count != 0)) {
      Add_Polygons_to_Tree(p_Var1,&p_Var1->transform,unaff_ESI);
    }
  }
  Render_Bsp_Mesh((BSP_POLYGON *)param_1);
  return;
}
