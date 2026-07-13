/*
 * Entry: 004e3e53
 * Name: Font_Print_String_Shadowed
 * Namespace: Global
 * Signature: void Font_Print_String_Shadowed(FONT * param_1, _GRAPHIC_BUFFER * param_2, long param_3, long param_4, char * param_5, long param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Font_Print_String_Shadowed
          (FONT *param_1,_GRAPHIC_BUFFER *param_2,long param_3,long param_4,char *param_5,
          long param_6)

{
  FONT *unaff_EBX;
  int unaff_ESI;
  int unaff_EDI;
  
  Font_Set_Foreground(unaff_EBX,DisplayInterface::colorBlack);
  Font_Print_String(unaff_EBX,(_GRAPHIC_BUFFER *)param_1,unaff_EDI + 1,unaff_ESI + 1,(char *)param_2
                   );
  Font_Set_Foreground(unaff_EBX,param_3);
  Font_Print_String(unaff_EBX,(_GRAPHIC_BUFFER *)param_1,unaff_EDI,unaff_ESI,(char *)param_2);
  return;
}
