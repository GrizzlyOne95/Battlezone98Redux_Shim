/*
 * Entry: 0044ff70
 * Name: std::swap<Strip_*>
 * Namespace: std
 * Signature: void swap<Strip_*>(Strip * * param_1, Strip * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::swap<Strip_*>(Strip **param_1,Strip **param_2)

{
  Strip *pSVar1;
  
  if (param_1 != param_2) {
    pSVar1 = *param_1;
    *param_1 = *param_2;
    *param_2 = pSVar1;
  }
  return;
}
