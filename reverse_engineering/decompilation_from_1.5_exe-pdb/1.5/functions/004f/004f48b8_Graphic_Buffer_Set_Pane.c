/*
 * Entry: 004f48b8
 * Name: Graphic_Buffer_Set_Pane
 * Namespace: Global
 * Signature: long Graphic_Buffer_Set_Pane(_GRAPHIC_BUFFER * param_1, long param_2, long param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
Graphic_Buffer_Set_Pane
          (_GRAPHIC_BUFFER *param_1,long param_2,long param_3,long param_4,long param_5)

{
  long lVar1;
  PANE local_24;
  PANE local_14;
  
  local_14.x1 = param_4;
  if (param_4 < param_2) {
    local_14.x1 = param_2;
    param_2 = param_4;
  }
  local_14.y1 = param_5;
  if (param_5 < param_3) {
    local_14.y1 = param_3;
    param_3 = param_5;
  }
  local_24.x0 = 0;
  local_24.y0 = 0;
  local_24.x1 = param_1->Width + -1;
  local_24.y1 = param_1->Height + -1;
  local_14.x0 = param_2;
  local_14.y0 = param_3;
  lVar1 = Clip_Pane(&local_14,&local_24);
  if (-1 < lVar1) {
    (param_1->Pane).x0 = local_14.x0;
    (param_1->Pane).y0 = local_14.y0;
    (param_1->Pane).x1 = local_14.x1;
    (param_1->Pane).y1 = local_14.y1;
  }
  return lVar1;
}
