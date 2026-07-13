/*
 * Entry: 005c9b5b
 * Name: `dynamic_initializer_for_'perimeterArea''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'perimeterArea''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__perimeterArea__(void)

{
  std::
  map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
  ::
  map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
            (&perimeterArea);
  atexit(_dynamic_atexit_destructor_for__perimeterArea__);
  return;
}
