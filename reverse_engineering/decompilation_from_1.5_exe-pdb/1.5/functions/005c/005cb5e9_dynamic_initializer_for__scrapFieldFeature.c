/*
 * Entry: 005cb5e9
 * Name: `dynamic_initializer_for_'scrapFieldFeature''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'scrapFieldFeature''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__scrapFieldFeature__(void)

{
  GameFeature::GameFeature((GameFeature *)&scrapFieldFeature);
  scrapFieldFeature._padding_ = (int)&ScrapFieldFeature::_vftable_;
  return;
}
