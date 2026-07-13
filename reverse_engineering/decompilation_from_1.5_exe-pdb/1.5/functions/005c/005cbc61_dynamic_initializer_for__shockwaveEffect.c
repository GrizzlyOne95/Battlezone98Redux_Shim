/*
 * Entry: 005cbc61
 * Name: `dynamic_initializer_for_'shockwaveEffect''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'shockwaveEffect''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__shockwaveEffect__(void)

{
  GameFeature::GameFeature((GameFeature *)&shockwaveEffect);
  shockwaveEffect._padding_ = (int)&ShockWaveEffect::_vftable_;
  return;
}
