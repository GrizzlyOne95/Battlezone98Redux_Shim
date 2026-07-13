/*
 * Entry: 00450b20
 * Name: std::iter_swap<Strip_*_*,Strip_*_*>
 * Namespace: std
 * Signature: void iter_swap<Strip_*_*,Strip_*_*>(Strip * * param_1, Strip * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::iter_swap<Strip_*_*,Strip_*_*>(Strip **param_1,Strip **param_2)

{
  Strip *pSVar1;
  
  if (param_1 != param_2) {
    pSVar1 = *param_1;
    *param_1 = *param_2;
    *param_2 = pSVar1;
  }
  return;
}
