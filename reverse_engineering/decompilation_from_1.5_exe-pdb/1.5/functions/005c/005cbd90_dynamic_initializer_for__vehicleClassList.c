/*
 * Entry: 005cbd90
 * Name: `dynamic_initializer_for_'vehicleClassList''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'vehicleClassList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__vehicleClassList__(void)

{
  std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
  vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>(&vehicleClassList);
  atexit(_dynamic_atexit_destructor_for__vehicleClassList__);
  return;
}
