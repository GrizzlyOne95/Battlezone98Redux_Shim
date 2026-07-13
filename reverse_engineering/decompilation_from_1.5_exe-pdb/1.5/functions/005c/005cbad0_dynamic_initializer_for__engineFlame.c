/*
 * Entry: 005cbad0
 * Name: `dynamic_initializer_for_'engineFlame''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'engineFlame''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__engineFlame__(void)

{
  GameFeature::GameFeature((GameFeature *)&engineFlame);
  engineFlame._padding_ = (int)&EngineFlame::_vftable_;
  return;
}
