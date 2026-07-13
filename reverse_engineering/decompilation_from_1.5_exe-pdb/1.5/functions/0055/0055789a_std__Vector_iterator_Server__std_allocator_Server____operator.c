/*
 * Entry: 0055789a
 * Name: std::_Vector_iterator<Server_*,std::allocator<Server_*>_>::operator+=
 * Namespace: std::_Vector_iterator<Server_*,std::allocator<Server_*>_>
 * Signature: _Vector_iterator<Server_*,std::allocator<Server_*>_> * operator+=(_Vector_iterator<Server_*,std::allocator<Server_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Server_*,std::allocator<Server_*>_> * __thiscall
std::_Vector_iterator<Server_*,std::allocator<Server_*>_>::operator+=
          (_Vector_iterator<Server_*,std::allocator<Server_*>_> *this,int param_1)

{
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator+=
            ((_Vector_const_iterator<Server_*,std::allocator<Server_*>_> *)this,param_1);
  return this;
}
