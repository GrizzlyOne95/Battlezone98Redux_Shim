/*
 * Entry: 004fbe30
 * Name: DrawSprite
 * Namespace: Global
 * Signature: int DrawSprite(_GRAPHIC_BUFFER * param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl DrawSprite(_GRAPHIC_BUFFER *param_1,int param_2,int param_3,int param_4,int param_5)

{
  TEXTURE *pTVar1;
  POLYGON_SKIN PVar2;
  float fVar3;
  _GRAPHIC_BUFFER *p_Var4;
  int iVar5;
  SPRITE *pSVar6;
  _GRAPHIC_BUFFER *p_Var7;
  _GRAPHIC_BUFFER local_e4;
  _GRAPHIC_BUFFER local_b0;
  POINT_3D local_7c;
  float local_64;
  float local_60;
  float local_5c;
  _GRAPHIC_BUFFER *local_58;
  float local_54;
  TEXEL_u_8 local_50;
  float local_4c;
  float local_48;
  float local_44;
  _GRAPHIC_BUFFER *local_40;
  float local_3c;
  TEXEL_u_8 local_38;
  float local_34;
  float local_30;
  float local_2c;
  int local_28;
  float local_24;
  TEXEL_u_8 local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  if ((param_2 < 0) || (spriteTableSize <= param_2)) {
    pSVar6 = spriteTable;
  }
  else {
    pSVar6 = spriteTable + param_2;
  }
  local_c = (float)pSVar6->width;
  if ((param_5 & 0x10000U) == 0) {
    if ((param_5 & 0x20000U) != 0) {
      param_3 = param_3 - (int)local_c;
    }
  }
  else {
    param_3 = param_3 - ((int)local_c >> 1);
  }
  local_8 = (float)pSVar6->height;
  if ((param_5 & 0x40000U) == 0) {
    fVar3 = local_8;
    if ((param_5 & 0x80000U) == 0) goto LAB_004fbe9f;
  }
  else {
    fVar3 = (float)((int)local_8 >> 1);
  }
  param_4 = param_4 - (int)fVar3;
LAB_004fbe9f:
  if (((VIDEO_DEVICE *)param_1 == &Device) && (useD3D != 0)) {
    PVar2 = (POLYGON_SKIN)pSVar6->texPtr;
    fVar3 = 1.0 / (float)(int)((PVar2.Texture)->width >>
                              (2 < (PVar2.Texture)->type) + (0 < (PVar2.Texture)->type));
    local_10 = 1.0 / (float)(PVar2.Texture)->height;
    param_2 = (int)((float)pSVar6->u * fVar3);
    local_18 = (float)pSVar6->v * local_10;
    param_1 = (_GRAPHIC_BUFFER *)((float)(pSVar6->u + (int)local_c) * fVar3);
    local_10 = local_10 * (float)(pSVar6->v + (int)local_8);
    if ((param_5 & 0x200000U) != 0) {
      param_3 = param_3 + Device.Viewport.Pane.x0;
      param_4 = param_4 + Device.Viewport.Pane.y0;
      iVar5 = ClipSprite(Device.Viewport.Pane.x0,Device.Viewport.Pane.y0,Device.Viewport.Pane.x1,
                         Device.Viewport.Pane.y1,&param_3,&param_4,(int *)&local_c,(int *)&local_8,
                         (float *)&param_2,&local_18,(float *)&param_1,&local_10);
      if (iVar5 == 0) {
        return 0;
      }
    }
    local_14 = (float)param_3;
    local_1c = (float)param_4;
    local_c = (float)(int)local_c + local_14;
    local_8 = (float)(int)local_8 + local_1c;
    ClampZ();
    iVar5 = param_2;
    local_7c.Texel.field2_0x8.luma = 1.0;
    local_7c.Vector.z = 1.0 / spriteZ;
    if ((param_5 & 0x100000U) != 0) {
      param_2 = (int)param_1;
      param_1 = (_GRAPHIC_BUFFER *)iVar5;
    }
    local_7c.Vector.x = local_14;
    local_7c.Vector.y = local_1c;
    Colored_Light_RGBA = colorTable[pSVar6->flags & 0xf];
    local_7c.Texel.u = (float)param_2;
    local_7c.Texel.v = local_18;
    local_64 = local_c;
    local_60 = local_1c;
    local_58 = param_1;
    local_54 = local_18;
    local_4c = local_c;
    local_48 = local_8;
    local_40 = param_1;
    local_3c = local_10;
    local_34 = local_14;
    local_30 = local_8;
    local_28 = param_2;
    local_24 = local_10;
    local_5c = local_7c.Vector.z;
    local_50.luma = local_7c.Texel.field2_0x8.luma;
    local_44 = local_7c.Vector.z;
    local_38.luma = local_7c.Texel.field2_0x8.luma;
    local_2c = local_7c.Vector.z;
    local_20.luma = local_7c.Texel.field2_0x8.luma;
    Draw_D3D_Poly(&local_7c,4,PVar2,BitmapOper2PolyTypeD3D[param_5 & 7]);
    Colored_Light_RGBA = 0xffffff;
  }
  else {
    pTVar1 = pSVar6->texPtr;
    p_Var4 = Graphic_Buffer_Init_Ex
                       (&local_e4,(int)pTVar1->width,pTVar1->height,(char *)(pTVar1 + 1),
                        BYTES_FORMAT);
    local_b0.Pane.x0 = pSVar6->u;
    local_b0.Pane.y0 = pSVar6->v;
    p_Var7 = &local_b0;
    for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
      p_Var7->Width = p_Var4->Width;
      p_Var4 = (_GRAPHIC_BUFFER *)&p_Var4->Height;
      p_Var7 = (_GRAPHIC_BUFFER *)&p_Var7->Height;
    }
    local_b0.Pane.x1 = local_b0.Pane.x0 + -1 + (int)local_c;
    local_b0.Pane.y1 = local_b0.Pane.y0 + -1 + (int)local_8;
    Graphic_Copy_Bitmap(param_1,&local_b0,param_3,param_4,param_5 & UPSIDE_DOWN_ALPHA_PIXELS);
  }
  return 1;
}
