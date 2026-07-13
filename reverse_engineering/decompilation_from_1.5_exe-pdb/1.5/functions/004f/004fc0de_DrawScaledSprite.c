/*
 * Entry: 004fc0de
 * Name: DrawScaledSprite
 * Namespace: Global
 * Signature: int DrawScaledSprite(CAMERA * param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
DrawScaledSprite(CAMERA *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                int param_7,int param_8)

{
  TEXTURE *pTVar1;
  POLYGON_SKIN PVar2;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar3;
  _GRAPHIC_BUFFER *p_Var4;
  int extraout_EAX_03;
  int extraout_EAX_04;
  int extraout_EAX_05;
  int extraout_EAX_06;
  SPRITE *pSVar5;
  _GRAPHIC_BUFFER *p_Var6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int *piVar10;
  int *piVar11;
  int *piVar12;
  CAMERA **ppCVar13;
  float *pfVar14;
  float *pfVar15;
  float *pfVar16;
  _GRAPHIC_BUFFER local_e0;
  _GRAPHIC_BUFFER local_ac;
  POINT_3D local_78;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  CAMERA *local_50;
  undefined4 local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  undefined4 local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_1c;
  int local_18;
  VIDEO_DEVICE *local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_14 = (VIDEO_DEVICE *)param_1->Buffer;
  if (((param_6 < 1) || (param_7 < 1)) || (param_5 < 1)) {
LAB_004fc422:
    iVar3 = 0;
  }
  else {
    if ((param_2 < 0) || (spriteTableSize <= param_2)) {
      pSVar5 = spriteTable;
    }
    else {
      pSVar5 = spriteTable + param_2;
    }
    if ((param_8 & 0x10000U) == 0) {
      iVar3 = param_6;
      if ((param_8 & 0x20000U) != 0) goto LAB_004fc152;
    }
    else {
      iVar3 = param_6 >> 1;
LAB_004fc152:
      param_3 = param_3 + (1 - iVar3);
    }
    local_18 = pSVar5->height;
    if ((param_8 & 0x40000U) == 0) {
      iVar3 = param_7;
      if ((param_8 & 0x80000U) != 0) goto LAB_004fc176;
    }
    else {
      iVar3 = param_7 >> 1;
LAB_004fc176:
      param_4 = param_4 + (1 - iVar3);
    }
    if ((local_14 == &Device) && (useD3D != 0)) {
      PVar2 = (POLYGON_SKIN)pSVar5->texPtr;
      local_14 = (VIDEO_DEVICE *)(pSVar5->u + pSVar5->width);
      local_c = 1.0 / (float)(int)((PVar2.Texture)->width >>
                                  (2 < (PVar2.Texture)->type) + (0 < (PVar2.Texture)->type));
      local_10 = 1.0 / (float)(PVar2.Texture)->height;
      local_18 = pSVar5->v + local_18;
      pfVar16 = &local_10;
      local_8 = (float)pSVar5->u * local_c;
      pfVar15 = &local_c;
      ppCVar13 = &param_1;
      pfVar14 = &local_8;
      param_1 = (CAMERA *)((float)pSVar5->v * local_10);
      piVar12 = &param_7;
      piVar11 = &param_6;
      piVar10 = &param_4;
      local_c = (float)(int)local_14 * local_c;
      piVar9 = &param_3;
      local_10 = local_10 * (float)local_18;
      _ftol2_sse();
      iVar8 = extraout_EAX_03;
      _ftol2_sse();
      iVar7 = extraout_EAX_04;
      _ftol2_sse();
      iVar3 = extraout_EAX_05;
      _ftol2_sse();
      iVar3 = ClipSprite(extraout_EAX_06,iVar3,iVar7,iVar8,piVar9,piVar10,piVar11,piVar12,pfVar14,
                         (float *)ppCVar13,pfVar15,pfVar16);
      if (iVar3 == 0) goto LAB_004fc422;
      local_78.Vector.x = (float)param_3;
      local_78.Vector.y = (float)param_4;
      Colored_Light_RGBA = colorTable[pSVar5->flags & 0xf];
      local_78.Vector.z = 1.0 / (float)param_5;
      local_60 = ((float)param_6 + local_78.Vector.x) - 1.0;
      local_44 = ((float)param_7 + local_78.Vector.y) - 1.0;
      local_78.Texel.u = local_8;
      local_78.Texel.v = (float)param_1;
      local_78.Texel.field2_0x8.luma = 1.0;
      local_54 = local_c;
      local_50 = param_1;
      local_4c = 0x3f800000;
      local_3c = local_c;
      local_38 = local_10;
      local_34 = 0x3f800000;
      local_24 = local_8;
      local_20 = local_10;
      local_1c = 0x3f800000;
      local_5c = local_78.Vector.y;
      local_58 = local_78.Vector.z;
      local_48 = local_60;
      local_40 = local_78.Vector.z;
      local_30 = local_78.Vector.x;
      local_2c = local_44;
      local_28 = local_78.Vector.z;
      Draw_D3D_Poly(&local_78,4,PVar2,BitmapOper2PolyTypeD3D[param_8 & 7]);
      Colored_Light_RGBA = 0xffffff;
    }
    else {
      param_1 = (CAMERA *)(float)pSVar5->u;
      pfVar16 = &local_c;
      pfVar15 = &local_8;
      local_10 = (float)pSVar5->v;
      pfVar14 = &local_10;
      ppCVar13 = &param_1;
      piVar12 = &param_7;
      piVar11 = &param_6;
      piVar10 = &param_4;
      local_8 = ((float)pSVar5->width + (float)param_1) - 1.0;
      piVar9 = &param_3;
      local_c = (local_10 + (float)local_18) - 1.0;
      _ftol2_sse();
      iVar8 = extraout_EAX;
      _ftol2_sse();
      iVar7 = extraout_EAX_00;
      _ftol2_sse();
      iVar3 = extraout_EAX_01;
      _ftol2_sse();
      iVar3 = ClipSprite(extraout_EAX_02,iVar3,iVar7,iVar8,piVar9,piVar10,piVar11,piVar12,
                         (float *)ppCVar13,pfVar14,pfVar15,pfVar16);
      if (iVar3 == 0) goto LAB_004fc422;
      pTVar1 = pSVar5->texPtr;
      p_Var4 = Graphic_Buffer_Init_Ex
                         (&local_e0,(int)pTVar1->width,pTVar1->height,(char *)(pTVar1 + 1),
                          BYTES_FORMAT);
      p_Var6 = &local_ac;
      for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
        p_Var6->Width = p_Var4->Width;
        p_Var4 = (_GRAPHIC_BUFFER *)&p_Var4->Height;
        p_Var6 = (_GRAPHIC_BUFFER *)&p_Var6->Height;
      }
      _ftol2_sse();
      _ftol2_sse();
      _ftol2_sse();
      _ftol2_sse();
      Graphic_Stretch_Bitmap
                (&local_14->Viewport,&local_ac,param_3,param_4,param_3 + -1 + param_6,
                 param_4 + -1 + param_7,param_8 & UPSIDE_DOWN_ALPHA_PIXELS,0);
    }
    iVar3 = 1;
  }
  return iVar3;
}
