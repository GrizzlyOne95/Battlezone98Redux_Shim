/*
 * Entry: 005cccab
 * Name: `dynamic_atexit_destructor_for_'scrapGauge''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'scrapGauge''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__scrapGauge__(void)

{
  scrapGauge._padding_ = (int)&ScrapGauge::_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)&scrapGauge);
  return;
}
