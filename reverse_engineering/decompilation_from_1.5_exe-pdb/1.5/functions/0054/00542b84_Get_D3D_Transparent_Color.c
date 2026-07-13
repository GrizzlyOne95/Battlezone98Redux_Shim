/*
 * Entry: 00542b84
 * Name: Get_D3D_Transparent_Color
 * Namespace: Global
 * Signature: long Get_D3D_Transparent_Color(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Get_D3D_Transparent_Color(void)

{
  return D3D_Texture_Format_Remap_Palette[1][0xff];
}
