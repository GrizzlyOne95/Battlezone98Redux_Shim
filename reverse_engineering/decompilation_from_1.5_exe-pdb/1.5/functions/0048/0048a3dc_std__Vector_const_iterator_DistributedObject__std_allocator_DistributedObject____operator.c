/*
 * Entry: 0048a3dc
 * Name: std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::operator==
 * Namespace: std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: bool operator==(_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * this, _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::operator==
          (_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *this,
          _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> *param_1)

{
  if ((this->_padding_ == 0) || (this->_padding_ != param_1->_padding_)) {
    _invalid_parameter_noinfo();
  }
  return (bool)('\x01' - (this->_Myptr != param_1->_Myptr));
}
