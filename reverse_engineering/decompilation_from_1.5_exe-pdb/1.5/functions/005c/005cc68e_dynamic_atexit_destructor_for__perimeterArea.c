/*
 * Entry: 005cc68e
 * Name: `dynamic_atexit_destructor_for_'perimeterArea''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'perimeterArea''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__perimeterArea__(void)

{
  std::
  _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
  ::_Tidy((_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
           *)&perimeterArea);
  operator_delete((void *)perimeterArea._0_4_);
  return;
}
