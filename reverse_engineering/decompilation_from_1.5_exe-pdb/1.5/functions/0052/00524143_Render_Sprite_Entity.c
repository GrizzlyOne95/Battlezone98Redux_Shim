/*
 * Entry: 00524143
 * Name: Render_Sprite_Entity
 * Namespace: Global
 * Signature: void Render_Sprite_Entity(_ZSORTING * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Sprite_Entity(_ZSORTING *param_1,CAMERA *param_2)

{
  _ZSORTING *p_Var1;
  POLYGON_SKIN PVar2;
  float fVar3;
  float fVar4;
  _GRAPHIC_BUFFER *p_Var5;
  float fVar6;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int extraout_EAX_03;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  long lVar11;
  int local_24;
  int local_1c;
  double local_14;
  int local_c;
  
  p_Var1 = param_1 + 1;
  if (useD3D == 0) {
    fVar3 = (float)(int)LODInfo.spriteRangeOff;
    if ((int)LODInfo.spriteRangeOff < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    if ((float)param_1[1].Bitmap_Operation <= fVar3) {
      return;
    }
    fVar3 = (float)(int)LODInfo.spriteRadiusOff;
    if ((int)LODInfo.spriteRadiusOff < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    if (fVar3 < (float)param_1[1].Type != (fVar3 == (float)param_1[1].Type)) {
      return;
    }
    fVar3 = (float)(int)LODInfo.spriteRangeSolid;
    if ((int)LODInfo.spriteRangeSolid < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    if (fVar3 < (float)param_1[1].Bitmap_Operation == (fVar3 == (float)param_1[1].Bitmap_Operation))
    {
      fVar3 = (float)(int)LODInfo.spriteRadiusSolid;
      if ((int)LODInfo.spriteRadiusSolid < 0) {
        fVar3 = fVar3 + 4.2949673e+09;
      }
      if (fVar3 < (float)param_1[1].Type) goto LAB_00524312;
    }
    PVar2 = param_1[1].Skin_Color;
    iVar7 = (param_1->Skin_Color).Color;
    p_Var5 = param_2->Buffer;
    fVar4 = (float)param_1[1].Type * 0.5;
    fVar3 = (float)p_Var1->vcnt + fVar4;
    fVar4 = (float)param_1[1].Skin_Color + fVar4;
    if (param_2->Left <= (float)p_Var1->vcnt) {
      fVar6 = (float)Float2Int + (float)p_Var1->vcnt;
    }
    else {
      fVar6 = param_2->Left + (float)Float2Int;
    }
    local_14 = (double)fVar6;
    fVar6 = (float)Float2Int;
    if (param_2->Right < (float)p_Var1->vcnt) {
      fVar3 = param_2->Right;
    }
    if ((float)PVar2 < param_2->Bottom) {
      PVar2 = (POLYGON_SKIN)param_2->Bottom;
    }
    if (param_2->Top < fVar4) {
      fVar4 = param_2->Top;
    }
    local_24 = SUB84((double)(fVar3 + fVar6),0);
    if (local_24 != local_14._0_4_ && -1 < local_24 - local_14._0_4_) {
      local_1c = SUB84((double)(fVar6 + fVar4),0);
      local_c = SUB84((double)((float)PVar2 + fVar6),0);
      if (local_1c != local_c && -1 < local_1c - local_c) {
        Graphic_Rect_Filled(p_Var5,local_14._0_4_,local_c,local_24,local_1c,
                            (uint)Headlight_Mask_Luma
                                  [*(byte *)((int)&spriteTable[iVar7].texPtr[1].width +
                                            (spriteTable[iVar7].height / 2 + spriteTable[iVar7].v) *
                                            (int)(spriteTable[iVar7].texPtr)->width +
                                            spriteTable[iVar7].width / 2 + spriteTable[iVar7].u)]
                                  [p_Var5->Buffer
                                   [local_14._0_4_ +
                                    ((p_Var5->Pane).y0 + local_c) * p_Var5->Width +
                                    (p_Var5->Pane).x0]],SOLID_PIXELS);
      }
    }
  }
  else {
LAB_00524312:
    lVar11 = param_1->Bitmap_Operation;
    _ftol2_sse();
    iVar10 = extraout_EAX;
    _ftol2_sse();
    iVar9 = extraout_EAX_00;
    _ftol2_sse();
    iVar8 = extraout_EAX_01;
    _ftol2_sse();
    iVar7 = extraout_EAX_02;
    _ftol2_sse();
    DrawScaledSprite(param_2,(param_1->Skin_Color).Color,extraout_EAX_03,iVar7,iVar8,iVar9,iVar10,
                     lVar11);
  }
  return;
}
