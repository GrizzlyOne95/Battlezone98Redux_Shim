/*
 * Entry: 004e8503
 * Name: MakeSortingPlane
 * Namespace: Global
 * Signature: void * MakeSortingPlane(FACE * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl MakeSortingPlane(FACE *param_1,MAT_3D *param_2)

{
  BSP_POLYGON *pBVar1;
  int in_EAX;
  
  pBVar1 = Poly_Leading_Ptr;
  (Poly_Leading_Ptr->Test).y = 0.0;
  (pBVar1->Test).z = 0.0;
  *(byte *)((int)&pBVar1->Bsp_Type + 1) = 0;
  Vector_Transform((VECTOR_3D *)pBVar1->Texture_name,(VECTOR_3D *)(in_EAX + 0x34),1,
                   (MAT_3D *)param_1);
  Transform_Plane((PLANE *)(Poly_Leading_Ptr->Texture_name + 0xc),(PLANE *)(in_EAX + 0xc),
                  (MAT_3D *)param_1);
  pBVar1 = Poly_Leading_Ptr;
  *(byte *)((int)&Poly_Leading_Ptr->Bsp_Type + 1) = 0;
  return &pBVar1->Plane;
}
