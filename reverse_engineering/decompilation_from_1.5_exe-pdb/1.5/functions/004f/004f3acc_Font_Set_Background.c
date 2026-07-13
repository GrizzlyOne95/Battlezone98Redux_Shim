/*
 * Entry: 004f3acc
 * Name: Font_Set_Background
 * Namespace: Global
 * Signature: void Font_Set_Background(FONT * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Font_Set_Background(FONT *param_1,long param_2)

{
  if (useD3D == 0) {
    if ((uint)param_2 < 0x100) {
      memset(param_1->Back_Foreground,param_2);
    }
    else {
      memmove(param_1->Back_Foreground,&Reset_Chroma,0x100);
    }
  }
  return;
}
