/*
 * Entry: 004c32d7
 * Name: ColorFade_SetFade
 * Namespace: Global
 * Signature: void ColorFade_SetFade(float param_1, float param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ColorFade_SetFade(float param_1,float param_2,int param_3,int param_4,int param_5)

{
  ColorFade::SetFade(&colorFade,param_1,param_2,param_3,param_4,param_5);
  return;
}
