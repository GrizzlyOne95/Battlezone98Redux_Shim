/*
 * Entry: 005cbb76
 * Name: `dynamic_initializer_for_'LightningFeature''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'LightningFeature''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__LightningFeature__(void)

{
  GameFeature::GameFeature((GameFeature *)&LightningFeature);
  LightningFeature._padding_ = (int)&LightningFeature::_vftable_;
  return;
}
