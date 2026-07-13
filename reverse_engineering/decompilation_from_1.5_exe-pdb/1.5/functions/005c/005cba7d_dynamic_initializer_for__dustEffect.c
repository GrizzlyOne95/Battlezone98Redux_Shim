/*
 * Entry: 005cba7d
 * Name: `dynamic_initializer_for_'dustEffect''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'dustEffect''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__dustEffect__(void)

{
  GameFeature::GameFeature((GameFeature *)&dustEffect);
  dustEffect._padding_ = (int)&DustEffect::_vftable_;
  atexit(_dynamic_atexit_destructor_for__dustEffect__);
  return;
}
