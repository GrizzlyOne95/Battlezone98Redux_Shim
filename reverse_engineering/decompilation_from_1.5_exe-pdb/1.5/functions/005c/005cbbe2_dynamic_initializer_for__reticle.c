/*
 * Entry: 005cbbe2
 * Name: `dynamic_initializer_for_'reticle''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'reticle''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__reticle__(void)

{
  GameFeature::GameFeature((GameFeature *)&reticle);
  reticle._padding_ = (int)&Reticle::_vftable_;
  return;
}
