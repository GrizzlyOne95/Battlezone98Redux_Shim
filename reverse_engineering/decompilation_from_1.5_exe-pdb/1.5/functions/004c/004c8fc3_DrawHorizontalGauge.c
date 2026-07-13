/*
 * Entry: 004c8fc3
 * Name: DrawHorizontalGauge
 * Namespace: Global
 * Signature: void DrawHorizontalGauge(_GRAPHIC_BUFFER * param_1, float param_2, tagRECT * param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
DrawHorizontalGauge(_GRAPHIC_BUFFER *param_1,float param_2,tagRECT *param_3,long param_4,
                   long param_5)

{
  int iVar1;
  long lVar2;
  PANE local_1c;
  double local_c;
  
  local_1c.x0 = param_3->left;
  local_1c.y0 = param_3->top;
  local_1c.x1 = param_3->right;
  local_1c.y1 = param_3->bottom;
  lVar2 = Clip_Pane(&local_1c,&param_1->Pane);
  if (-1 < lVar2) {
    iVar1 = param_3->left;
    local_c = (double)((float)((param_3->right - iVar1) + 1) * param_2 + (float)Float2Int);
    lVar2 = Clamp<long>(iVar1 + local_c._0_4_,iVar1,param_3->right);
    if (local_1c.x0 < lVar2) {
      Clipped_Rect_Filled(param_1,local_1c.x0,local_1c.y0,lVar2 + -1,local_1c.y1,param_4,
                          SOLID_PIXELS);
    }
    if (lVar2 <= local_1c.x1) {
      Clipped_Rect_Filled(param_1,lVar2,local_1c.y0,local_1c.x1,local_1c.y1,param_5,SOLID_PIXELS);
    }
  }
  return;
}
