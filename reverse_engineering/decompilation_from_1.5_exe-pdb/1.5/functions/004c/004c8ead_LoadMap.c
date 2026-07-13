/*
 * Entry: 004c8ead
 * Name: LoadMap
 * Namespace: Global
 * Signature: bool LoadMap(char * param_1, _GRAPHIC_BUFFER * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl LoadMap(char *param_1,_GRAPHIC_BUFFER *param_2)

{
  short *psVar1;
  _GRAPHIC_BUFFER *p_Var2;
  int iVar3;
  _GRAPHIC_BUFFER local_38;
  
  psVar1 = UseItem(param_1);
  if (psVar1 == (short *)0x0) {
    DEBUG_systemWarning("Could not open file \"%s\".");
    p_Var2 = Graphic_Buffer_Init_Ex(&local_38,0,0,(char *)0x0,BYTES_FORMAT);
  }
  else {
    p_Var2 = Graphic_Buffer_Init_Ex
                       (&local_38,(int)*psVar1,*(long *)(psVar1 + 2),(char *)(psVar1 + 4),
                        BYTES_FORMAT);
  }
  for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
    param_2->Width = p_Var2->Width;
    p_Var2 = (_GRAPHIC_BUFFER *)&p_Var2->Height;
    param_2 = (_GRAPHIC_BUFFER *)&param_2->Height;
  }
  UnlockItem(param_1);
  return psVar1 == (short *)0x0;
}
