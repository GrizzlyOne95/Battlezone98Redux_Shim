/*
 * Entry: 004fa112
 * Name: Save_pcx_Texture
 * Namespace: Global
 * Signature: int Save_pcx_Texture(char * param_1, TEXTURE * param_2, RGB * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Save_pcx_Texture(char *param_1,TEXTURE *param_2,RGB *param_3)

{
  _GRAPHIC_BUFFER *p_Var1;
  int iVar2;
  _GRAPHIC_BUFFER *p_Var3;
  _GRAPHIC_BUFFER local_6c;
  _GRAPHIC_BUFFER local_38;
  
  p_Var1 = Graphic_Buffer_Init_Ex
                     (&local_6c,(int)param_2->width,param_2->height,(char *)(param_2 + 1),
                      BYTES_FORMAT);
  p_Var3 = &local_38;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    p_Var3->Width = p_Var1->Width;
    p_Var1 = (_GRAPHIC_BUFFER *)&p_Var1->Height;
    p_Var3 = (_GRAPHIC_BUFFER *)&p_Var3->Height;
  }
  iVar2 = Save_pcx_GraphicBuffer(param_1,&local_38,param_3);
  Graphic_Buffer_Close(&local_38);
  return iVar2;
}
