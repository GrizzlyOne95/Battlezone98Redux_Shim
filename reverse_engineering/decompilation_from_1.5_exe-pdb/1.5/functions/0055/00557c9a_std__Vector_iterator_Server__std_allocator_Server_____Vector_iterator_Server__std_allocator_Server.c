/*
 * Entry: 00557c9a
 * Name: std::_Vector_iterator<Server_*,std::allocator<Server_*>_>::_Vector_iterator<Server_*,std::allocator<Server_*>_>
 * Namespace: std::_Vector_iterator<Server_*,std::allocator<Server_*>_>
 * Signature: _Vector_iterator<Server_*,std::allocator<Server_*>_> * _Vector_iterator<Server_*,std::allocator<Server_*>_>(_Vector_iterator<Server_*,std::allocator<Server_*>_> * this, Server * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Server_*,std::allocator<Server_*>_> * __thiscall
std::_Vector_iterator<Server_*,std::allocator<Server_*>_>::
_Vector_iterator<Server_*,std::allocator<Server_*>_>
          (_Vector_iterator<Server_*,std::allocator<Server_*>_> *this,Server **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
            ((_Vector_const_iterator<Server_*,std::allocator<Server_*>_> *)this,param_1,param_2);
  return this;
}
