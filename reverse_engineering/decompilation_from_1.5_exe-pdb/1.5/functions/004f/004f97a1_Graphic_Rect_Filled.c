/*
 * Entry: 004f97a1
 * Name: Graphic_Rect_Filled
 * Namespace: Global
 * Signature: void Graphic_Rect_Filled(_GRAPHIC_BUFFER * param_1, long param_2, long param_3, long param_4, long param_5, long param_6, BITMAP_OPER param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Graphic_Rect_Filled(_GRAPHIC_BUFFER *param_1,long param_2,long param_3,long param_4,long param_5,
                   long param_6,BITMAP_OPER param_7)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((((param_2 <= param_4) && (param_3 <= param_5)) &&
      (iVar1 = (param_1->Pane).x1, param_2 < iVar1)) &&
     (((iVar2 = (param_1->Pane).x0, iVar2 < param_4 && (iVar3 = (param_1->Pane).y1, param_3 < iVar3)
       ) && (iVar4 = (param_1->Pane).y0, iVar4 < param_5)))) {
    if (param_2 < iVar2) {
      param_2 = iVar2;
    }
    if (iVar1 < param_4) {
      param_4 = iVar1;
    }
    if (param_3 < iVar4) {
      param_3 = iVar4;
    }
    if (iVar3 < param_5) {
      param_5 = iVar3;
    }
    Clipped_Rect_Filled(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  }
  return;
}
