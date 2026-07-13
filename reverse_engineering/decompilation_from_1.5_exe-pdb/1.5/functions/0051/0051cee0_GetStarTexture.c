/*
 * Entry: 0051cee0
 * Name: GetStarTexture
 * Namespace: Global
 * Signature: TEXTURE * GetStarTexture(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TEXTURE * __cdecl GetStarTexture(int param_1)

{
  if (param_1 < StarSet.starCount) {
    return VisibleStar[param_1].texture;
  }
  return (TEXTURE *)0x0;
}
