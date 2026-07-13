/*
 * Entry: 004e9615
 * Name: Cache_Recursive_Transform_Vertex_List
 * Namespace: Global
 * Signature: void Cache_Recursive_Transform_Vertex_List(_OBJ76 * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Cache_Recursive_Transform_Vertex_List(_OBJ76 *param_1,MAT_3D *param_2)

{
  MAT_3D *pMVar1;
  int iVar2;
  MAT_3D *unaff_ESI;
  _OBJ76 *unaff_EDI;
  MAT_3D *pMVar3;
  bool bVar4;
  MAT_3D local_88;
  MAT_3D local_48;
  int local_8;
  
  do {
    local_8 = Cache_Is_Moving_Obj(unaff_EDI);
    pMVar1 = Matrix_Multiply(&local_88,&param_1->transform,param_2);
    bVar4 = local_8 == 0;
    pMVar3 = &local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      pMVar3->right_x = pMVar1->right_x;
      pMVar1 = (MAT_3D *)&pMVar1->right_y;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
    }
    if (bVar4) {
      iVar2 = GeoCache_SelectLOD(param_1,LOD);
      if (((iVar2 == 1) && (param_1->geom != (_GEOMETRY *)0x0)) &&
         (param_1->geom->vertex_count != 0)) {
        if ((param_1->flags & 1) == 0) {
          Cache_Transform_Vertex_List(unaff_EDI,unaff_ESI);
        }
        Entity_Vertex_Count = Entity_Vertex_Count + param_1->geom->vertex_count;
      }
      if (param_1->child != (_OBJ76 *)0x0) {
        Cache_Recursive_Transform_Vertex_List(param_1->child,&local_48);
      }
    }
    param_1 = param_1->sibling;
  } while (param_1 != (_OBJ76 *)0x0);
  return;
}
