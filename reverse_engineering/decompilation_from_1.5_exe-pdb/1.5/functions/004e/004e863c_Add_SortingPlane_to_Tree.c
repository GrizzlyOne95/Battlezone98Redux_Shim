/*
 * Entry: 004e863c
 * Name: Add_SortingPlane_to_Tree
 * Namespace: Global
 * Signature: void Add_SortingPlane_to_Tree(_OBJ76 * param_1, MAT_3D * param_2, CAMERA * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Add_SortingPlane_to_Tree(_OBJ76 *param_1,MAT_3D *param_2,CAMERA *param_3)

{
  PLANE *pPVar1;
  BSP_POLYGON *pBVar2;
  int in_EAX;
  MAT_3D *pMVar3;
  int iVar4;
  int iVar5;
  BSP_POLYGON *unaff_EDI;
  MAT_3D *pMVar6;
  MAT_3D local_84;
  MAT_3D local_44;
  
  iVar5 = *(int *)(*(int *)(in_EAX + 100) + 0x14);
  if (iVar5 != 0) {
    pMVar3 = Matrix_Multiply(&local_84,(MAT_3D *)param_1,param_2 + 1);
    pMVar6 = &local_44;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      pMVar6->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
    }
    do {
      pBVar2 = Poly_Leading_Ptr;
      (Poly_Leading_Ptr->Test).y = 0.0;
      (pBVar2->Test).z = 0.0;
      *(byte *)((int)&pBVar2->Bsp_Type + 1) = 0;
      Vector_Transform((VECTOR_3D *)pBVar2->Texture_name,(VECTOR_3D *)(iVar5 + 0x34),1,&local_44);
      Transform_Plane((PLANE *)(Poly_Leading_Ptr->Texture_name + 0xc),(PLANE *)(iVar5 + 0xc),
                      &local_44);
      pBVar2 = Poly_Leading_Ptr;
      *(byte *)((int)&Poly_Leading_Ptr->Bsp_Type + 1) = 0;
      pPVar1 = &pBVar2->Plane;
      if (Root_Polygon == (BSP_POLYGON *)0x0) {
        Root_Polygon = pBVar2;
      }
      else {
        Polygon_To_Poly_List(unaff_EDI);
      }
      iVar5 = *(int *)(iVar5 + 0x30);
      Poly_Leading_Ptr = (BSP_POLYGON *)pPVar1;
    } while (iVar5 != 0);
  }
  return;
}
