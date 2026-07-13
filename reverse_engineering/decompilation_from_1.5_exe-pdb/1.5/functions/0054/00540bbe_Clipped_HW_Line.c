/*
 * Entry: 00540bbe
 * Name: Clipped_HW_Line
 * Namespace: Global
 * Signature: void Clipped_HW_Line(_GRAPHIC_BUFFER * param_1, long param_2, long param_3, long param_4, long param_5, int param_6, long param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Clipped_HW_Line(_GRAPHIC_BUFFER *param_1,long param_2,long param_3,long param_4,long param_5,
               int param_6,long param_7)

{
  tagPOINT local_24;
  long local_1c;
  long local_18;
  
  local_24.x = param_2;
  local_24.y = param_3;
  local_1c = param_4;
  local_18 = param_5;
  D3D_PolyLine(&local_24,2,(POLYGON_SKIN)param_6);
  return;
}
