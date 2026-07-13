/*
 * Entry: 005c9b45
 * Name: `dynamic_initializer_for_'buildingArea''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'buildingArea''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__buildingArea__(void)

{
  std::
  map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
  ::
  map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
            (&buildingArea);
  atexit(_dynamic_atexit_destructor_for__buildingArea__);
  return;
}
