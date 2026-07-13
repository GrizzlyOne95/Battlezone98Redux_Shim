/*
 * Entry: 0048bb09
 * Name: std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Namespace: std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>(_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * this, DistributedObject * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * __thiscall
std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
          (_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *this,
          DistributedObject **param_1,_Container_base_aux *param_2)

{
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            ((_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *)
             this,param_1,param_2);
  return this;
}
