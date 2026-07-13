/*
 * Entry: 005cc808
 * Name: `dynamic_atexit_destructor_for_'DistributedObject::localDistributedObjectMap''
 * Namespace: `dynamic_atexit_destructor_for_'DistributedObject
 * Signature: void localDistributedObjectMap''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'DistributedObject::localDistributedObjectMap__(void)

{
  std::
  _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
  ::_Tidy((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
           *)&DistributedObject::localDistributedObjectMap);
  operator_delete((void *)DistributedObject::localDistributedObjectMap._0_4_);
  return;
}
