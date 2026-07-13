/*
 * Entry: 005ca7f9
 * Name: `dynamic_initializer_for_'DistributedObject::remoteDistributedObjectMap''
 * Namespace: `dynamic_initializer_for_'DistributedObject
 * Signature: void remoteDistributedObjectMap''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'DistributedObject::remoteDistributedObjectMap__(void)

{
  std::
  map<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>_>
  ::
  map<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>_>
            (&DistributedObject::remoteDistributedObjectMap);
  atexit(`dynamic_atexit_destructor_for_'DistributedObject::remoteDistributedObjectMap__);
  return;
}
