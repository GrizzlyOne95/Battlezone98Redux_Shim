/*
 * Entry: 00544500
 * Name: FindTextureIndex
 * Namespace: Global
 * Signature: long FindTextureIndex(TEXTURE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl FindTextureIndex(TEXTURE *param_1)

{
  long lVar1;
  int iVar2;
  int iVar3;
  TEXTURE *unaff_ESI;
  
  iVar3 = 0;
  lVar1 = 0;
  iVar2 = textureCount + -1;
  if (-1 < iVar2) {
    do {
      lVar1 = iVar2 + iVar3 >> 1;
      if (cache[lVar1].texture < unaff_ESI) {
        iVar3 = lVar1 + 1;
      }
      else {
        iVar2 = lVar1 + -1;
      }
    } while (iVar3 <= iVar2);
  }
  if (cache[lVar1].texture < unaff_ESI) {
    lVar1 = lVar1 + 1;
  }
  return lVar1;
}
