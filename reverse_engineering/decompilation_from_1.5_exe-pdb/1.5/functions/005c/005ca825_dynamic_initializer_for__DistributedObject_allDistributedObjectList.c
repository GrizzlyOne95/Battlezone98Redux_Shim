/*
 * Entry: 005ca825
 * Name: `dynamic_initializer_for_'DistributedObject::allDistributedObjectList''
 * Namespace: `dynamic_initializer_for_'DistributedObject
 * Signature: void allDistributedObjectList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'DistributedObject::allDistributedObjectList__(void)

{
  std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (&DistributedObject::allDistributedObjectList);
  atexit(`dynamic_atexit_destructor_for_'DistributedObject::allDistributedObjectList__);
  return;
}
