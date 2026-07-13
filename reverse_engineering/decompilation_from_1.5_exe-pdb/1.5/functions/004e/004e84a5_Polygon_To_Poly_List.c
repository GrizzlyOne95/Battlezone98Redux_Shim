/*
 * Entry: 004e84a5
 * Name: Polygon_To_Poly_List
 * Namespace: Global
 * Signature: void Polygon_To_Poly_List(BSP_POLYGON * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Polygon_To_Poly_List(BSP_POLYGON *param_1)

{
  BSP_POLYGON *pBVar1;
  BSP_POLYGON *pBVar2;
  float in_EDX;
  
  pBVar1 = Root_Polygon;
  if (((byte)D3IniFlags & 1) != 0) {
    *(float *)((int)in_EDX + 0x28) = (Root_Polygon->Test).y;
    (pBVar1->Test).y = in_EDX;
    return;
  }
  do {
    while (pBVar2 = pBVar1,
          (float)pBVar2->Bitmap_Operation * *(float *)((int)in_EDX + 0x14) +
          *(float *)(pBVar2->Texture_name + 0xc) * *(float *)((int)in_EDX + 0xc) +
          (float)pBVar2->Color_Index * *(float *)((int)in_EDX + 0x10) + (pBVar2->Test).x < 0.0) {
      pBVar1 = (BSP_POLYGON *)(pBVar2->Test).z;
      if (pBVar1 == (BSP_POLYGON *)0x0) {
        (pBVar2->Test).z = in_EDX;
        return;
      }
    }
    pBVar1 = (BSP_POLYGON *)(pBVar2->Test).y;
  } while (pBVar1 != (BSP_POLYGON *)0x0);
  (pBVar2->Test).y = in_EDX;
  return;
}
