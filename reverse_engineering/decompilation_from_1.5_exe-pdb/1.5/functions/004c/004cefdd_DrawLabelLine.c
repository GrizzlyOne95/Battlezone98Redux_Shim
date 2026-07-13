/*
 * Entry: 004cefdd
 * Name: DrawLabelLine
 * Namespace: Global
 * Signature: void DrawLabelLine(_GRAPHIC_BUFFER * param_1, tagRECT * param_2, tagPOINT * param_3, tagPOINT * param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
DrawLabelLine(_GRAPHIC_BUFFER *param_1,tagRECT *param_2,tagPOINT *param_3,tagPOINT *param_4,
             long param_5)

{
  long *in_EAX;
  int *unaff_EBX;
  int *unaff_EDI;
  
  Graphic_Rect_Filled(param_1,*unaff_EDI + -2,unaff_EDI[1] + -2,*unaff_EDI + 2,unaff_EDI[1] + 2,
                      (long)param_2,SOLID_PIXELS);
  if (in_EAX[1] != -1) {
    Graphic_Line(param_1,*unaff_EDI,unaff_EDI[1],*unaff_EBX + -0x32,unaff_EDI[1],(long)param_2,
                 SOLID_PIXELS);
    Graphic_Line(param_1,*unaff_EBX + -0x32,unaff_EDI[1],*in_EAX,in_EAX[1],(long)param_2,
                 SOLID_PIXELS);
    Graphic_Rect_Filled(param_1,*in_EAX + -2,in_EAX[1] + -2,*in_EAX + 2,in_EAX[1] + 2,(long)param_2,
                        SOLID_PIXELS);
  }
  return;
}
