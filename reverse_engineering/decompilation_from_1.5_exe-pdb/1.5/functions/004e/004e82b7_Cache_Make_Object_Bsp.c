/*
 * Entry: 004e82b7
 * Name: Cache_Make_Object_Bsp
 * Namespace: Global
 * Signature: void * Cache_Make_Object_Bsp(_OBJ76 * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl Cache_Make_Object_Bsp(_OBJ76 *param_1,MAT_3D *param_2)

{
  BSP_POLYGON *pBVar1;
  MAT_3D *pMVar2;
  int iVar3;
  MAT_3D *pMVar4;
  PLANE *pPVar5;
  MAT_3D local_84;
  MAT_3D local_44;
  
  if (0x1000 < (int)Poly_Leading_Ptr + (0x120 - Poly_Base_Ptr)) {
    Add_Container(Current_Entity);
  }
  pBVar1 = Poly_Leading_Ptr;
  (Poly_Leading_Ptr->Test).y = 0.0;
  (pBVar1->Test).z = 0.0;
  pBVar1->Texture_name[0] = '\0';
  pBVar1->Texture_name[1] = '\0';
  pBVar1->Texture_name[2] = '\0';
  pBVar1->Texture_name[3] = '\0';
  pBVar1->Texture_name[4] = '\0';
  pBVar1->Texture_name[5] = '\0';
  pBVar1->Texture_name[6] = '\0';
  pBVar1->Texture_name[7] = '\0';
  pBVar1->Texture_name[8] = '\0';
  pBVar1->Texture_name[9] = '\0';
  pBVar1->Texture_name[10] = '\0';
  pBVar1->Texture_name[0xb] = '\0';
  pBVar1->Texture_name[0xc] = '\0';
  pBVar1->Texture_name[0xd] = '\0';
  pBVar1->Texture_name[0xe] = '\0';
  pBVar1->Texture_name[0xf] = '\0';
  pBVar1->Color_Index = 0;
  pBVar1->Bitmap_Operation = 0;
  (pBVar1->Test).x = 0.0;
  *(undefined1 *)&pBVar1->Bsp_Type = BSP_I76_OBJ;
  pBVar1->Count = (long)param_1;
  pMVar2 = Matrix_Multiply(&local_84,&param_1->transform,param_2);
  pMVar4 = &local_44;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar4->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  Vector_Transform((VECTOR_3D *)Poly_Leading_Ptr->Texture_name,&(param_1->bSphere).origin,1,
                   &local_44);
  pBVar1 = Poly_Leading_Ptr;
  pPVar5 = &Poly_Leading_Ptr->Plane;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    (pPVar5->surf_normal).x = param_2->right_x;
    param_2 = (MAT_3D *)&param_2->right_y;
    pPVar5 = (PLANE *)&(pPVar5->surf_normal).y;
  }
  return &pBVar1[1].Test.y;
}
