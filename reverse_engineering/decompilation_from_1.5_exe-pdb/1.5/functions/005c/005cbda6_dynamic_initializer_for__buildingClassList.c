/*
 * Entry: 005cbda6
 * Name: `dynamic_initializer_for_'buildingClassList''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'buildingClassList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__buildingClassList__(void)

{
  std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
  vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>(&buildingClassList);
  atexit(_dynamic_atexit_destructor_for__buildingClassList__);
  return;
}
