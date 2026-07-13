/*
 * Entry: 00542ec3
 * Name: D3D_SetPalette
 * Namespace: Global
 * Signature: int D3D_SetPalette(VIDEO_DEVICE * param_1, long param_2, long param_3, RGB * param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
D3D_SetPalette(VIDEO_DEVICE *param_1,long param_2,long param_3,RGB *param_4,char *param_5)

{
  memmove(param_1->Palette + param_2,param_4 + param_2,param_3 * 3);
  ApplyGammaToPalette(param_1->Palette + param_2,param_2,param_3,0);
  D3D_OverlayPalette(param_1,param_1->Palette);
  Device_Init_Luminance_Table(param_1,param_5);
  UpdateFloatPalette(param_1->Palette);
  return 1;
}
