/*
 * Entry: 005cc6a5
 * Name: `dynamic_atexit_destructor_for_'buildingArea''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'buildingArea''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__buildingArea__(void)

{
  std::
  _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
  ::_Tidy((_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
           *)&buildingArea);
  operator_delete((void *)buildingArea._0_4_);
  return;
}
