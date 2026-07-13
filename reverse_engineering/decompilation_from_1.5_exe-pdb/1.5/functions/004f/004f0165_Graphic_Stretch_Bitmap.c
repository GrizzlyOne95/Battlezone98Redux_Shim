/*
 * Entry: 004f0165
 * Name: Graphic_Stretch_Bitmap
 * Namespace: Global
 * Signature: void Graphic_Stretch_Bitmap(_GRAPHIC_BUFFER * param_1, _GRAPHIC_BUFFER * param_2, long param_3, long param_4, long param_5, long param_6, BITMAP_OPER param_7, long param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Graphic_Stretch_Bitmap
          (_GRAPHIC_BUFFER *param_1,_GRAPHIC_BUFFER *param_2,long param_3,long param_4,long param_5,
          long param_6,BITMAP_OPER param_7,long param_8)

{
  PANE *pPVar1;
  long lVar2;
  long lVar3;
  BITMAP_BLIT_STRUCT local_48;
  PANE local_14;
  
  lVar2 = param_4;
  lVar3 = param_3;
  if ((param_1->Bit_Depth == WORD_FORMAT) || (param_2->Bit_Depth == WORD_FORMAT)) {
    Trace("Unsupported Graphic_Stretch_Bitmap format\n");
    return;
  }
  if (param_1->Status == 0) {
    return;
  }
  if (param_2->Status == 0) {
    return;
  }
  if (param_5 < param_3) {
    param_3 = param_5;
    param_5 = lVar3;
  }
  if (param_6 < param_4) {
    param_4 = param_6;
    param_6 = lVar2;
  }
  local_48.Scale_x = 0;
  if (param_5 - param_3 != 0) {
    local_48.Scale_x =
         ((((param_2->Pane).x1 - (param_2->Pane).x0) + 1) * 0x10000) / ((param_5 - param_3) + 1);
  }
  local_48.Scale_y = 0;
  if (param_6 - param_4 != 0) {
    local_48.Scale_y =
         ((((param_2->Pane).y1 - (param_2->Pane).y0) + 1) * 0x10000) / ((param_6 - param_4) + 1);
  }
  pPVar1 = &param_1->Pane;
  local_14.x0 = param_3 + pPVar1->x0;
  local_14.y1 = (param_1->Pane).y0;
  local_14.y0 = param_4 + local_14.y1;
  local_14.x1 = pPVar1->x0 + param_5;
  local_14.y1 = local_14.y1 + param_6;
  lVar3 = Clip_Pane(&local_14,pPVar1);
  if (lVar3 < 0) {
    return;
  }
  local_48.src_x0 = (param_2->Pane).x0;
  local_48.src_y0 = (param_2->Pane).y0;
  local_48.Src_Pitch = param_2->Width;
  local_48.off_x0 = (local_14.x0 - param_3) - pPVar1->x0;
  local_48.off_y0 = (local_14.y0 - param_4) - (param_1->Pane).y0;
  local_48.Width = (local_14.x1 - local_14.x0) + 1;
  local_48.Height = (local_14.y1 - local_14.y0) + 1;
  local_48.Dst_Pitch = param_1->Width;
  local_48.Dst = (char *)(param_1->Buffer + local_14.x0 + local_48.Dst_Pitch * local_14.y0);
  local_48.Src = (char *)param_2->Buffer;
  if (param_7 == TRANSPARENT_PIXELS) {
LAB_004f02c9:
    Stretch_Transparent_Bitmap(&local_48);
  }
  else {
    if (param_7 == ONE_THIRD_TRANSLUCENT_PIXELS) {
      Stretch_Translucent_Bitmap(&local_48);
      return;
    }
    if (param_7 == TWO_THIRD_TRANSLUCENT_PIXELS) {
      Stretch_Translucent2_Bitmap(&local_48);
      return;
    }
    if (param_7 != ALPHA_PIXELS) {
      if (param_7 == UPSIDE_DOWN_TRANSPARENT_PIXELS) {
        local_48.Src = local_48.Src + (param_2->Height + -1) * local_48.Src_Pitch;
        local_48.Src_Pitch = -local_48.Src_Pitch;
        goto LAB_004f02c9;
      }
      if (param_7 != UPSIDE_DOWN_ALPHA_PIXELS) {
        Stretch_Solid_Bitmap(&local_48);
        return;
      }
      local_48.Src = local_48.Src + (param_2->Height + -1) * local_48.Src_Pitch;
      local_48.Src_Pitch = -local_48.Src_Pitch;
    }
    Stretch_Alpha_Bitmap(&local_48);
  }
  return;
}
