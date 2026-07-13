/*
 * Entry: 004e89be
 * Name: Screen_Draw_Pixel
 * Namespace: Global
 * Signature: void Screen_Draw_Pixel(CAMERA * param_1, VECTOR_3D * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Screen_Draw_Pixel(CAMERA *param_1,VECTOR_3D *param_2,long param_3)

{
  int iVar1;
  int iVar2;
  _GRAPHIC_BUFFER *p_Var3;
  int iVar4;
  float *in_EAX;
  uchar *puVar5;
  int local_14;
  int local_c;
  
  p_Var3 = param_1->Buffer;
  local_c = SUB84((double)((float)Float2Int + in_EAX[1]),0);
  iVar1 = (p_Var3->Pane).x1;
  iVar2 = (p_Var3->Pane).y1;
  iVar4 = p_Var3->Width;
  local_14 = SUB84((double)(*in_EAX + (float)Float2Int),0);
  puVar5 = p_Var3->Buffer + (p_Var3->Pane).x0 + local_14 + ((p_Var3->Pane).y0 + local_c) * iVar4;
  *puVar5 = (uchar)param_2;
  if ((local_c + 1 < iVar2) && (local_14 + 1 < iVar1)) {
    puVar5[1] = (uchar)param_2;
    puVar5[iVar4] = (uchar)param_2;
    (puVar5 + iVar4)[1] = (uchar)param_2;
  }
  return;
}
