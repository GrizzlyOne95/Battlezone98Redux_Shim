/*
 * Entry: 004fc42c
 * Name: DrawPolySprite
 * Namespace: Global
 * Signature: int DrawPolySprite(CAMERA * param_1, int param_2, VECTOR_3D * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl DrawPolySprite(CAMERA *param_1,int param_2,VECTOR_3D *param_3,int param_4)

{
  POLYGON_SKIN PVar1;
  SPRITE *pSVar2;
  POINT_3D local_64;
  float local_4c;
  float fStack_48;
  float fStack_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  float local_34;
  float fStack_30;
  float fStack_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  float fStack_18;
  float fStack_14;
  float local_10;
  float local_c;
  undefined4 local_8;
  
  if ((param_2 < 0) || (spriteTableSize <= param_2)) {
    pSVar2 = spriteTable;
  }
  else {
    pSVar2 = spriteTable + param_2;
  }
  PVar1 = (POLYGON_SKIN)pSVar2->texPtr;
  local_40 = 1.0 / (float)(int)((PVar1.Texture)->width >>
                               (2 < (PVar1.Texture)->type) + (0 < (PVar1.Texture)->type));
  local_24 = 1.0 / (float)(PVar1.Texture)->height;
  local_64.Texel.u = (float)pSVar2->u * local_40;
  local_64.Texel.v = (float)pSVar2->v * local_24;
  local_64.Vector.x = param_3->x;
  local_40 = (float)(pSVar2->width + pSVar2->u) * local_40;
  local_64.Vector.y = param_3->y;
  local_24 = (float)(pSVar2->height + pSVar2->v) * local_24;
  local_64.Vector.z = param_3->z;
  local_64.Texel.field2_0x8.luma = 1.0;
  local_4c = param_3[1].x;
  fStack_48 = param_3[1].y;
  fStack_44 = param_3[1].z;
  local_38 = 0x3f800000;
  local_34 = param_3[2].x;
  fStack_30 = param_3[2].y;
  fStack_2c = param_3[2].z;
  local_20 = 0x3f800000;
  local_1c = param_3[3].x;
  fStack_18 = param_3[3].y;
  fStack_14 = param_3[3].z;
  local_8 = 0x3f800000;
  Colored_Light_RGBA = colorTable[pSVar2->flags & 0xf];
  local_3c = local_64.Texel.v;
  local_28 = local_40;
  local_10 = local_64.Texel.u;
  local_c = local_24;
  if (useD3D == 0) {
    __Camera_Software_Draw_polygon__
              (param_1,&local_64,4,PVar1,BitmapOper2PolyType[param_4 & 7] | 0x10U);
  }
  else {
    __Camera_Hardware_Draw_polygon__
              (param_1,&local_64,4,PVar1,BitmapOper2PolyType[param_4 & 7] | 0x10U);
  }
  Colored_Light_RGBA = 0xffffff;
  return 1;
}
