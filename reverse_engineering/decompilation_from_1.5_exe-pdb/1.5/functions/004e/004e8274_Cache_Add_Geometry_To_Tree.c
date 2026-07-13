/*
 * Entry: 004e8274
 * Name: Cache_Add_Geometry_To_Tree
 * Namespace: Global
 * Signature: void Cache_Add_Geometry_To_Tree(MATRIX_STACK * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cache_Add_Geometry_To_Tree(MATRIX_STACK *param_1,long param_2)

{
  MATRIX_LIST *pMVar1;
  _OBJ76 *p_Var2;
  MATRIX_LIST **ppMVar3;
  
  if (0 < param_2) {
    ppMVar3 = &param_1->Elem;
    do {
      pMVar1 = *ppMVar3;
      p_Var2 = pMVar1->Obj;
      GeoCache_SelectLOD(p_Var2,LOD);
      Cache_Add_Polygons_to_Tree(p_Var2,&pMVar1->Mat,pMVar1->Vertex_Offset);
      ppMVar3 = ppMVar3 + 2;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return;
}
