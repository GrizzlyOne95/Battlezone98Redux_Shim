/*
 * Entry: 0044ee00
 * Name: CompareStrips
 * Namespace: Global
 * Signature: bool CompareStrips(Strip * param_1, Strip * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CompareStrips(Strip *param_1,Strip *param_2)

{
  Strip *in_ECX;
  Strip *pSVar1;
  float fVar2;
  
  pSVar1 = (Strip *)StripDist(in_ECX);
  fVar2 = StripDist(pSVar1);
  if ((float)pSVar1 < fVar2) {
    return true;
  }
  return false;
}
