/*
 * Entry: 0048ebaf
 * Name: DistributedObject::GlobalSetLocal
 * Namespace: DistributedObject
 * Signature: void GlobalSetLocal(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::GlobalSetLocal(DistributedObject *this)

{
  DistributedObject **ppDVar1;
  
  if ((this->object_type != '\x01') && (this->object_type != '\x02')) {
    this->object_type = '\x01';
    this->dwLocalID = dwGlobalIDCounter;
    dwGlobalIDCounter = dwGlobalIDCounter + 1;
    ppDVar1 = std::
              map<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>_>
              ::operator[](&localDistributedObjectMap,&this->dwLocalID);
    *ppDVar1 = this;
  }
  return;
}
