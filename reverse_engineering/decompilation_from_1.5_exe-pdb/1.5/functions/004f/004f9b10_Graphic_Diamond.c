/*
 * Entry: 004f9b10
 * Name: Graphic_Diamond
 * Namespace: Global
 * Signature: void Graphic_Diamond(_GRAPHIC_BUFFER * param_1, long param_2, long param_3, long param_4, long param_5, BITMAP_OPER param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Graphic_Diamond(_GRAPHIC_BUFFER *param_1,long param_2,long param_3,long param_4,long param_5,
               BITMAP_OPER param_6)

{
  Graphic_Line(param_1,param_2 + param_4,param_3,param_2,param_3 + param_4,param_5,param_6);
  Graphic_Line(param_1,param_2,param_3 + param_4,param_2 - param_4,param_3,param_5,param_6);
  Graphic_Line(param_1,param_2 - param_4,param_3,param_2,param_3 - param_4,param_5,param_6);
  Graphic_Line(param_1,param_2,param_3 - param_4,param_2 + param_4,param_3,param_5,param_6);
  return;
}
