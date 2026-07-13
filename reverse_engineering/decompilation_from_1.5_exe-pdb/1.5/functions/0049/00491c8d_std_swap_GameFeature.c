/*
 * Entry: 00491c8d
 * Name: std::swap<GameFeature_*>
 * Namespace: std
 * Signature: void swap<GameFeature_*>(GameFeature * * param_1, GameFeature * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::swap<GameFeature_*>(GameFeature **param_1,GameFeature **param_2)

{
  GameFeature *pGVar1;
  
  if (param_1 != param_2) {
    pGVar1 = *param_1;
    *param_1 = *param_2;
    *param_2 = pGVar1;
  }
  return;
}
