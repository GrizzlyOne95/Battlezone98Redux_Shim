/*
 * Entry: 00492785
 * Name: std::fill<GameFeature_*_*,GameFeature_*>
 * Namespace: std
 * Signature: void fill<GameFeature_*_*,GameFeature_*>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<GameFeature_*_*,GameFeature_*>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
