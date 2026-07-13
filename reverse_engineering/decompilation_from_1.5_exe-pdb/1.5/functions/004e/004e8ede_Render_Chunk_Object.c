/*
 * Entry: 004e8ede
 * Name: Render_Chunk_Object
 * Namespace: Global
 * Signature: void Render_Chunk_Object(SORTING_LIST_ENTITY * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Chunk_Object(SORTING_LIST_ENTITY *param_1,CAMERA *param_2)

{
  _OBJ76 *p_Var1;
  long unaff_EDI;
  _OBJ76 *p_Var2;
  
  p_Var1 = param_1->Obj;
  if (p_Var1->child != (_OBJ76 *)0x0) {
    Root_Polygon = (BSP_POLYGON *)0x0;
    Local_Camera = param_2;
    LOD = param_1->LOD;
    Project_Polygon_Only = param_1->Project_Polygons_Flag;
    Vertex_Table = Vertex_Pool;
    Poly_Leading_Ptr = Quadtree_Cell_Pool;
    p_Var2 = p_Var1;
    Select_Light_Sources(p_Var1);
    Submit_Sorting_Planes((_OBJ76 *)&p_Var1->transform,(MAT_3D *)p_Var2,unaff_EDI);
    if (p_Var1->child != (_OBJ76 *)0x0) {
      Recursive_Build_Display_List(p_Var1->child,&p_Var1->transform);
    }
    Render_Bsp_Mesh((BSP_POLYGON *)param_1);
    return;
  }
  return;
}
