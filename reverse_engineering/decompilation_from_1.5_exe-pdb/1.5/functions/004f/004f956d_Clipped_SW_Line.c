/*
 * Entry: 004f956d
 * Name: Clipped_SW_Line
 * Namespace: Global
 * Signature: void Clipped_SW_Line(_GRAPHIC_BUFFER * param_1, long param_2, long param_3, long param_4, long param_5, long param_6, BITMAP_OPER param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Clipped_SW_Line(_GRAPHIC_BUFFER *param_1,long param_2,long param_3,long param_4,long param_5,
               long param_6,BITMAP_OPER param_7)

{
  long lVar1;
  int iVar2;
  int iVar3;
  long unaff_EBP;
  long unaff_ESI;
  uchar *puVar4;
  long unaff_EDI;
  long lVar5;
  
  if (param_1->Status != 0) {
    iVar2 = param_1->Width;
    iVar3 = param_4 - param_2;
    lVar1 = param_5 - param_3;
    puVar4 = param_1->Buffer + param_2 + ((param_1->Pane).y0 + param_3) * iVar2 + (param_1->Pane).x0
    ;
    if (param_7 == SOLID_PIXELS) {
      if (lVar1 < 0) {
        iVar2 = -iVar2;
        lVar1 = -lVar1;
      }
      if (iVar3 < 0) {
        iVar3 = -iVar3;
        lVar5 = -1;
      }
      else {
        lVar5 = 1;
      }
      Draw_Line(puVar4,iVar3,lVar1,lVar5,iVar2,param_6);
    }
    else if (param_7 == ONE_THIRD_TRANSLUCENT_PIXELS) {
      if (lVar1 < 0) {
        lVar1 = -lVar1;
      }
      if (iVar3 < 0) {
        iVar3 = -iVar3;
      }
      Draw_Translucent_Line(puVar4,iVar3,lVar1,unaff_ESI,unaff_EDI,unaff_EBP);
    }
    else if (param_7 == TWO_THIRD_TRANSLUCENT_PIXELS) {
      if (iVar3 < 0) {
        iVar3 = -iVar3;
      }
      Draw_Translucent2_Line(puVar4,iVar3,param_6,unaff_ESI,unaff_EDI,unaff_EBP);
    }
    else if (param_7 == ALPHA_PIXELS) {
      if (lVar1 < 0) {
        lVar1 = -lVar1;
      }
      if (iVar3 < 0) {
        iVar3 = -iVar3;
      }
      Draw_Alpha_Blend_Line(puVar4,iVar3,lVar1,unaff_ESI,unaff_EDI,unaff_EBP);
    }
  }
  return;
}
