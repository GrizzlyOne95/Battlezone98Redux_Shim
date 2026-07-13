/*
 * Entry: 0051d338
 * Name: Close_Stars
 * Namespace: Global
 * Signature: void Close_Stars(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Close_Stars(void)

{
  tagVisibleStar *ptVar1;
  
  ptVar1 = VisibleStar;
  do {
    if (ptVar1->name[0] != '\0') {
      TexCache_UnlockTexture(ptVar1->name);
    }
    ptVar1 = ptVar1 + 1;
  } while ((int)ptVar1 < 0xc40498);
  StarSet.starCount = 0;
  StarSet.domeRadius = 0.0;
  memset(VisibleStar,0,0xb00);
  return;
}
