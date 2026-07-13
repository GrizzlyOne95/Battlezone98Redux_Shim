/*
 * Entry: 0051ca3a
 * Name: GetCloudTexture
 * Namespace: Global
 * Signature: TEXTURE * GetCloudTexture(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TEXTURE * __cdecl GetCloudTexture(int param_1)

{
  if (param_1 < CloudSet.typeCount) {
    return CloudSet.texture[param_1];
  }
  return (TEXTURE *)0x0;
}
