/*
 * Entry: 004e8551
 * Name: Make_Poly
 * Namespace: Global
 * Signature: void * Make_Poly(_OBJ76 * param_1, FACE * param_2, MAT_3D * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl Make_Poly(_OBJ76 *param_1,FACE *param_2,MAT_3D *param_3,float *param_4)

{
  byte bVar1;
  VECTOR_3D *pVVar2;
  BSP_POLYGON *pBVar3;
  int in_EAX;
  PLANE *pPVar4;
  int iVar5;
  int *piVar6;
  VECTOR_3D *pVVar7;
  
  Transform_Plane((PLANE *)(Poly_Leading_Ptr->Texture_name + 0xc),(PLANE *)(in_EAX + 0xc),
                  (MAT_3D *)param_2);
  if (0.0 < (Poly_Leading_Ptr->Test).x) {
    return (void *)0x0;
  }
  Vector_Transform((VECTOR_3D *)Poly_Leading_Ptr->Texture_name,(VECTOR_3D *)(in_EAX + 0x34),1,
                   (MAT_3D *)param_2);
  pBVar3 = Poly_Leading_Ptr;
  Poly_Leading_Ptr->Count = (long)param_1;
  (pBVar3->Test).y = 0.0;
  (pBVar3->Test).z = 0.0;
  *(byte *)((int)&pBVar3->Bsp_Type + 1) = 0;
  *(undefined1 *)&pBVar3->Bsp_Type = BSP_SINGLE_POLYGON;
  pBVar3->Obj76 = (_OBJ76 *)(-(uint)(*(char *)(in_EAX + 0x20U) != '\0') & in_EAX + 0x20U);
  *(byte *)((int)&pBVar3->Bsp_Type + 2) = *(byte *)(in_EAX + 8);
  if (*(char *)(in_EAX + 0x1c) == '\0') {
    *(undefined1 *)(in_EAX + 0x1c) = 4;
  }
  bVar1 = sniped_by[((uint)*(byte *)(in_EAX + 0x1d) + (uint)*(byte *)(in_EAX + 0x1c) * 8) * 4 + 0xf8
                   ];
  *(byte *)((int)&pBVar3->Bsp_Type + 3) = bVar1;
  if (*(char *)(in_EAX + 0x1e) != '\0') {
    *(byte *)((int)&pBVar3->Bsp_Type + 3) = bVar1 | 0x80;
  }
  *(byte *)((int)&pBVar3->Bsp_Type + 1) = *(byte *)(in_EAX + 4);
  pPVar4 = &pBVar3->Plane;
  piVar6 = (int *)(in_EAX + 0x40);
  for (iVar5 = *(int *)(in_EAX + 4); 0 < iVar5; iVar5 = iVar5 + -1) {
    pPVar4->dist = (float)piVar6[2];
    *(BSP_POLYGON **)(pPVar4 + 1) = (BSP_POLYGON *)piVar6[3];
    *(BSP_POLYGON **)((int)(pPVar4 + 1) + 4) = (BSP_POLYGON *)(&param_3->right_x)[piVar6[1]];
    pVVar7 = Vertex_Table + *piVar6;
    (pPVar4->surf_normal).x = pVVar7->x;
    pVVar2 = &pPVar4->surf_normal;
    (pPVar4->surf_normal).y = pVVar7->y;
    pPVar4 = (PLANE *)((int)(pPVar4 + 1) + 8);
    pVVar2->z = pVVar7->z;
    piVar6 = piVar6 + 4;
  }
  return pPVar4;
}
