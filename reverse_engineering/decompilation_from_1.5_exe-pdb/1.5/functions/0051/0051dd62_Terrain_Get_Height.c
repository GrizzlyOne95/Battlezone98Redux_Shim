/*
 * Entry: 0051dd62
 * Name: Terrain_Get_Height
 * Namespace: Global
 * Signature: long Terrain_Get_Height(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Terrain_Get_Height(long param_1,long param_2)

{
  uint in_EAX;
  uint in_ECX;
  
  return Terrain.Zone_Page_Table[(in_EAX & 0xffffff80) + ((int)in_ECX >> 7) + 0xc18]->Height
         [(in_EAX & 0x7f) * 0x80 + (in_ECX & 0x7f)] & 0xfff;
}
