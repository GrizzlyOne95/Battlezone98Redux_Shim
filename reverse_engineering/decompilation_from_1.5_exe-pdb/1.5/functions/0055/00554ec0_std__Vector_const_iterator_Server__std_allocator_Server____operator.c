/*
 * Entry: 00554ec0
 * Name: std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator==
 * Namespace: std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>
 * Signature: bool operator==(_Vector_const_iterator<Server_*,std::allocator<Server_*>_> * this, _Vector_const_iterator<Server_*,std::allocator<Server_*>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator==
          (_Vector_const_iterator<Server_*,std::allocator<Server_*>_> *this,
          _Vector_const_iterator<Server_*,std::allocator<Server_*>_> *param_1)

{
  if ((this->_padding_ == 0) || (this->_padding_ != param_1->_padding_)) {
    _invalid_parameter_noinfo();
  }
  return (bool)('\x01' - (this->_Myptr != param_1->_Myptr));
}
