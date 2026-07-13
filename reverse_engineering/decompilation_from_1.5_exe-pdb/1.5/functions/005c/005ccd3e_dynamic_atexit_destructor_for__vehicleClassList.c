/*
 * Entry: 005ccd3e
 * Name: `dynamic_atexit_destructor_for_'vehicleClassList''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'vehicleClassList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__vehicleClassList__(void)

{
  std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::_Tidy(&vehicleClassList);
  operator_delete((void *)vehicleClassList._padding_);
  return;
}
