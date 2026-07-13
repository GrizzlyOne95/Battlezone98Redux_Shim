/*
 * Entry: 004cf5a6
 * Name: PrintChar
 * Namespace: Global
 * Signature: void PrintChar(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PrintChar(ushort param_1)

{
  _GRAPHIC_BUFFER *p_Var1;
  int iVar2;
  _GRAPHIC_BUFFER *p_Var3;
  _GRAPHIC_BUFFER local_6c;
  _GRAPHIC_BUFFER local_38;
  
  p_Var1 = Graphic_Buffer_Init_Ex(&local_6c,0x10,0x10,charBuffer,BYTES_FORMAT);
  p_Var3 = &local_38;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    p_Var3->Width = p_Var1->Width;
    p_Var1 = (_GRAPHIC_BUFFER *)&p_Var1->Height;
    p_Var3 = (_GRAPHIC_BUFFER *)&p_Var3->Height;
  }
  memset(charBuffer,0xff,0x100);
  memset(J_Font->Back_Foreground + 1,DisplayInterface::colorWhite,0x100);
  Font_Print_Character(J_Font,&local_38,0,0,param_1);
  Graphic_Buffer_Close(&local_38);
  return;
}
