/*
 * Entry: 00489254
 * Name: std::fill<Craft_*_*,Craft_*>
 * Namespace: std
 * Signature: void fill<Craft_*_*,Craft_*>(Craft * * param_1, Craft * * param_2, Craft * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::fill<Craft_*_*,Craft_*>(Craft **param_1,Craft **param_2,Craft **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
