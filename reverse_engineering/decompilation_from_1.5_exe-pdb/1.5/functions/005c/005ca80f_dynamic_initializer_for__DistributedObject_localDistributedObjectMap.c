/*
 * Entry: 005ca80f
 * Name: `dynamic_initializer_for_'DistributedObject::localDistributedObjectMap''
 * Namespace: `dynamic_initializer_for_'DistributedObject
 * Signature: void localDistributedObjectMap''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'DistributedObject::localDistributedObjectMap__(void)

{
  std::
  map<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>_>
  ::
  map<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>_>
            (&DistributedObject::localDistributedObjectMap);
  atexit(`dynamic_atexit_destructor_for_'DistributedObject::localDistributedObjectMap__);
  return;
}
