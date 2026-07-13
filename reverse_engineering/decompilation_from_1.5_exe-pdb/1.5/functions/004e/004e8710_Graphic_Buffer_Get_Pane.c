/*
 * Entry: 004e8710
 * Name: Graphic_Buffer_Get_Pane
 * Namespace: Global
 * Signature: PANE * Graphic_Buffer_Get_Pane(PANE * __return_storage_ptr__, _GRAPHIC_BUFFER * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PANE * __cdecl Graphic_Buffer_Get_Pane(PANE *__return_storage_ptr__,_GRAPHIC_BUFFER *param_1)

{
  __return_storage_ptr__->x0 = (param_1->Pane).x0;
  __return_storage_ptr__->y0 = (param_1->Pane).y0;
  __return_storage_ptr__->x1 = (param_1->Pane).x1;
  __return_storage_ptr__->y1 = (param_1->Pane).y1;
  return __return_storage_ptr__;
}
