/*
 * Entry: 004e8e55
 * Name: Recursive_Build_Display_List
 * Namespace: Global
 * Signature: void Recursive_Build_Display_List(_OBJ76 * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Recursive_Build_Display_List(_OBJ76 *param_1,MAT_3D *param_2)

{
  MAT_3D *pMVar1;
  int iVar2;
  CAMERA *unaff_EDI;
  MAT_3D *pMVar3;
  MAT_3D local_84;
  MAT_3D local_44;
  
  do {
    pMVar1 = Matrix_Multiply(&local_84,&param_1->transform,param_2);
    pMVar3 = &local_44;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      pMVar3->right_x = pMVar1->right_x;
      pMVar1 = (MAT_3D *)&pMVar1->right_y;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
    }
    if ((param_1->flags & 1) == 0) {
      iVar2 = GeoCache_SelectLOD(param_1,LOD);
      if (((iVar2 == 1) && (param_1->geom != (_GEOMETRY *)0x0)) &&
         (param_1->geom->vertex_count != 0)) {
        Add_Polygons_to_Tree(param_1,&local_44,unaff_EDI);
      }
    }
    if (param_1->child != (_OBJ76 *)0x0) {
      Recursive_Build_Display_List(param_1->child,&local_44);
    }
    param_1 = param_1->sibling;
  } while (param_1 != (_OBJ76 *)0x0);
  return;
}
