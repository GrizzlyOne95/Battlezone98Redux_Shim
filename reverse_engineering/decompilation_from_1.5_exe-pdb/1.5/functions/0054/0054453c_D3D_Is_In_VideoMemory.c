/*
 * Entry: 0054453c
 * Name: D3D_Is_In_VideoMemory
 * Namespace: Global
 * Signature: int D3D_Is_In_VideoMemory(TEXTURE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3D_Is_In_VideoMemory(TEXTURE *param_1)

{
  long lVar1;
  TEXTURE *unaff_ESI;
  
  if (textureCount != 0) {
    lVar1 = FindTextureIndex(unaff_ESI);
    if (param_1 == cache[lVar1].texture) {
      return 1;
    }
  }
  return 0;
}
