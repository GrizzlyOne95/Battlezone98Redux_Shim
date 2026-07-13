/*
 * Entry: 004ecebd
 * Name: Obj76_Bounding_Box
 * Namespace: Global
 * Signature: void Obj76_Bounding_Box(_OBJ76 * param_1, MAT_3D * param_2, VECTOR_3D * param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Obj76_Bounding_Box(_OBJ76 *param_1,MAT_3D *param_2,VECTOR_3D *param_3,VECTOR_3D *param_4)

{
  _GEOMETRY *p_Var1;
  MAT_3D *pMVar2;
  int iVar3;
  _OBJ76 *p_Var4;
  MAT_3D *pMVar5;
  int iVar6;
  MAT_3D local_90;
  MAT_3D local_50;
  VECTOR_3D local_10;
  
  p_Var4 = param_1;
  do {
    pMVar2 = Matrix_Multiply(&local_90,&p_Var4->transform,param_2);
    pMVar5 = &local_50;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar5->right_x = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
    }
    if ((p_Var4->flags & 1) == 0) {
      iVar6 = 0;
      iVar3 = GeoCache_SelectLOD(p_Var4,0);
      if ((iVar3 == 1) && (p_Var1 = p_Var4->geom, 0 < p_Var1->vertex_count)) {
        param_1 = (_OBJ76 *)0x0;
        do {
          Vector_Transform(&local_10,
                           (VECTOR_3D *)
                           ((param_1->tex_info).group + (int)(p_Var1->vertex_table + -10)),1,
                           &local_50);
          if (local_10.x < param_3->x) {
            param_3->x = local_10.x;
          }
          if (local_10.y < param_3->y) {
            param_3->y = local_10.y;
          }
          if (local_10.z < param_3->z) {
            param_3->z = local_10.z;
          }
          if (param_4->x < local_10.x) {
            param_4->x = local_10.x;
          }
          if (param_4->y < local_10.y) {
            param_4->y = local_10.y;
          }
          if (param_4->z < local_10.z) {
            param_4->z = local_10.z;
          }
          param_1 = (_OBJ76 *)((int)&param_1->id + 4);
          iVar6 = iVar6 + 1;
        } while (iVar6 < p_Var1->vertex_count);
      }
    }
    if (p_Var4->child != (_OBJ76 *)0x0) {
      Obj76_Bounding_Box(p_Var4->child,&local_50,param_3,param_4);
    }
    p_Var4 = p_Var4->sibling;
  } while (p_Var4 != (_OBJ76 *)0x0);
  return;
}
