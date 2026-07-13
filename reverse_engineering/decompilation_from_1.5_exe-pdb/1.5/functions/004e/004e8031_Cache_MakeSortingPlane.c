/*
 * Entry: 004e8031
 * Name: Cache_MakeSortingPlane
 * Namespace: Global
 * Signature: void * Cache_MakeSortingPlane(FACE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl Cache_MakeSortingPlane(FACE *param_1)

{
  BSP_POLYGON *pBVar1;
  
  if (0x1000 < (int)Poly_Leading_Ptr + (0x30 - Poly_Base_Ptr)) {
    Add_Container(Current_Entity);
  }
  pBVar1 = Poly_Leading_Ptr;
  (Poly_Leading_Ptr->Test).y = 0.0;
  (pBVar1->Test).z = 0.0;
  *(byte *)((int)&pBVar1->Bsp_Type + 1) = 0;
  *(undefined1 *)&pBVar1->Bsp_Type = BSP_SINGLE_POLYGON;
  *(float *)pBVar1->Texture_name = (param_1->Test_Point).x;
  *(float *)(pBVar1->Texture_name + 4) = (param_1->Test_Point).y;
  *(float *)(pBVar1->Texture_name + 8) = (param_1->Test_Point).z;
  *(float *)(pBVar1->Texture_name + 0xc) = (param_1->plane).surf_normal.x;
  pBVar1->Color_Index = (long)(param_1->plane).surf_normal.y;
  pBVar1->Bitmap_Operation = (long)(param_1->plane).surf_normal.z;
  (pBVar1->Test).x = (param_1->plane).dist;
  return &pBVar1->Plane;
}
