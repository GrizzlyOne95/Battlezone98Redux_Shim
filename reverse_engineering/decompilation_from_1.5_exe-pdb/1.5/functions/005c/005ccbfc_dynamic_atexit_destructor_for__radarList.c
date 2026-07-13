/*
 * Entry: 005ccbfc
 * Name: `dynamic_atexit_destructor_for_'radarList''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'radarList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__radarList__(void)

{
  std::vector<RadarItem,std::allocator<RadarItem>_>::_Tidy(&radarList);
  operator_delete((void *)radarList._padding_);
  return;
}
