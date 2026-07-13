/*
 * Entry: 00504fb2
 * Name: AllocViewport
 * Namespace: Global
 * Signature: void AllocViewport(VIDEO_DEVICE * param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AllocViewport(VIDEO_DEVICE *param_1,long param_2,long param_3)

{
  _GRAPHIC_BUFFER *p_Var1;
  int iVar2;
  _GRAPHIC_BUFFER local_38;
  
  p_Var1 = Graphic_Buffer_Init_Ex(&local_38,param_2,param_3,(char *)0x0,BYTES_FORMAT);
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    (param_1->Viewport).Width = p_Var1->Width;
    p_Var1 = (_GRAPHIC_BUFFER *)&p_Var1->Height;
    param_1 = (VIDEO_DEVICE *)&(param_1->Viewport).Height;
  }
  return;
}
