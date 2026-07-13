/*
 * Entry: 005cc7da
 * Name: `dynamic_atexit_destructor_for_'DistributedObject::allDistributedObjectList''
 * Namespace: `dynamic_atexit_destructor_for_'DistributedObject
 * Signature: void allDistributedObjectList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'DistributedObject::allDistributedObjectList__(void)

{
  std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Tidy
            (&DistributedObject::allDistributedObjectList);
  operator_delete((void *)DistributedObject::allDistributedObjectList._padding_);
  return;
}
