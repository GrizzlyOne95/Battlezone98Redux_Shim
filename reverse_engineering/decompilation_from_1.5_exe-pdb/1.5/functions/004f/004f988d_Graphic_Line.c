/*
 * Entry: 004f988d
 * Name: Graphic_Line
 * Namespace: Global
 * Signature: void Graphic_Line(_GRAPHIC_BUFFER * param_1, long param_2, long param_3, long param_4, long param_5, long param_6, BITMAP_OPER param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Graphic_Line(_GRAPHIC_BUFFER *param_1,long param_2,long param_3,long param_4,long param_5,
            long param_6,BITMAP_OPER param_7)

{
  _GRAPHIC_BUFFER *p_Var1;
  int iVar2;
  long lVar3;
  int iVar4;
  _GRAPHIC_BUFFER *local_c;
  _GRAPHIC_BUFFER *local_8;
  
  p_Var1 = param_1;
  if (param_1->Status != 0) {
    local_8 = (_GRAPHIC_BUFFER *)ComputeOutCode(param_2,param_3,&param_1->Pane);
    local_c = (_GRAPHIC_BUFFER *)ComputeOutCode(param_4,param_5,&param_1->Pane);
    while (local_c != (_GRAPHIC_BUFFER *)0x0 || local_8 != (_GRAPHIC_BUFFER *)0x0) {
      if (((uint)local_8 & (uint)local_c) != 0) {
        return;
      }
      param_1 = local_8;
      if (local_8 == (_GRAPHIC_BUFFER *)0x0) {
        param_1 = local_c;
      }
      if (((uint)param_1 & 8) == 0) {
        if (((uint)param_1 & 4) == 0) {
          if (((uint)param_1 & 2) == 0) {
            iVar2 = (int)(((longlong)(param_4 - param_2) * (longlong)((p_Var1->Pane).y1 - param_3))
                         / (longlong)(param_5 - param_3));
            iVar4 = (p_Var1->Pane).y1;
          }
          else {
            iVar2 = (int)(((longlong)(param_4 - param_2) * (longlong)((p_Var1->Pane).y0 - param_3))
                         / (longlong)(param_5 - param_3));
            iVar4 = (p_Var1->Pane).y0;
          }
          lVar3 = iVar2 + param_2;
        }
        else {
          iVar4 = (int)(((longlong)(param_5 - param_3) * (longlong)((p_Var1->Pane).x1 - param_2)) /
                       (longlong)(param_4 - param_2)) + param_3;
          lVar3 = (p_Var1->Pane).x1;
        }
      }
      else {
        iVar4 = (int)(((longlong)(param_5 - param_3) * (longlong)((p_Var1->Pane).x0 - param_2)) /
                     (longlong)(param_4 - param_2)) + param_3;
        lVar3 = (p_Var1->Pane).x0;
      }
      if (param_1 == local_8) {
        local_8 = (_GRAPHIC_BUFFER *)ComputeOutCode(lVar3,iVar4,&p_Var1->Pane);
        param_3 = iVar4;
        param_2 = lVar3;
      }
      else {
        local_c = (_GRAPHIC_BUFFER *)ComputeOutCode(lVar3,iVar4,&p_Var1->Pane);
        param_4 = lVar3;
        param_5 = iVar4;
      }
    }
    Clipped_Line(p_Var1,param_2,param_3,param_4,param_5,param_6,param_7);
  }
  return;
}
