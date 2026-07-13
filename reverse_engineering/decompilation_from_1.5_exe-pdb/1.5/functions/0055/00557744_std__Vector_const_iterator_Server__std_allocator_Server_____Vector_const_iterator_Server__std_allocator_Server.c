/*
 * Entry: 00557744
 * Name: std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>
 * Namespace: std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>
 * Signature: _Vector_const_iterator<Server_*,std::allocator<Server_*>_> * _Vector_const_iterator<Server_*,std::allocator<Server_*>_>(_Vector_const_iterator<Server_*,std::allocator<Server_*>_> * this, Server * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_const_iterator<Server_*,std::allocator<Server_*>_> * __thiscall
std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
_Vector_const_iterator<Server_*,std::allocator<Server_*>_>
          (_Vector_const_iterator<Server_*,std::allocator<Server_*>_> *this,Server **param_1,
          _Container_base_aux *param_2)

{
  this->_padding_ = 0;
  if (((param_2 == (_Container_base_aux *)0x0) || (param_1 < param_2[3]._Myownedaux)) ||
     (param_2[4]._Myownedaux < param_1)) {
    _invalid_parameter_noinfo();
  }
  this->_padding_ = (int)param_2->_Myownedaux;
  this->_Myptr = param_1;
  return this;
}
