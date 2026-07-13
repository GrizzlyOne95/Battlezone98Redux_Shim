/*
 * Entry: 00492080
 * Name: std::iter_swap<GameFeature_*_*,GameFeature_*_*>
 * Namespace: std
 * Signature: void iter_swap<GameFeature_*_*,GameFeature_*_*>(GameFeature * * param_1, GameFeature * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::iter_swap<GameFeature_*_*,GameFeature_*_*>(GameFeature **param_1,GameFeature **param_2)

{
  GameFeature *pGVar1;
  
  if (param_1 != param_2) {
    pGVar1 = *param_1;
    *param_1 = *param_2;
    *param_2 = pGVar1;
  }
  return;
}
