/*
 * Entry: 004777a9
 * Name: Draw_Moon_Sun
 * Namespace: Global
 * Signature: void Draw_Moon_Sun(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Draw_Moon_Sun(CAMERA *param_1)

{
  float fVar1;
  VECTOR_3D *pVVar2;
  float *unaff_EBX;
  undefined1 local_20 [12];
  float local_14;
  double local_10;
  float local_8;
  
  local_8 = spriteZ;
  if (SunIndex != 0) {
    pVVar2 = Vector_Rotate((VECTOR_3D *)local_20,&Sun_Light,(MAT_3D *)(unaff_EBX + 0x10));
    local_14 = pVVar2->x;
    if (unaff_EBX[0x42] <= pVVar2->z) {
      fVar1 = 1.0 / pVVar2->z;
      local_20._4_8_ = (undefined8)(unaff_EBX[2] * local_14 * fVar1 + *unaff_EBX + (float)Float2Int)
      ;
      local_10 = (double)(unaff_EBX[3] * pVVar2->y * fVar1 + unaff_EBX[1] + (float)Float2Int);
      spriteZ = TerrainVisibilityRange;
      DrawSprite((_GRAPHIC_BUFFER *)unaff_EBX[0xe],SunIndex,local_20._4_4_,local_10._0_4_,0x250004);
      spriteZ = local_8;
    }
  }
  return;
}
