/*
 * Entry: 00451160
 * Name: std::fill<Strip_*_*,Strip_*>
 * Namespace: std
 * Signature: void fill<Strip_*_*,Strip_*>(Strip * * param_1, Strip * * param_2, Strip * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::fill<Strip_*_*,Strip_*>(Strip **param_1,Strip **param_2,Strip **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
