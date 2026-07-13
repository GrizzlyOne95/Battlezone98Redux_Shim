/*
 * Entry: 004e7e29
 * Name: Cache_Build_Bsp_Backbone
 * Namespace: Global
 * Signature: long Cache_Build_Bsp_Backbone(_OBJ76 * param_1, MAT_3D * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Cache_Build_Bsp_Backbone(_OBJ76 *param_1,MAT_3D *param_2,long param_3)

{
  MATRIX_LIST *pMVar1;
  long lVar2;
  MAT_3D *pMVar3;
  int iVar4;
  int iVar5;
  _OBJ76 *unaff_EDI;
  MAT_3D *pMVar6;
  MAT_3D local_84;
  MAT_3D local_44;
  
  iVar5 = param_3;
  for (; param_1 != (_OBJ76 *)0x0; param_1 = param_1->sibling) {
    pMVar3 = Matrix_Multiply(&local_84,&param_1->transform,param_2);
    pMVar6 = &local_44;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      pMVar6->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
    }
    iVar4 = Cache_Is_Moving_Obj(unaff_EDI);
    lVar2 = Moving_Objects_Counter;
    pMVar1 = Bsp_Moving_Objects;
    param_3 = iVar5;
    if (iVar4 == 0) {
      iVar4 = GeoCache_SelectLOD(param_1,LOD);
      if (((iVar4 == 1) && (param_1->geom != (_GEOMETRY *)0x0)) &&
         (param_1->geom->vertex_count != 0)) {
        param_3 = iVar5 + 1;
        pMVar1 = Bsp_Backbone + iVar5;
        pMVar3 = &local_44;
        pMVar6 = &pMVar1->Mat;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          pMVar6->right_x = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
        }
        pMVar1->Obj = param_1;
        pMVar1->Vertex_Offset = Entity_Vertex_Count;
        Entity_Vertex_Count = Entity_Vertex_Count + param_1->geom->vertex_count;
      }
      if (param_1->child != (_OBJ76 *)0x0) {
        param_3 = Cache_Build_Bsp_Backbone(param_1->child,&local_44,param_3);
      }
    }
    else {
      Moving_Objects_Counter = Moving_Objects_Counter + 1;
      pMVar3 = param_2;
      pMVar6 = &Bsp_Moving_Objects[lVar2].Mat;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar6->right_x = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pMVar6 = (MAT_3D *)&pMVar6->right_y;
      }
      pMVar1[lVar2].Obj = param_1;
    }
    iVar5 = param_3;
  }
  return iVar5;
}
