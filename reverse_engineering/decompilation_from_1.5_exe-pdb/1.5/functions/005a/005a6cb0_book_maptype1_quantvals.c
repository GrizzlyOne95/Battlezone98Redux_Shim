/*
 * Entry: 005a6cb0
 * Name: _book_maptype1_quantvals
 * Namespace: Global
 * Signature: long _book_maptype1_quantvals(static_codebook * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl _book_maptype1_quantvals(static_codebook *param_1)

{
  int iVar1;
  int iVar2;
  int extraout_EAX;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  
  iVar1 = param_1->dim;
  iVar2 = param_1->entries;
  fVar7 = (float10)__CIpow();
  floor((double)fVar7);
  _ftol2_sse();
  iVar3 = extraout_EAX;
  while( true ) {
    while( true ) {
      iVar4 = 1;
      iVar5 = 1;
      if (0 < iVar1) {
        iVar6 = iVar1;
        do {
          iVar4 = iVar4 * iVar3;
          iVar5 = iVar5 * (iVar3 + 1);
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      if (iVar4 <= iVar2) break;
      iVar3 = iVar3 + -1;
    }
    if (iVar2 < iVar5) break;
    iVar3 = iVar3 + 1;
  }
  return iVar3;
}
