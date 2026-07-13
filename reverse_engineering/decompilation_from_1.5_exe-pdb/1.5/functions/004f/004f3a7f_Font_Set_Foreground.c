/*
 * Entry: 004f3a7f
 * Name: Font_Set_Foreground
 * Namespace: Global
 * Signature: void Font_Set_Foreground(FONT * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Font_Set_Foreground(FONT *param_1,long param_2)

{
  if (useD3D != 0) {
    Foreground_Color = param_2 & 0xff;
    return;
  }
  if ((uint)param_2 < 0x100) {
    memset(param_1->Back_Foreground + 1,param_2);
  }
  else {
    memmove(param_1->Back_Foreground + 1,&Reset_Chroma,0x100);
  }
  return;
}
