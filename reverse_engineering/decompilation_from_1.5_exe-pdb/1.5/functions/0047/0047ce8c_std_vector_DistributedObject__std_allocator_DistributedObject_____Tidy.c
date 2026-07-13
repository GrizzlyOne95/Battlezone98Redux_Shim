/*
 * Entry: 0047ce8c
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Tidy
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: void _Tidy(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Tidy
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this)

{
  if (this->_Myfirst != (DistributedObject **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (DistributedObject **)0x0;
  this->_Mylast = (DistributedObject **)0x0;
  this->_Myend = (DistributedObject **)0x0;
  return;
}
