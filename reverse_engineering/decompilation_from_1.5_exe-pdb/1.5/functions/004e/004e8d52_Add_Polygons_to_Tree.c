/*
 * Entry: 004e8d52
 * Name: Add_Polygons_to_Tree
 * Namespace: Global
 * Signature: void Add_Polygons_to_Tree(_OBJ76 * param_1, MAT_3D * param_2, CAMERA * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Add_Polygons_to_Tree(_OBJ76 *param_1,MAT_3D *param_2,CAMERA *param_3)

{
  _GEOMETRY *p_Var1;
  FACE *pFVar2;
  MAT_3D *pMVar3;
  BSP_POLYGON *pBVar4;
  int iVar5;
  int in_EDX;
  BSP_POLYGON *unaff_EDI;
  MAT_3D *pMVar6;
  _GEOMETRY *p_Var7;
  MAT_3D local_cc;
  MAT_3D local_8c;
  MAT_3D local_4c;
  FACE *local_c;
  MAT_3D *local_8;
  
  p_Var1 = param_1->geom;
  local_c = p_Var1->faces;
  if (local_c != (FACE *)0x0) {
    local_8 = (MAT_3D *)(Vertex_Table + p_Var1->vertex_count);
    if ((param_1->flags & 0x40) == 0) {
      pMVar3 = &local_cc;
      pMVar6 = param_2;
    }
    else {
      Rot_Mat.posit_x = param_2->posit_x;
      Rot_Mat.posit_y = param_2->posit_y;
      Rot_Mat.posit_z = param_2->posit_z;
      pMVar3 = &local_8c;
      pMVar6 = &Rot_Mat;
    }
    pMVar3 = Matrix_Multiply(pMVar3,pMVar6,(MAT_3D *)(in_EDX + 0x40));
    pMVar6 = &local_4c;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      pMVar6->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
    }
    pMVar3 = (MAT_3D *)p_Var1->vertex_table;
    p_Var7 = (_GEOMETRY *)Vertex_Table;
    Vector_Transform(Vertex_Table,(VECTOR_3D *)pMVar3,p_Var1->vertex_count,&local_4c);
    Apply_Simple_Light_Model(Vertex_Table,&param_2->right_x,p_Var7,pMVar3);
    do {
      pFVar2 = local_c;
      if ((2 < local_c->vertex_count) &&
         (pBVar4 = Make_Poly(param_1,(FACE *)&local_4c,local_8,(float *)unaff_EDI),
         pBVar4 != (BSP_POLYGON *)0x0)) {
        if (Root_Polygon == (BSP_POLYGON *)0x0) {
          Root_Polygon = Poly_Leading_Ptr;
          Poly_Leading_Ptr = pBVar4;
        }
        else {
          Polygon_To_Poly_List(unaff_EDI);
          Poly_Leading_Ptr = pBVar4;
        }
      }
      local_c = pFVar2->front_facet;
    } while (local_c != (FACE *)0x0);
  }
  return;
}
