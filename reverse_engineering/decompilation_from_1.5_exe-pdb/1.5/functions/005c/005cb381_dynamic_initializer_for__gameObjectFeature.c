/*
 * Entry: 005cb381
 * Name: `dynamic_initializer_for_'gameObjectFeature''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'gameObjectFeature''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__gameObjectFeature__(void)

{
  GameFeature::GameFeature((GameFeature *)&gameObjectFeature);
  gameObjectFeature._padding_._0_1_ = (byte)gameObjectFeature._padding_ | 1;
  gameObjectFeature._padding_ = (int)&GameObjectFeature::_vftable_;
  return;
}
