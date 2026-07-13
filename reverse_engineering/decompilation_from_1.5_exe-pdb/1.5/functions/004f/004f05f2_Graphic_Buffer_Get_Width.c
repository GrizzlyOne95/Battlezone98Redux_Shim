/*
 * Entry: 004f05f2
 * Name: Graphic_Buffer_Get_Width
 * Namespace: Global
 * Signature: long Graphic_Buffer_Get_Width(_GRAPHIC_BUFFER * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Graphic_Buffer_Get_Width(_GRAPHIC_BUFFER *param_1)

{
  return ((param_1->Pane).x1 - (param_1->Pane).x0) + 1;
}
