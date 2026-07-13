/*
 * Entry: 005cbbb7
 * Name: `dynamic_initializer_for_'particleEffect''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'particleEffect''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__particleEffect__(void)

{
  GameFeature::GameFeature((GameFeature *)&particleEffect);
  particleEffect._padding_ = (int)&ParticleEffect::_vftable_;
  return;
}
