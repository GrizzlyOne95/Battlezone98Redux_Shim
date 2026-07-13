/*
 * Entry: 005ccd55
 * Name: `dynamic_atexit_destructor_for_'buildingClassList''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'buildingClassList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__buildingClassList__(void)

{
  std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Tidy(&buildingClassList);
  operator_delete((void *)buildingClassList._padding_);
  return;
}
