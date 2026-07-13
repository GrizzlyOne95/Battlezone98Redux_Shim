/*
 * Entry: 005cba9d
 * Name: `dynamic_initializer_for_'earthQuake''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'earthQuake''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__earthQuake__(void)

{
  GameFeature::GameFeature((GameFeature *)&earthQuake);
  earthQuake.scale = 0.0;
  earthQuake._padding_ = (int)&EarthQuake::_vftable_;
  return;
}
