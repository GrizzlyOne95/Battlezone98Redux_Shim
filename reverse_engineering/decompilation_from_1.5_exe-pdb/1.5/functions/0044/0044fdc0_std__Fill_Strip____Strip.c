/*
 * Entry: 0044fdc0
 * Name: std::_Fill<Strip_*_*,Strip_*>
 * Namespace: std
 * Signature: void _Fill<Strip_*_*,Strip_*>(Strip * * param_1, Strip * * param_2, Strip * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Fill<Strip_*_*,Strip_*>(Strip **param_1,Strip **param_2,Strip **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
