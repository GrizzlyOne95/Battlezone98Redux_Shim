/*
 * Entry: 00542f42
 * Name: D3D_Lock_Buffer
 * Namespace: Global
 * Signature: int D3D_Lock_Buffer(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3D_Lock_Buffer(VIDEO_DEVICE *param_1)

{
  _GRAPHIC_BUFFER *p_Var1;
  int iVar2;
  VIDEO_DEVICE *pVVar3;
  _GRAPHIC_BUFFER local_58;
  _D3DSURFACE_DESC local_24;
  
  iVar2 = 1;
  if (Is_Buffer_Lock != 1) {
    Is_Buffer_Lock = 1;
    iVar2 = 0;
    if (d3dappi.lpBackBuffer != (IDirect3DSurface9 *)0x0) {
      (*(d3dappi.lpBackBuffer)->lpVtbl->GetDesc)(d3dappi.lpBackBuffer,&local_24);
      p_Var1 = Graphic_Buffer_Init_Ex
                         (&local_58,local_24.Width,local_24.Height,(char *)0xfff00000,WORD_FORMAT);
      pVVar3 = param_1;
      for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
        (pVVar3->Viewport).Width = p_Var1->Width;
        p_Var1 = (_GRAPHIC_BUFFER *)&p_Var1->Height;
        pVVar3 = (VIDEO_DEVICE *)&(pVVar3->Viewport).Height;
      }
      Graphic_Buffer_Set_Pane(&param_1->Viewport,0,0,local_24.Width - 1,local_24.Height - 1);
      iVar2 = 1;
    }
  }
  return iVar2;
}
