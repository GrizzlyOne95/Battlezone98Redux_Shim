/*
 * Entry: 00460cbe
 * Name: std::fill<Scrap_*_*,Scrap_*>
 * Namespace: std
 * Signature: void fill<Scrap_*_*,Scrap_*>(Scrap * * param_1, Scrap * * param_2, Scrap * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::fill<Scrap_*_*,Scrap_*>(Scrap **param_1,Scrap **param_2,Scrap **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
