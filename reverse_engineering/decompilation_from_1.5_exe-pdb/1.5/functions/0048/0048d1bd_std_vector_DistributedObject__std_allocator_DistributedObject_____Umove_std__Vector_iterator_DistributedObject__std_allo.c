/*
 * Entry: 0048d1bd
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Umove<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>_>
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: DistributedObject * * _Umove<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>_>(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this, _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_1, _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_2, DistributedObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject ** __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::
_Umove<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>_>
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this,
          _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_1,
          _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> param_2,
          DistributedObject **param_3)

{
  DistributedObject **ppDVar1;
  
  ppDVar1 = stdext::
            _Unchecked_uninitialized_move<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*_*,std::allocator<DistributedObject_*>_>
                      (param_1,param_2,param_3,(allocator<DistributedObject_*> *)&this->_padding_);
  return ppDVar1;
}
