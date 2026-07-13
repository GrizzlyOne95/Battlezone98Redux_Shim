/*
 * Entry: 005cb7b8
 * Name: `dynamic_initializer_for_'radarList''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'radarList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__radarList__(void)

{
  std::vector<RadarItem,std::allocator<RadarItem>_>::vector<RadarItem,std::allocator<RadarItem>_>
            (&radarList,0x200,&emptyItem);
  atexit(_dynamic_atexit_destructor_for__radarList__);
  return;
}
