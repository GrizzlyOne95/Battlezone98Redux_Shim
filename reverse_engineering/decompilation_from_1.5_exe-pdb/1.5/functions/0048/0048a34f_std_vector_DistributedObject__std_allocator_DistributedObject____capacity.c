/*
 * Entry: 0048a34f
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::capacity
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: uint capacity(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::capacity
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this)

{
  if (this->_Myfirst == (DistributedObject **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
