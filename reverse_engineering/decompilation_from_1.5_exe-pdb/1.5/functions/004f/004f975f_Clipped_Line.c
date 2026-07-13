/*
 * Entry: 004f975f
 * Name: Clipped_Line
 * Namespace: Global
 * Signature: void Clipped_Line(_GRAPHIC_BUFFER * param_1, long param_2, long param_3, long param_4, long param_5, long param_6, BITMAP_OPER param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Clipped_Line(_GRAPHIC_BUFFER *param_1,long param_2,long param_3,long param_4,long param_5,
            long param_6,BITMAP_OPER param_7)

{
  if (((VIDEO_DEVICE *)param_1 == &Device) && (useD3D != 0)) {
    Clipped_HW_Line(&Device.Viewport,param_2,param_3,param_4,param_5,param_6,param_7);
    return;
  }
  Clipped_SW_Line(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  return;
}
