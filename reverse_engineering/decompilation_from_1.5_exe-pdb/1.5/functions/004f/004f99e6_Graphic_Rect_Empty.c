/*
 * Entry: 004f99e6
 * Name: Graphic_Rect_Empty
 * Namespace: Global
 * Signature: void Graphic_Rect_Empty(_GRAPHIC_BUFFER * param_1, long param_2, long param_3, long param_4, long param_5, long param_6, BITMAP_OPER param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Graphic_Rect_Empty(_GRAPHIC_BUFFER *param_1,long param_2,long param_3,long param_4,long param_5,
                  long param_6,BITMAP_OPER param_7)

{
  Graphic_Line(param_1,param_2,param_3,param_4,param_3,param_6,param_7);
  Graphic_Line(param_1,param_4,param_3,param_4,param_5,param_6,param_7);
  Graphic_Line(param_1,param_4,param_5,param_2,param_5,param_6,param_7);
  Graphic_Line(param_1,param_2,param_5,param_2,param_3,param_6,param_7);
  return;
}
