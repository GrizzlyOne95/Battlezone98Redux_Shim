/*
 * Entry: 0048a362
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::size
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: uint size(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::size
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
