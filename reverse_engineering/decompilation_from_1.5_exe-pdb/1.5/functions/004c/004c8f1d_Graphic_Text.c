/*
 * Entry: 004c8f1d
 * Name: Graphic_Text
 * Namespace: Global
 * Signature: void Graphic_Text(_GRAPHIC_BUFFER * param_1, long param_2, long param_3, long * param_4, long * param_5, char * param_6, FONT * param_7, long param_8, long param_9, int param_10, long param_11, long param_12)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Graphic_Text(_GRAPHIC_BUFFER *param_1,long param_2,long param_3,long *param_4,long *param_5,
            char *param_6,FONT *param_7,long param_8,long param_9,int param_10,long param_11,
            long param_12)

{
  int iVar1;
  int iVar2;
  
  Font_Get_String_Dimensions(param_7,param_6,param_4,param_5);
  iVar2 = param_2 - (*param_4 * param_11) / 2;
  iVar1 = param_3 - (*param_5 * param_12) / 2;
  *param_4 = *param_4 + iVar2;
  *param_5 = *param_5 + iVar1;
  if (-1 < param_9) {
    Graphic_Rect_Filled(param_1,iVar2,iVar1,*param_4,*param_5,param_9,param_10);
  }
  Font_Set_Foreground(param_7,param_8);
  Font_Print_String(param_7,param_1,iVar2,iVar1,param_6);
  return;
}
