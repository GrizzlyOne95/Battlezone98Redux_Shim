/*
 * Entry: 0048d209
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Umove<DistributedObject_*_*>
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: DistributedObject * * _Umove<DistributedObject_*_*>(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this, DistributedObject * * param_1, DistributedObject * * param_2, DistributedObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject ** __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Umove<DistributedObject_*_*>
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this,
          DistributedObject **param_1,DistributedObject **param_2,DistributedObject **param_3)

{
  DistributedObject **ppDVar1;
  
  ppDVar1 = stdext::
            unchecked_uninitialized_copy<DistributedObject_*_*,DistributedObject_*_*,std::allocator<DistributedObject_*>_>
                      (param_1,param_2,param_3,(allocator<DistributedObject_*> *)&this->_padding_);
  return ppDVar1;
}
