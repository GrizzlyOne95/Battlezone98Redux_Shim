/*
 * Entry: 004ecdea
 * Name: Obj76_Get_Radius
 * Namespace: Global
 * Signature: float Obj76_Get_Radius(_OBJ76 * param_1, MAT_3D * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Obj76_Get_Radius(_OBJ76 *param_1,MAT_3D *param_2,float param_3)

{
  _GEOMETRY *p_Var1;
  float fVar2;
  MAT_3D *pMVar3;
  int iVar4;
  _OBJ76 *p_Var5;
  MAT_3D *pMVar6;
  int iVar7;
  MAT_3D local_90;
  MAT_3D local_50;
  VECTOR_3D local_10;
  
  p_Var5 = param_1;
  do {
    pMVar3 = Matrix_Multiply(&local_90,&p_Var5->transform,param_2);
    pMVar6 = &local_50;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      pMVar6->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
    }
    if ((p_Var5->flags & 1) == 0) {
      iVar7 = 0;
      iVar4 = GeoCache_SelectLOD(p_Var5,0);
      if ((iVar4 == 1) && (p_Var1 = p_Var5->geom, 0 < p_Var1->vertex_count)) {
        param_1 = (_OBJ76 *)0x0;
        do {
          Vector_Transform(&local_10,
                           (VECTOR_3D *)
                           ((param_1->tex_info).group + (int)(p_Var1->vertex_table + -10)),1,
                           &local_50);
          fVar2 = local_10.x * local_10.x + local_10.y * local_10.y + local_10.z * local_10.z;
          if (param_3 < fVar2) {
            param_3 = fVar2;
          }
          param_1 = (_OBJ76 *)((int)&param_1->id + 4);
          iVar7 = iVar7 + 1;
        } while (iVar7 < p_Var1->vertex_count);
      }
    }
    if (p_Var5->child != (_OBJ76 *)0x0) {
      param_3 = Obj76_Get_Radius(p_Var5->child,&local_50,param_3);
    }
    p_Var5 = p_Var5->sibling;
  } while (p_Var5 != (_OBJ76 *)0x0);
  return param_3;
}
