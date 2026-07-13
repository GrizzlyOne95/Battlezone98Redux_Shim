/*
 * Entry: 0045e3a2
 * Name: std::_Fill<Scrap_*_*,Scrap_*>
 * Namespace: std
 * Signature: void _Fill<Scrap_*_*,Scrap_*>(Scrap * * param_1, Scrap * * param_2, Scrap * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Fill<Scrap_*_*,Scrap_*>(Scrap **param_1,Scrap **param_2,Scrap **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
