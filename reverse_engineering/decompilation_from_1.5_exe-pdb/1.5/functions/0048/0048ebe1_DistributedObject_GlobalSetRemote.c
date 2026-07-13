/*
 * Entry: 0048ebe1
 * Name: DistributedObject::GlobalSetRemote
 * Namespace: DistributedObject
 * Signature: void GlobalSetRemote(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::GlobalSetRemote(DistributedObject *this)

{
  DistributedObject **ppDVar1;
  
  this->object_type = '\x02';
  this->dwLocalID = dwGlobalIDCounter;
  dwGlobalIDCounter = dwGlobalIDCounter + 1;
  ppDVar1 = std::
            map<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>_>
            ::operator[](&remoteDistributedObjectMap,&this->dwLocalID);
  *ppDVar1 = this;
  return;
}
