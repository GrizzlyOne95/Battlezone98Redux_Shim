/*
 * Entry: 00540acd
 * Name: Clipped_HW_Rect_Filled
 * Namespace: Global
 * Signature: void Clipped_HW_Rect_Filled(_GRAPHIC_BUFFER * param_1, long param_2, long param_3, long param_4, long param_5, long param_6, BITMAP_OPER param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Clipped_HW_Rect_Filled
          (_GRAPHIC_BUFFER *param_1,long param_2,long param_3,long param_4,long param_5,long param_6
          ,BITMAP_OPER param_7)

{
  int unaff_ESI;
  POINT_3D local_304;
  float local_2ec;
  float local_2e8;
  float local_2e4;
  TEXEL_u_8 local_2d8;
  float local_2d4;
  float local_2d0;
  float local_2cc;
  TEXEL_u_8 local_2c0;
  float local_2bc;
  float local_2b8;
  float local_2b4;
  TEXEL_u_8 local_2a8;
  
  ClampZ();
  local_304.Texel.field2_0x8.luma = 1.0;
  local_304.Vector.z = 1.0 / spriteZ;
  if (param_4 < (param_1->Pane).x1) {
    param_4 = param_4 + 1;
  }
  if (param_5 < (param_1->Pane).y1) {
    param_5 = param_5 + 1;
  }
  local_304.Vector.x = (float)param_2;
  local_304.Vector.y = (float)param_3;
  local_2ec = (float)param_4;
  local_2d0 = (float)param_5;
  local_2e8 = local_304.Vector.y;
  local_2e4 = local_304.Vector.z;
  local_2d8.luma = local_304.Texel.field2_0x8.luma;
  local_2d4 = local_2ec;
  local_2cc = local_304.Vector.z;
  local_2c0.luma = local_304.Texel.field2_0x8.luma;
  local_2bc = local_304.Vector.x;
  local_2b8 = local_2d0;
  local_2b4 = local_304.Vector.z;
  local_2a8.luma = local_304.Texel.field2_0x8.luma;
  Set_Rounding(unaff_ESI);
  if (((byte)param_7 & 7) < 2) {
    D3D_Flat_Polygon(&local_304,4,(POLYGON_SKIN)param_6);
  }
  else {
    D3D_Alpha_Blend_Polygon(&local_304,4,(POLYGON_SKIN)param_6);
  }
  Set_Rounding(unaff_ESI);
  return;
}
